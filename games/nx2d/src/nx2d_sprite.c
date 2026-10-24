#include "nx2d_sprite.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
static int exact_read(int fd,void *dst,size_t len)
{
  uint8_t *p=dst;
  while(len)
    {
      ssize_t n=read(fd,p,len);
      if(n<0 && errno==EINTR) continue;
      if(n<=0) return -1;
      p+=n;len-=(size_t)n;
    }
  return 0;
}
static unsigned le16(const uint8_t *p) { return (unsigned)p[0]|((unsigned)p[1]<<8); }
int nx2d_sprite_load(struct nx2d_sprite_s *s,const char *path)
{
  uint8_t h[12];size_t bytes;int fd;
  memset(s,0,sizeof(*s));fd=open(path,O_RDONLY);
  if(fd<0) return -1;
  if(exact_read(fd,h,sizeof(h))<0 || memcmp(h,"NX2S",4)!=0 ||
     le16(h+4)!=NX2D_SPRITE_W || le16(h+6)!=NX2D_SPRITE_H ||
     le16(h+8)!=NX2D_SPRITE_FRAMES || h[11]!=0)
    { close(fd);errno=EINVAL;return -1; }
  s->width=le16(h+4);s->height=le16(h+6);s->frames=le16(h+8);
  s->transparent=h[10];
  bytes=(size_t)s->width*s->height*s->frames;
  s->pixels=malloc(bytes);
  if(!s->pixels) {close(fd);errno=ENOMEM;return -1;}
  if(exact_read(fd,s->pixels,bytes)<0)
    {nx2d_sprite_free(s);close(fd);errno=EIO;return -1;}
  close(fd);return 0;
}
void nx2d_sprite_free(struct nx2d_sprite_s *s)
{ free(s->pixels);memset(s,0,sizeof(*s)); }
void nx2d_sprite_draw(const struct nx2d_sprite_s *s,uint8_t *dst,
                      unsigned stride,unsigned dw,unsigned dh,
                      int x,int y,unsigned frame,bool flip)
{
  if(!s->pixels || frame>=s->frames) return;
  const uint8_t *src=s->pixels+(size_t)frame*s->width*s->height;
  for(unsigned sy=0;sy<s->height;sy++)
    {
      int dy=y+(int)sy;
      if(dy<0 || (unsigned)dy>=dh) continue;
      for(unsigned sx=0;sx<s->width;sx++)
        {
          int dx=x+(int)sx;
          if(dx<0 || (unsigned)dx>=dw) continue;
          unsigned tx=flip?(s->width-1-sx):sx;
          uint8_t c=src[sy*s->width+tx];
          if(c!=s->transparent) dst[(size_t)dy*stride+dx]=c;
        }
    }
}
