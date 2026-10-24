#include "nx2d.h"
#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#ifndef CONFIG_GAMES_NX2D_PROGNAME
#define CONFIG_GAMES_NX2D_PROGNAME "nx2d"
#endif
static uint64_t nx2d_main_us(void)
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000000u + ts.tv_nsec / 1000u;
}
/* ARMv7-M DWT: measure short sections in CPU cycles without depending on
 * CLOCK_MONOTONIC tick resolution. This is optional and has a safe fallback.
 * Addresses are ARM architectural debug registers (Cortex-M7 only). */
#if defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_7M__)
#  define NX2D_DWT_DEMCR (*(volatile uint32_t *)0xe000edfc)
#  define NX2D_DWT_CTRL  (*(volatile uint32_t *)0xe0001000)
#  define NX2D_DWT_CYCCNT (*(volatile uint32_t *)0xe0001004)
static bool nx2d_dwt_start(void)
{
  NX2D_DWT_DEMCR |= (1u << 24);
  NX2D_DWT_CYCCNT = 0;
  NX2D_DWT_CTRL |= 1u;
  return (NX2D_DWT_CTRL & 1u) != 0;
}
static uint32_t nx2d_dwt_now(void) { return NX2D_DWT_CYCCNT; }
#else
static bool nx2d_dwt_start(void) { return false; }
static uint32_t nx2d_dwt_now(void) { return 0; }
#endif
extern void nx2d_video_set_detailed_profile(bool enable);
/* Mirror the section snapshot returned by the video module. */
struct nx2d_video_cycles_s
{
  uint64_t bg, map, objects, expand, fbwrite;
  uint32_t frames;
};
extern void nx2d_video_profile_take(struct nx2d_video_cycles_s *out);

