/* T2NATIVE V1.5: ROM-authentic captured intro, native Cortex-M7 playback.
 * Capture was performed OFFLINE using the original ROM and Musashi/VDP.
 * No ROM, Musashi, or 68000 emulation is needed at runtime.
 */
#include <nuttx/config.h>
#include <nuttx/video/fb.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <poll.h>
#include <stdbool.h>
#include "intro_assets.h"
#include "game_assets.h"
#define GAME_W 320
#define GAME_H 224
#define PIXELS (GAME_W*GAME_H)

struct display_s { int fd,w,h,stride; uint8_t *fb,*logical; };
static int init_display(struct display_s *d)
{
  struct fb_videoinfo_s vi;
  struct fb_planeinfo_s pi;
  d->fd=open("/dev/fb0",O_RDWR);
  if(d->fd<0) {perror("T2NATIVE open /dev/fb0");return -1;}
  if(ioctl(d->fd,FBIOGET_VIDEOINFO,(unsigned long)(uintptr_t)&vi)<0 ||
     ioctl(d->fd,FBIOGET_PLANEINFO,(unsigned long)(uintptr_t)&pi)<0)
    {perror("T2NATIVE framebuffer ioctl");return -1;}
  d->w=vi.xres;d->h=vi.yres;d->stride=pi.stride;d->fb=pi.fbmem;
  if(d->w!=1024 || d->h!=600 || pi.bpp!=8 || d->stride<d->w ||
     pi.fblen<(size_t)d->stride*d->h || !d->fb)
    {printf("T2NATIVE: unsupported framebuffer %dx%d %ubpp stride=%d\n",
            d->w,d->h,(unsigned)pi.bpp,d->stride);return -1;}
  d->logical=malloc(PIXELS);
  if(!d->logical){printf("T2NATIVE: no 320x224 backbuffer\n");return -1;}
#ifdef FBIOPUT_CMAP
  uint8_t r[256],g[256],b[256];
  for(unsigned i=0;i<256;i++){
    r[i]=(uint8_t)(((i>>5)&7u)*255u/7u);
    g[i]=(uint8_t)(((i>>2)&7u)*255u/7u);
    b[i]=(uint8_t)((i&3u)*255u/3u);
  }
  struct fb_cmap_s cmap={0};cmap.first=0;cmap.len=256;
  cmap.red=r;cmap.green=g;cmap.blue=b;
  if(ioctl(d->fd,FBIOPUT_CMAP,(unsigned long)(uintptr_t)&cmap)<0)
    {perror("T2NATIVE FBIOPUT_CMAP");return -1;}
#else
  printf("T2NATIVE: FBIOPUT_CMAP unavailable\n");return -1;
#endif
  printf("T2NATIVE V1.5: FB %dx%d 8bpp stride=%d at %p, viewport %dx%d centered at %d,%d\n",d->w,d->h,d->stride,d->fb,800,560,112,20);
  return 0;
}
/* Centered 800x560 viewport (320x224 at 2.5x), with 112px horizontal
 * and 20px vertical black borders on the 1024x600 LTDC framebuffer.
 * Cache one expanded scanline and duplicate it for repeated source lines.
 * 2.5x horizontal expansion is done using 2 source pixels -> 5 output pixels.
 */
