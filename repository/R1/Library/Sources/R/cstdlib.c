// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

#include "R/cstdlib.h"

// memmove, memcpy, memcmp
#include <string.h>
// exit, EXIT_FAILURE, malloc, realloc, free
#include <stdlib.h>
#include <stdint.h>
#include "R/Configure.h"

Arcadia_NoReturn() void c_exit(int code) {
  exit(code);
}

void* c_memcpy(void* restrict dst, const void* restrict src, size_t count) {
  return memcpy(dst, src, count);
}

void* c_memmove(void* dst, const void* src, size_t count) {
  return memmove(dst, src, count);
}

int c_memcmp(const void* lhs, const void* rhs, size_t count) {
  return memcmp(lhs, rhs, count);
}

size_t c_strlen(const char* w) {
  return strlen(w);
}
