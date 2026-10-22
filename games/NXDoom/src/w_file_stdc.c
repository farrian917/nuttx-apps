/****************************************************************************
 * apps/games/NXDoom/src/w_file_stdc.c
 *
 * SPDX-License-Identifer: GPLv2
 *
 * Copyright(C) 1993-1996 Id Software, Inc.
 * Copyright(C) 2005-2014 Simon Howard
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * DESCRIPTION:
 *  WAD I/O functions.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

#include "m_misc.h"
#include "w_file.h"
#include "z_zone.h"


/****************************************************************************
 * Defines
 ****************************************************************************/

#define WAD_READ_CHUNK 1024

/****************************************************************************
 * Private Types
 ****************************************************************************/

typedef struct
{
  wad_file_t wad;
  FILE *fstream;
} stdc_wad_file_t;

static uint8_t g_wad_read_buffer[WAD_READ_CHUNK] __attribute__((aligned(32)));

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static wad_file_t *w_stdc_openfile(const char *path);
static void w_stdc_closefile(wad_file_t *wad);
static size_t w_stdc_read(wad_file_t *wad, unsigned int offset, void *buffer,
                          size_t buffer_len);

/****************************************************************************
 * Public Data
 ****************************************************************************/

wad_file_class_t stdc_wad_file =
{
  w_stdc_openfile,
  w_stdc_closefile,
  w_stdc_read,
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static wad_file_t *w_stdc_openfile(const char *path)
{
  stdc_wad_file_t *result;
  FILE *fstream;

  fstream = fopen(path, "rb");

  if (fstream == NULL)
    {
      return NULL;
    }

  /* Create a new stdc_wad_file_t to hold the file handle. */

  result = z_malloc(sizeof(stdc_wad_file_t), PU_STATIC, 0);
  result->wad.file_class = &stdc_wad_file;
  result->wad.mapped = NULL;
  result->wad.length = m_file_length(fstream);
  result->wad.path = m_string_duplicate(path);
  result->fstream = fstream;

  return &result->wad;
}

static void w_stdc_closefile(wad_file_t *wad)
{
  stdc_wad_file_t *stdc_wad;

  stdc_wad = (stdc_wad_file_t *)wad;

  fclose(stdc_wad->fstream);
  z_free(stdc_wad);
}

/* Read data from the specified position in the file into the
 * provided buffer.  Returns the number of bytes read.
 */

// static size_t w_stdc_read(wad_file_t *wad, unsigned int offset, void *buffer,
//                           size_t buffer_len)
// {
//   stdc_wad_file_t *stdc_wad;
//   size_t result;

//   stdc_wad = (stdc_wad_file_t *)wad;

//   /* Jump to the specified position in the file. */

//   fseek(stdc_wad->fstream, offset, SEEK_SET);

//   /* Read into the buffer. */

//   result = fread(buffer, 1, buffer_len, stdc_wad->fstream);

//   return result;
// }

static size_t w_stdc_read(wad_file_t *wad, unsigned int offset,
                          void *buffer, size_t buffer_len)
{
  stdc_wad_file_t *stdc_wad = (stdc_wad_file_t *)wad;
  uint8_t *dest = (uint8_t *)buffer;
  size_t total = 0;

  if (fseek(stdc_wad->fstream, (long)offset, SEEK_SET) != 0)
    {
      printf("WAD: fseek failed errno=%d\n", errno);
      return 0;
    }

  printf("WAD: dest=%p temp=%p size=%lu\n",
         buffer,
         g_wad_read_buffer,
         (unsigned long)buffer_len);

  while (total < buffer_len)
    {
      size_t remaining = buffer_len - total;
      size_t chunk = remaining > WAD_READ_CHUNK ?
                     WAD_READ_CHUNK : remaining;

      size_t n = fread(g_wad_read_buffer, 1, chunk,
                       stdc_wad->fstream);

      if (n > 0)
        {
          memcpy(dest + total, g_wad_read_buffer, n);
          total += n;
        }

      if (n != chunk)
        {
          printf("WAD: read failed offset=%lu total=%lu errno=%d\n",
                 (unsigned long)offset,
                 (unsigned long)total,
                 errno);
          break;
        }
    }

  return total;
}