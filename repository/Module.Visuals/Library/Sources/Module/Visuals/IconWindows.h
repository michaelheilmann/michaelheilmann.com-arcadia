#if !defined(OS_WINDOWS_ICON_H_INCLUDED)
#define OS_WINDOWS_ICON_H_INCLUDED
 
#include "R.h"

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

Rex_declareObjectType("IconWindows", IconWindows, "R.Object")

struct IconWindows {
  R_Object _parent;
  int32_t reference_count;
  HICON hIcon;
};

void
IconWindows_construct
  (
    IconWindows* self,
    int width,
    int height
  );

IconWindows*
IconWindows_create
  (
    int width,
    int height
  );

#endif // OS_WINDOWS_ICON_H_INCLUDED