#define NX2D_FRAME_NS 16666667LL
static int64_t nx2d_ts_ns(const struct timespec *ts)
{
  return (int64_t)ts->tv_sec * 1000000000LL + ts->tv_nsec;
}
static struct timespec nx2d_from_ns(int64_t ns)
{
  struct timespec ts;
  ts.tv_sec = (time_t)(ns / 1000000000LL);
  ts.tv_nsec = (long)(ns % 1000000000LL);
  return ts;
}
/* Advance to the first future deadline; never catch up with a busy loop. */
static unsigned nx2d_wait_frame(int64_t *next_ns)
{
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  int64_t current = nx2d_ts_ns(&now);
  unsigned skipped = 0;
  if (current >= *next_ns)
    {
      int64_t missed = (current - *next_ns) / NX2D_FRAME_NS + 1;
      skipped = missed > 0xffffffffLL ? 0xffffffffu : (unsigned)missed;
      *next_ns += missed * NX2D_FRAME_NS;
    }
  struct timespec deadline = nx2d_from_ns(*next_ns);
  int ret;
  do { ret = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME,
                             &deadline, NULL); } while (ret == EINTR);
  *next_ns += NX2D_FRAME_NS;
  return skipped;
}
int main(int argc, char **argv)
{
  struct nx2d_video_s video;
  struct nx2d_game_s game;
  const char *fb = argc > 1 ? argv[1] : "/dev/fb0";
  const char *input = argc > 2 ? argv[2] : NULL;
  if (nx2d_video_open(&video, fb) < 0)
    { perror("nx2d framebuffer"); return EXIT_FAILURE; }
  int joyfd = nx2d_input_open(input);
  if (input && joyfd < 0) perror("nx2d controller");
  unsigned scaler = 6; /* v12 exact-ratio scaler by default */
  if (argc > 3)
    {
      if (strcmp(argv[3], "memcpy") == 0) scaler = 0;
      else if (strcmp(argv[3], "word32") == 0) scaler = 1;
      else if (strcmp(argv[3], "unroll") == 0) scaler = 2;
      else if (strcmp(argv[3], "rowcopy") == 0) scaler = 3;
      else if (strcmp(argv[3], "burst16") == 0) scaler = 4;
      else if (strcmp(argv[3], "packed") == 0) scaler = 5;
      else if (strcmp(argv[3], "ratio") == 0) scaler = 6;
      else if (strcmp(argv[3], "ratio16") == 0) scaler = 7;
      else if (strcmp(argv[3], "ratio64") == 0) scaler = 8;
      else printf("NX2D: unknown scaler '%s', using ratio\n", argv[3]);
    }
  nx2d_video_set_background(argc > 4 && strcmp(argv[4], "classic") == 0 ? 0u : 1u);
  bool bench = false;
  bool detail = false;
  bool quiet = false;
  for (int i = 3; i < argc; ++i)
    {
      if (strcmp(argv[i], "bench") == 0) bench = true;
      if (strcmp(argv[i], "detail") == 0) detail = true;
      if (strcmp(argv[i], "quiet") == 0) quiet = true;
    }
  nx2d_video_set_detailed_profile(detail);
  nx2d_video_set_scaler(&video, scaler);
  if (bench) nx2d_video_benchmark(&video, scaler);
  else printf("NX2D: startup benchmark disabled (add bench to enable)\n");
  bool dwt_enabled = nx2d_dwt_start();
  printf("NX2D V20: DWT profiling %s; quiet=%u\n",
         dwt_enabled ? "enabled (CPU cycles)" : "unavailable", quiet ? 1u : 0u);
  nx2d_game_init(&game);
  struct timespec next;
  clock_gettime(CLOCK_MONOTONIC, &next);
  int64_t next_ns = nx2d_ts_ns(&next) + NX2D_FRAME_NS;
  printf("NX2D: %ux%u L8 indexed; input=%s\n", video.width, video.height,
         input ? input : "none");
  /* V14: collect timing before printing anything. Console output is deferred
   * until after the frame wait and never occurs inside the measured sections.
   * Input and update timings are separate, including elapsed preemption. */
  uint64_t input_sum = 0, update_sum = 0, render_sum = 0, work_sum = 0;
  uint64_t input_max = 0, update_max = 0, render_max = 0, work_max = 0;
  uint64_t work_min = UINT64_MAX;
  uint64_t worst_input = 0, worst_update = 0, worst_render = 0;
  unsigned profile_frames = 0, overruns = 0, skipped_sum = 0;
  unsigned wake_late = 0, wake_late_max_us = 0;
  unsigned skips_1 = 0, skips_2plus = 0;
  unsigned slow_input = 0, slow_update = 0, slow_render = 0;
  uint32_t last_ticks = 0;
  unsigned zero_input = 0, zero_update = 0;
  unsigned max_enemies = 0, max_bullets = 0, max_effects = 0;
  uint64_t input_cycles_sum = 0, update_cycles_sum = 0, render_cycles_sum = 0;
  uint32_t input_cycles_max = 0, update_cycles_max = 0, render_cycles_max = 0;
  for (;;)
    {
      uint32_t c0 = nx2d_dwt_now();
      uint64_t t0 = nx2d_main_us();
      uint32_t buttons = nx2d_input_read(joyfd);
      uint64_t t1 = nx2d_main_us();
      uint32_t c1 = nx2d_dwt_now();
      if (buttons & NX2D_BUTTON_QUIT) break;
      nx2d_game_step(&game, buttons);
      uint64_t t2 = nx2d_main_us();
      uint32_t c2 = nx2d_dwt_now();
      nx2d_video_draw(&video, &game);
      uint64_t t3 = nx2d_main_us();
      uint32_t c3 = nx2d_dwt_now();
      uint64_t input_us = t1 - t0;
      uint64_t update_us = t2 - t1;
      uint64_t render_us = t3 - t2;
      uint64_t work_us = t3 - t0;
      if (dwt_enabled)
        {
          uint32_t ic = c1 - c0, uc = c2 - c1, rc = c3 - c2;
          input_cycles_sum += ic;
          update_cycles_sum += uc;
          render_cycles_sum += rc;
          if (ic > input_cycles_max) input_cycles_max = ic;
          if (uc > update_cycles_max) update_cycles_max = uc;
          if (rc > render_cycles_max) render_cycles_max = rc;
        }
      input_sum += input_us;
      update_sum += update_us;
      render_sum += render_us;
      work_sum += work_us;
      if (input_us > input_max) input_max = input_us;
      if (update_us > update_max) update_max = update_us;
      if (render_us > render_max) render_max = render_us;
      if (work_us > work_max)
        {
          work_max = work_us;
          worst_input = input_us;
          worst_update = update_us;
          worst_render = render_us;
        }
      if (work_us < work_min) work_min = work_us;
      if (input_us == 0) zero_input++;
      if (update_us == 0) zero_update++;
      unsigned active_enemies = 0, active_bullets = 0, active_effects = 0;
      for (unsigned j = 0; j < NX2D_MAX_ENEMIES; j++)
        if (game.enemies[j].active) active_enemies++;
      for (unsigned j = 0; j < NX2D_MAX_BULLETS; j++)
        if (game.bullets[j].active) active_bullets++;
      for (unsigned j = 0; j < NX2D_MAX_EFFECTS; j++)
        if (game.effects[j].active) active_effects++;
      if (active_enemies > max_enemies) max_enemies = active_enemies;
      if (active_bullets > max_bullets) max_bullets = active_bullets;
      if (active_effects > max_effects) max_effects = active_effects;
      if (input_us > 3000) slow_input++;
      if (update_us > 5000) slow_update++;
      if (render_us > 14000) slow_render++;
      if (work_us > 16667) overruns++;
      unsigned skipped = nx2d_wait_frame(&next_ns);
      skipped_sum += skipped;
      if (skipped == 1) skips_1++;
      if (skipped >= 2) skips_2plus++;
      /* How late did the actual wake-up happen relative to the deadline? */
      int64_t wake_ns = (int64_t)nx2d_main_us() * 1000;
      int64_t lateness_ns = wake_ns - (next_ns - NX2D_FRAME_NS);
      if (lateness_ns > 0)
        {
          wake_late++;
          unsigned late_us = (unsigned)(lateness_ns / 1000);
          if (late_us > wake_late_max_us) wake_late_max_us = late_us;
        }
      if (++profile_frames >= 120)
        {
          /* The following prints can delay the *next* frame. To isolate
           * console interference, also test with `quiet` mode below. */
          if (!quiet) printf("NX2D V20: input=%lu update=%lu render=%lu work=%lu us avg/120\n",
                 (unsigned long)(input_sum / profile_frames),
                 (unsigned long)(update_sum / profile_frames),
                 (unsigned long)(render_sum / profile_frames),
                 (unsigned long)(work_sum / profile_frames));
          if (!quiet) printf("NX2D V20 MAX: input=%lu update=%lu render=%lu work=%lu min=%lu us\n",
                 (unsigned long)input_max, (unsigned long)update_max,
                 (unsigned long)render_max, (unsigned long)work_max,
                 (unsigned long)work_min);
          if (!quiet) printf("NX2D V20 WORST: input=%lu update=%lu render=%lu us overruns=%u skipped=%u/120\n",
                 (unsigned long)worst_input, (unsigned long)worst_update,
                 (unsigned long)worst_render, overruns, skipped_sum);
          if (!quiet) printf("NX2D V20 SPIKES: input_gt3ms=%u update_gt5ms=%u render_gt14ms=%u/120\n",
                 slow_input, slow_update, slow_render);
          if (!quiet) printf("NX2D V20 GAME: ticks=%lu (+%lu) x=%ld y=%ld camera=%ld hp=%u checkpoint=%u deaths=%u\n",
                 (unsigned long)game.ticks,
                 (unsigned long)(game.ticks - last_ticks),
                 (long)(game.x / 65536), (long)(game.y / 65536),
                 (long)game.camera,
                 (unsigned)game.hp, (unsigned)game.checkpoint,
                 (unsigned)game.deaths);
          if (!quiet) printf("NX2D V20 PROGRESS: score=%u tokens=%u/%u kills=%u enemies_max=%u bullets_max=%u effects_max=%u\n",
                 (unsigned)game.score, (unsigned)game.pickups_collected,
                 (unsigned)NX2D_MAX_PICKUPS, (unsigned)game.kills,
                 max_enemies, max_bullets, max_effects);
          if (!quiet) printf("NX2D V20 CLOCK: zero_input=%u zero_update=%u/120 (clock resolution may hide short stages)\n",
                 zero_input, zero_update);
          if (!quiet && dwt_enabled)
            {
              printf("NX2D V20 DWT AVG: input=%lu update=%lu render=%lu cycles/frame\n",
                     (unsigned long)(input_cycles_sum / profile_frames),
                     (unsigned long)(update_cycles_sum / profile_frames),
                     (unsigned long)(render_cycles_sum / profile_frames));
              printf("NX2D V20 DWT MAX: input=%lu update=%lu render=%lu cycles\n",
                     (unsigned long)input_cycles_max,
                     (unsigned long)update_cycles_max,
                     (unsigned long)render_cycles_max);
            }
          struct nx2d_video_cycles_s vp;
          nx2d_video_profile_take(&vp);
          if (!quiet && dwt_enabled && vp.frames)
            {
              printf("NX2D V20 VIDEO AVG: bg=%lu map=%lu objects=%lu expand=%lu fbwrite=%lu cycles/frame\n",
                     (unsigned long)(vp.bg / vp.frames),
                     (unsigned long)(vp.map / vp.frames),
                     (unsigned long)(vp.objects / vp.frames),
                     (unsigned long)(vp.expand / vp.frames),
                     (unsigned long)(vp.fbwrite / vp.frames));
            }
          if (!quiet)
            printf("NX2D V20 PACING: skips1=%u skips2plus=%u late_wakes=%u/120 max_late=%u us\n",
                   skips_1, skips_2plus, wake_late, wake_late_max_us);
          skips_1 = skips_2plus = wake_late = wake_late_max_us = 0;
          input_cycles_sum = update_cycles_sum = render_cycles_sum = 0;
          input_cycles_max = update_cycles_max = render_cycles_max = 0;
          last_ticks = game.ticks;
          zero_input = zero_update = 0;
          max_enemies = max_bullets = max_effects = 0;
          input_sum = update_sum = render_sum = work_sum = 0;
          input_max = update_max = render_max = work_max = 0;
          worst_input = worst_update = worst_render = 0;
          work_min = UINT64_MAX;
          profile_frames = overruns = skipped_sum = 0;
          slow_input = slow_update = slow_render = 0;
        }
    }
  if (joyfd >= 0) close(joyfd);
  nx2d_video_close(&video);
  return EXIT_SUCCESS;
}
