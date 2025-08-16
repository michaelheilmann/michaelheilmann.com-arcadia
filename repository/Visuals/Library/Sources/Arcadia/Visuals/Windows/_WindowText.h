#if !defined(ARCADIA_VISUALS_WINDOWS__WINDOWTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS__WINDOWTEXT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

Arcadia_String*
Windows_getWindowText
  (
    Arcadia_Thread* thread,
    HWND hWnd
  );

void
Windows_setWindowText
  (
    Arcadia_Thread* thread,
    HWND hWnd,
    Arcadia_String* text
  );

static BOOL
Windows_multiByteToWideChar
  (
    const char* p,
    size_t n,
    wchar_t** q,
    size_t* m
  );

#endif // ARCADIA_VISUALS_WINDOWS__WINDOWTEXT_H_INCLUDED
