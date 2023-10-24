#ifndef FORMATS_BMP_BITMAP_H_
#define FORMATS_BMP_BITMAP_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct bitmap_t {
  unsigned int width, height;
  unsigned short bits;
  unsigned char *data;
} bitmap_t;

void bitmap_write(const bitmap_t *bitmap, const char *name);
void bitmap_read(bitmap_t *bitmap, const char *name);

#endif  // FORMATS_BMP_BITMAP_H_