#define VIEW_W 800
#define VIEW_H 560
#define VIEW_X ((1024-VIEW_W)/2)
#define VIEW_Y ((600-VIEW_H)/2)
static void present(struct display_s *d)
{
  uint8_t expanded[VIEW_W];
  int last=-1;
  for(int y=0;y<VIEW_H;y++)
    {
      int sy=(y*GAME_H)/VIEW_H;
      uint8_t *dst=d->fb+(size_t)(y+VIEW_Y)*d->stride+VIEW_X;
      if(sy==last)
        {
          memcpy(dst,dst-d->stride,VIEW_W);
          continue;
        }
      const uint8_t *src=d->logical+(size_t)sy*GAME_W;
      for(int x=0;x<GAME_W;x+=2)
        {
          int o=(x/2)*5;
          expanded[o]=src[x];expanded[o+1]=src[x];
          expanded[o+2]=src[x];
          expanded[o+3]=src[x+1];expanded[o+4]=src[x+1];
        }
      memcpy(dst,expanded,VIEW_W);
      last=sy;
    }
}
static void clear_borders(struct display_s *d)
{
  for(int y=0;y<d->h;y++)
    {
      uint8_t *row=d->fb+(size_t)y*d->stride;
      if(y<VIEW_Y || y>=VIEW_Y+VIEW_H)memset(row,0,d->w);
      else
        {
          memset(row,0,VIEW_X);
          memset(row+VIEW_X+VIEW_W,0,d->w-VIEW_X-VIEW_W);
        }
    }
}
/* Minimal LZ4 raw-block decoder. Bounds checks prevent corrupt data writes.
 * Each frame expands to exactly 320*224 bytes, either absolute or XOR delta.
 */
static int lz4_decode(const uint8_t *src,size_t size,uint8_t *dst,size_t cap)
{
  size_t ip=0,op=0;
  while(ip<size){
    uint8_t token=src[ip++];size_t lit=token>>4;
    if(lit==15){unsigned v;do{if(ip>=size)return -1;v=src[ip++];lit+=v;}while(v==255);}
    if(lit>size-ip || lit>cap-op)return -1;
    memcpy(dst+op,src+ip,lit);ip+=lit;op+=lit;
    if(ip==size)break;
    if(ip+2>size)return -1;
    unsigned dist=(unsigned)src[ip]|((unsigned)src[ip+1]<<8);ip+=2;
    if(!dist || dist>op)return -1;
    size_t match=(token&15u)+4u;
    if((token&15u)==15u){unsigned v;do{if(ip>=size)return -1;v=src[ip++];match+=v;}while(v==255);}
    if(match>cap-op)return -1;
    for(size_t j=0;j<match;j++)dst[op+j]=dst[op+j-dist];
    op+=match;
  }
  return op==cap?0:-1;
}
/* Original VDP sample numbers are nonuniform. Preserve their gaps.
 * Default 25 percent deliberately slows sparse captures by 4x.
 */
#ifndef T2_INTRO_SPEED_PERCENT
#  define T2_INTRO_SPEED_PERCENT 25u
#endif
#if T2_INTRO_SPEED_PERCENT < 1 || T2_INTRO_SPEED_PERCENT > 400
#  error "T2_INTRO_SPEED_PERCENT must be 1..400"
#endif
static uint64_t monotonic_ns(void)
{
  struct timespec ts;
  if(clock_gettime(CLOCK_MONOTONIC,&ts)<0)return 0;
  return (uint64_t)ts.tv_sec*1000000000ull+(uint64_t)ts.tv_nsec;
}
static void wait_until(uint64_t deadline)
{
  for(;;)
    {
      uint64_t now=monotonic_ns();
      if(!now || now>=deadline)break;
      uint64_t remain=deadline-now;
      struct timespec ts={(time_t)(remain/1000000000ull),(long)(remain%1000000000ull)};
      if(nanosleep(&ts,NULL)<0 && errno!=EINTR)break;
    }
}
static void delay_frames(unsigned frames)
{
  struct timespec ts={(time_t)(frames/60u),(long)((frames%60u)*16666667ull)};
  nanosleep(&ts,NULL);
}
static int play_intro(struct display_s *d)
{
  uint8_t *decoded=malloc(PIXELS);
  if(!decoded){printf("T2NATIVE: no frame decode buffer\n");return -1;}
  memset(d->logical,0,PIXELS);
  clear_borders(d);
  uint64_t start=monotonic_ns();
  uint64_t max_render_ns=0;
  unsigned late_frames=0;
  unsigned first=t2_intro_frames[0].sample;
  for(unsigned i=0;i<t2_intro_frame_count;i++){
    uint64_t render_start=monotonic_ns();
    const struct t2_intro_frame_s *fr=&t2_intro_frames[i];
    if(fr->offset>t2_intro_blob_len || fr->size>t2_intro_blob_len-fr->offset ||
       lz4_decode(t2_intro_blob+fr->offset,fr->size,decoded,PIXELS)<0){
      printf("T2NATIVE: damaged intro asset %u\n",i);free(decoded);return -1;
    }
    if(fr->keyframe)memcpy(d->logical,decoded,PIXELS);
    else for(unsigned p=0;p<PIXELS;p++)d->logical[p]^=decoded[p];
    present(d);
    uint64_t render_ns=monotonic_ns()-render_start;
    if(render_ns>max_render_ns)max_render_ns=render_ns;
    /* Absolute deadlines avoid accumulated timing drift. */
    unsigned next=(i+1<t2_intro_frame_count)
      ?t2_intro_frames[i+1].sample:fr->sample+180u;
    uint64_t deadline=start+((uint64_t)(next-first)*1000000000ull*100ull)/(60ull*T2_INTRO_SPEED_PERCENT);
    if(monotonic_ns()>deadline)late_frames++;
    if(i==0 || i%10==0 || i+1==t2_intro_frame_count)
      printf("T2NATIVE V1.5: original ROM frame %u/%u snapshot=%u\n",
             i+1,t2_intro_frame_count,fr->sample);
    wait_until(deadline);
  }
  printf("T2NATIVE V1.5: intro diagnostics: max_decode_present=%lu ms late_frames=%u/%u\n",
         (unsigned long)(max_render_ns/1000000ull),late_frames,t2_intro_frame_count);
  free(decoded);
  return 0;
}

