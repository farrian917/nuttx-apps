#include "nx2d.h"
#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <fcntl.h>
#include <errno.h>
#ifndef CONFIG_GAMES_NX2D_PROGNAME
#define CONFIG_GAMES_NX2D_PROGNAME "nx2d"
#endif
static void tick_sleep(struct timespec *next)
{
  next->tv_nsec += 16666667L;
  if (next->tv_nsec >= 1000000000L)
    { next->tv_sec++; next->tv_nsec -= 1000000000L; }
  while (clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, next, NULL) == EINTR) {}
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
  nx2d_game_init(&game);
  struct timespec next;
  clock_gettime(CLOCK_MONOTONIC, &next);
  printf("NX2D: %ux%u RGB565; input=%s\n", video.width, video.height,
         input ? input : "none");
  for (;;)
    {
      uint32_t buttons = nx2d_input_read(joyfd);
      if (buttons & NX2D_BUTTON_QUIT) break;
      nx2d_game_step(&game, buttons);
      nx2d_video_draw(&video, &game);
      tick_sleep(&next);
    }
  if (joyfd >= 0) close(joyfd);
  nx2d_video_close(&video);
  return EXIT_SUCCESS;
}
