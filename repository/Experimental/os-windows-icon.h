#if !defined(OS_WINDOWS_ICON_H_INCLUDED)
#define OS_WINDOWS_ICON_H_INCLUDED
 
#include "os-commons.h"

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct window_icon_t {
  int32_t reference_count;
  HICON hIcon;
};

int window_icon_create(struct window_icon_t** result, int width, int height);

int window_icon_ref(struct window_icon_t* self);

int window_icon_unref(struct window_icon_t* self);

#endif // OS_WINDOWS_ICON_H_INCLUDED
