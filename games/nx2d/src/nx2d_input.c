#include "nx2d.h"
#include <fcntl.h>
#include <unistd.h>
/* Adapter for a board-specific controller driver exporting a 32-bit bitmask.
 * Default button mapping is NX2D_BUTTON_*. Replace this adapter with your
 * Xbox USB host driver's actual read/ioctl interface as appropriate.
 */
int nx2d_input_open(const char *path)
{
  return path ? open(path, O_RDONLY | O_NONBLOCK) : -1;
}
uint32_t nx2d_input_read(int fd)
{
  uint32_t buttons = 0;
  if (fd >= 0)
    {
      ssize_t n = read(fd, &buttons, sizeof(buttons));
      if (n != sizeof(buttons)) buttons = 0;
    }
  return buttons;
}
