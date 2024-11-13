#if !defined(OS_WINDOWS_BITMAP_H_INCLUDED)
#define OS_WINDOWS_BITMAP_H_INCLUDED

// bool, true, false
#include <stdbool.h>

// uint8_t 
#include <stdint.h>

#include "os-commons.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct bitmap_t {
  reference_count_t reference_count;
  int width;
  int height;
  uint32_t* pixels;
  HBITMAP hBitmap;
};

int bitmap_create(struct bitmap_t** result, int width, int height);

int bitmap_ref(struct bitmap_t* self);

int bitmap_unref(struct bitmap_t* self);

#endif // OS_WINDOWS_BITMAP_H_INCLUDED
