#if !defined(ARCADIA_VISUALS_WINDOWS__CHARCONV_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS__CHARCONV_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

Arcadia_String*
Windows_fromMultiByte
  (
    Arcadia_Thread* thread,
    CONST CHAR* p,
    size_t n
  );

Arcadia_String*
Windows_fromWideChar
  (
    Arcadia_Thread* thread,
    CONST WCHAR* p,
    size_t n
  );

BOOL
Windows_multiByteToWideChar
  (
    const char* p,
    size_t n,
    wchar_t** q,
    size_t* m
  );

#endif // ARCADIA_VISUALS_WINDOWS__CHARCONV_H_INCLUDED
