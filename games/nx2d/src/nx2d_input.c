#include "nx2d.h"

#include <nuttx/input/xbox-controller.h>

#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/* Adjust these names to match nx2d.h */

#ifndef NX2D_BUTTON_LEFT
#  error "NX2D_BUTTON_LEFT missing"
#endif

static uint32_t g_last_buttons;

int nx2d_input_open(const char *path)
{
  int fd;

  g_last_buttons = 0;

  if (path == NULL)
    {
      path = "/dev/xboxa";
    }

  fd = open(path, O_RDONLY | O_NONBLOCK);

  if (fd < 0)
    {
      printf("NX2D: Xbox open %s failed: %d\n",
             path, errno);
    }
  else
    {
      printf("NX2D: Xbox connected: %s\n", path);
    }

  return fd;
}

uint32_t nx2d_input_read(int fd)
{
  struct xbox_controller_buttonstate_s pad;
  uint32_t buttons = 0;
  ssize_t n;

  if (fd < 0)
    {
      return 0;
    }

  memset(&pad, 0, sizeof(pad));

  n = read(fd, &pad, sizeof(pad));

  if (n < 0)
    {
      if (errno == EAGAIN || errno == EINTR)
        {
          return g_last_buttons;
        }

      g_last_buttons = 0;
      return 0;
    }

  if (n != sizeof(pad))
    {
      return g_last_buttons;
    }

  /* Movement */

  if (pad.dpad_left || pad.stick_left_x < -8000)
    {
      buttons |= NX2D_BUTTON_LEFT;
    }

  if (pad.dpad_right || pad.stick_left_x > 8000)
    {
      buttons |= NX2D_BUTTON_RIGHT;
    }

  /* Jump */

  if (pad.a)
    {
      buttons |= NX2D_BUTTON_JUMP;
    }

  /* Shooting: enable when the engine defines it */

#ifdef NX2D_BUTTON_FIRE
  if (pad.x || pad.bumper_right)
    {
      buttons |= NX2D_BUTTON_FIRE;
    }
#endif

  if (pad.x || pad.bumper_right)
    {
      buttons |= NX2D_BUTTON_FIRE;
    }

  if (pad.y) buttons |= NX2D_BUTTON_WEAPON;
  g_last_buttons = buttons;
  return buttons;
}