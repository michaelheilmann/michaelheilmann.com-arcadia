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

c_noreturn() void c_exit(int code) {
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

int c_fprintf(FILE* restrict stream, const char* restrict format, ...) {
  va_list arguments;
  va_start(arguments, format);
  int result = vfprintf(stream, format, arguments);
  va_end(arguments);
  return result;
}

int c_vfprintf(FILE* restrict stream, const char* restrict format, va_list arguments) {
  return vfprintf(stream, format, arguments);
}

void* c_malloc(size_t size) {
  return malloc(size > 0 ? size : 1);
}

void* c_realloc(void* ptr, size_t new_size) {
  return realloc(ptr, new_size > 0 ? new_size : 1);
}

void c_free(void* ptr) {
  free(ptr);
}

#include <stdint.h>
#include "R/Configure.h"

#if R_Configuration_CompilerC == R_Configuration_CompilerC_Msvc
  #include <intrin.h>
#endif

bool c_safe_add_sz(size_t a, size_t b, size_t* r) {
  #if R_Configuration_CompilerC == R_Configuration_CompilerC_Msvc
    #if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
      c_static_assert(SIZE_MAX == UINT64_MAX && sizeof(size_t) == sizeof(uint64_t), "environment not (yet) supported");
      size_t t = _umul128(a, b, r);
      return 0 != t;
    #elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
      c_static_assert(SIZE_MAX == UINT32_MAX && sizeof(size_t) == sizeof(uint32_t), "environment not (yet) supported");
      int64_t t = a * b;
      *r = (size_t)t;
      return t > SIZE_MAX;
    #else
      #error ("environemnt not (yet) supported");
    #endif
  #else
    // This builtin function returns false if there was no overflow and true if there was an overflow.
    return __builtin_add_overflow(a, b, r);
  #endif
}

bool c_safe_mul_sz(size_t a, size_t b, size_t* r) {
  #if R_Configuration_CompilerC == R_Configuration_CompilerC_Msvc
    #if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
      c_static_assert(SIZE_MAX == UINT64_MAX && sizeof(size_t) == sizeof(uint64_t), "environment not (yet) supported");
      size_t t = _umul128(a, b, r);
      return 0 != t;
    #elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
      c_static_assert(SIZE_MAX == UINT32_MAX && sizeof(size_t) == sizeof(uint32_t), "environment not (yet) supported");
      int64_t t = a * b;
      *r = (size_t)t;
      return t > SIZE_MAX;
    #else
      #error ("environemnt not (yet) supported");
    #endif
  #else
    // This builtin function returns false if there was no overflow and true if there was an overflow.
    return __builtin_mul_overflow(a, b, r);
  #endif
}

size_t c_strlen(const char* w) {
  return strlen(w);
}
