#include "bitmap.h"

#include <stdio.h>
#include <stdlib.h>

#pragma pack(2)
typedef struct {
  unsigned short bfType;
  unsigned int bfSize;
  unsigned short bfReserved1;
  unsigned short bfReserved2;
  unsigned int bfOffBits;
} BitmapFileHeader;

typedef struct {
  unsigned int biSize;
  unsigned int biWidth;
  unsigned int biHeight;
  unsigned short biPlanes;  // default: 1, custom: 0
  unsigned short biBitCount;
  unsigned int biCompression;
  unsigned int biSizeImage;
  unsigned int biXPelsPerMeter;  // 72 dpi = 2835 ppm, 96 dpi = 3780 ppm
  unsigned int biYPelsPerMeter;  // 120 dpi = 4724 ppm, 300 dpi = 11811 ppm
  unsigned int biClrUsed;
  unsigned int biClrImportant;
} BitmapInfoHeader;
#pragma pack()

void write_to_bitmap(const char *name, const unsigned char *raw_img,
                     unsigned int width, unsigned int height,
                     unsigned short bits) {
  if (!(name && raw_img)) {
    perror("Error write_to_bitmap.");
    return;
  }

  BitmapFileHeader file_h;
  file_h.bfType = 0x4d42;
  file_h.bfReserved1 = 0;
  file_h.bfReserved2 = 0;
  file_h.bfOffBits = 54;
  file_h.bfSize = file_h.bfOffBits + width * height * bits / 8;

  if (bits == 8) {
    file_h.bfSize += 1024;
    file_h.bfOffBits += 1024;
  }

  BitmapInfoHeader info_h;
  info_h.biSize = 40;
  info_h.biPlanes = 1;
  info_h.biCompression = 0;
  info_h.biXPelsPerMeter = 0;
  info_h.biYPelsPerMeter = 0;
  info_h.biClrUsed = 0;
  info_h.biClrImportant = 0;
  info_h.biWidth = width;
  info_h.biHeight = height;
  info_h.biBitCount = bits;
  info_h.biSizeImage = width * height * bits / 8;
  if (bits == 8) {
    info_h.biClrUsed = 256;
  }

  FILE *pFile = fopen(name, "wb+");
  if (!pFile) {
    perror("Error opening file.");
    return;
  }

  fwrite(&file_h, sizeof(char), sizeof(file_h), pFile);
  fwrite(&info_h, sizeof(char), sizeof(info_h), pFile);
  if (bits == 8) {
    for (unsigned i = 0; i < 256; ++i) {
      unsigned char c = i;
      fwrite(&c, sizeof(char), sizeof(unsigned char), pFile);
      fwrite(&c, sizeof(char), sizeof(unsigned char), pFile);
      fwrite(&c, sizeof(char), sizeof(unsigned char), pFile);
      char padding = 0;
      fwrite(&padding, sizeof(char), sizeof(unsigned char), pFile);
    }
  }

  size_t align = (width * bits / 8) % 4;
  for (int j = height - 1; j >= 0; --j) {
    for (unsigned i = 0; i < width; ++i) {
      unsigned int idx = j * width + i;
      if (bits == 24) {
        fwrite(&raw_img[idx * 3 + 2], sizeof(char), sizeof(unsigned char),
               pFile);
        fwrite(&raw_img[idx * 3 + 1], sizeof(char), sizeof(unsigned char),
               pFile);
        fwrite(&raw_img[idx * 3], sizeof(char), sizeof(unsigned char), pFile);
      } else if (bits == 8) {
        fwrite(&raw_img[idx], sizeof(char), sizeof(unsigned char), pFile);
      }
    }
    for (size_t i = 0; i < align; ++i) {
      char padding = 0;
      fwrite(&padding, sizeof(char), sizeof(unsigned char), pFile);
    }
  }
  fclose(pFile);
}

void read_from_bitmap(const char *name, unsigned char **raw_img,
                      unsigned int *width, unsigned int *height,
                      unsigned short *bits) {
  if (!(name && raw_img && width && height && bits)) {
    perror("Error read_from_bitmap.");
    return;
  }

  BitmapFileHeader file_h;
  BitmapInfoHeader info_h;

  FILE *pFile = fopen(name, "rb+");
  if (!pFile) {
    perror("Error opening file.");
    return;
  }

  fread(&file_h, sizeof(char), sizeof(file_h), pFile);
  fread(&info_h, sizeof(char), sizeof(info_h), pFile);

  *width = info_h.biWidth;
  *height = info_h.biHeight;
  *bits = info_h.biBitCount;
  size_t ImgSize = (*width) * (*height) * 3;
  *raw_img = (unsigned char *)calloc(ImgSize, sizeof(unsigned char));

  fseek(pFile, file_h.bfOffBits, SEEK_SET);
  size_t align = (info_h.biWidth * info_h.biBitCount / 8) % 4;
  for (int j = *height - 1; j >= 0; --j) {
    for (unsigned i = 0; i < *width; ++i) {
      unsigned int idx = j * (*width) + i;
      if (*bits == 24) {
        fread(&(*raw_img)[idx * 3 + 2], sizeof(char), sizeof(unsigned char),
              pFile);
        fread(&(*raw_img)[idx * 3 + 1], sizeof(char), sizeof(unsigned char),
              pFile);
        fread(&(*raw_img)[idx * 3], sizeof(char), sizeof(unsigned char), pFile);
      } else if (*bits == 8) {
        fread(&(*raw_img)[idx], sizeof(char), sizeof(unsigned char), pFile);
      }
    }
    fseek(pFile, (long)align, SEEK_CUR);
  }
  fclose(pFile);
}

void bitmap_write(const bitmap_t *bitmap, const char *name) {
  write_to_bitmap(name, bitmap->data, bitmap->width, bitmap->height,
                  bitmap->bits);
}

void bitmap_read(bitmap_t *bitmap, const char *name) {
  read_from_bitmap(name, &bitmap->data, &bitmap->width, &bitmap->height,
                   &bitmap->bits);
}

/* Example Code */

int main() {
  bitmap_t bitmap;
  bitmap_read(&bitmap, "test.bmp");
  bitmap_write(&bitmap, "test2.bmp");
  return 0;
}