/* T2NATIVE V1.5: original ROM-derived gameplay graphics.
 * Background: VDP capture frame 530 (first level, no player visible).
 * Character: exact changed pixels between VDP frames 530 and 700.
 * All game physics, controls, composition and projectiles are native.
 */
static int read_key(int timeout_ms)
{
  struct pollfd p={.fd=STDIN_FILENO,.events=POLLIN};
  if(poll(&p,1,timeout_ms)<=0 || !(p.revents&POLLIN))return -1;
  unsigned char ch;
  return read(STDIN_FILENO,&ch,1)==1?(int)ch:-1;
}
static void rect(struct display_s *d,int x,int y,int w,int h,uint8_t color)
{
  if(x<0){w+=x;x=0;}if(y<0){h+=y;y=0;}
  if(x>=GAME_W || y>=GAME_H || w<=0 || h<=0)return;
  if(w>GAME_W-x)w=GAME_W-x;
  if(h>GAME_H-y)h=GAME_H-y;
  for(int row=0;row<h;row++)memset(d->logical+(size_t)(y+row)*GAME_W+x,color,(size_t)w);
}
static void blit_player(struct display_s *d,const uint8_t *pixels,
                        const uint8_t *mask,int px,int py,bool facing_left)
{
  for(int sy=0;sy<T2_PLAYER_H;sy++)
    {
      int y=py+sy;
      if(y<0||y>=GAME_H)continue;
      for(int sx=0;sx<T2_PLAYER_W;sx++)
        {
          int x=px+sx;
          if(x<0||x>=GAME_W)continue;
          int ix=sy*T2_PLAYER_W+(facing_left?(T2_PLAYER_W-1-sx):sx);
          if(mask[ix])d->logical[y*GAME_W+x]=pixels[ix];
        }
    }
}
static void gameplay(struct display_s *d)
{
  const size_t sprite_bytes=(size_t)T2_PLAYER_W*T2_PLAYER_H;
  const size_t all_sprite_bytes=sprite_bytes*2*T2_PLAYER_FRAME_COUNT;
  uint8_t *background=malloc(PIXELS);
  uint8_t *sprite=malloc(all_sprite_bytes);
  if(!background||!sprite ||
     lz4_decode(t2_stage_lz4,t2_stage_lz4_size,background,PIXELS)<0 ||
     lz4_decode(t2_player_lz4,t2_player_lz4_size,sprite,all_sprite_bytes)<0)
    {
      printf("T2NATIVE V1.5: gameplay asset decode failed\n");
      free(background);free(sprite);return;
    }
  printf("T2NATIVE V1.5: VDP plane background + SAT-reconstructed T-800 sprites loaded\n");
  printf("T2NATIVE V1.5: a/d move, w jump, f fire, q exit (serial may require Enter)\n");
  int px=T2_PLAYER_ORIGIN_X,py=T2_PLAYER_ORIGIN_Y;
  const int ground_y=T2_PLAYER_ORIGIN_Y;
  int vy=0,bullet_x=-1,bullet_y=0,bullet_dir=1;
  int facing_left=0;
  unsigned fire_pose=0;
  unsigned shots=0;
  uint64_t tick=monotonic_ns();
  bool running=true;
  while(running)
    {
      int key;
      while((key=read_key(0))>=0)
        {
          if(key=='q'||key=='Q'){running=false;break;}
          if(key=='a'||key=='A'){px-=5;facing_left=1;}
          if(key=='d'||key=='D'){px+=5;facing_left=0;}
          if((key=='w'||key=='W')&&py>=ground_y)vy=-10;
          if((key=='f'||key=='F')&&bullet_x<0)
            {
              bullet_dir=facing_left?-1:1;
              bullet_x=px+(facing_left?0:T2_PLAYER_W);
              bullet_y=py+T2_PLAYER_H/2;
              shots++;
              fire_pose=12;
            }
        }
      if(!running)break;
      if(px<0)px=0;
      if(px>GAME_W-T2_PLAYER_W)px=GAME_W-T2_PLAYER_W;
      py+=vy;
      if(py<ground_y)vy++;
      if(py>=ground_y){py=ground_y;vy=0;}
      if(bullet_x>=0)
        {
          bullet_x+=bullet_dir*8;
          if(bullet_x<0||bullet_x>=GAME_W)bullet_x=-1;
        }
      memcpy(d->logical,background,PIXELS);
      /* SAT-reconstructed T-800 poses: snapshot 700 idle,
       * snapshots 720/730/740 contain changed upper-body tiles.
       * Use them only while firing, not as an invented walk cycle.
       */
      unsigned pose=0;
      if(fire_pose)
        {
          pose=1u+((12u-fire_pose)/4u)%3u;
          fire_pose--;
        }
      const uint8_t *frame=sprite+pose*2u*sprite_bytes;
      blit_player(d,frame,frame+sprite_bytes,px,py,facing_left!=0);
      if(bullet_x>=0)rect(d,bullet_x,bullet_y,5,2,0xfc);
      present(d);
      tick+=33333333ull; /* 30Hz native game loop */
      uint64_t now=monotonic_ns();
      if(now>tick+200000000ull)tick=now;
      wait_until(tick);
    }
  printf("T2NATIVE V1.5: gameplay exited, shots=%u\n",shots);
  free(background);free(sprite);
}
static void title_loop(struct display_s *d)
{
  printf("T2NATIVE V1.5: title ready. Press s then Enter to start, q then Enter to quit.\n");
  for(;;)
    {
      int key=read_key(100);
      if(key=='s'||key=='S'||key=='\n'||key=='\r')break;
      if(key=='q'||key=='Q')return;
    }
  gameplay(d);
}
int main(int argc,char **argv)
{
  (void)argc;(void)argv;
  struct display_s d={.fd=-1};
  printf("T2NATIVE V1.5: embedded original intro + authentic first-level gameplay graphics, no Musashi\n");
  if(init_display(&d)<0)goto fail;
  printf("T2NATIVE V1.5: intro playback speed %u%%\n",(unsigned)T2_INTRO_SPEED_PERCENT);
  if(play_intro(&d)<0)goto fail;
  title_loop(&d);
  close(d.fd);free(d.logical);return 0;
fail:
  if(d.fd>=0)close(d.fd);
  free(d.logical);return 1;
}
