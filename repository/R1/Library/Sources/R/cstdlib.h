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

#if !defined(R_CSTDLIB_H_INCLUDED)
#define R_CSTDLIB_H_INCLUDED

#include "R/Configure.h"
#include "Arcadia/Ring1/Include.h"

// assert
#include <assert.h>

// jmp_buf, setjmp, longjmp
#include <setjmp.h>

// size_t
#include <stddef.h>

// SIZE_MAX
#include <stdint.h>

// FILE, stdout, stderr, (v)fprintf
#include <stdio.h>

// va_list, va_start, va_end
#include <stdarg.h>

// uintx_t, intx_t
#include <inttypes.h>

// UINTx_MAX, INTx_MIN, INTx_MAX
#include <limits.h>

// https://en.cppreference.com/w/c/error/assert
#define c_assert(expression) assert(expression)

// https://en.cppreference.com/w/c/program/exit
Arcadia_NoReturn() void c_exit(int code);

// https://en.cppreference.com/w/c/string/byte/memcpy
void* c_memcpy(void* restrict dst, const void* restrict src, size_t count);

// https://en.cppreference.com/w/c/string/byte/memmove
void* c_memmove(void* dst, const void* src, size_t count);

// https://en.cppreference.com/w/c/string/byte/memcmp
int c_memcmp(const void* lhs, const void* rhs, size_t count);

// https://en.cppreference.com/w/c/string/byte/strlen
size_t c_strlen(const char *w);

/// @since 1.0
/// @brief
/// Function annotation indicating indicating its return value shall be used.
#if defined(C_WARN_UNUSED_RETURN_VALUE)
  #error("C_WARN_UNUSED_RETURN_VALUE() already defined")
#endif
#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC || \
    Arcadia_Configuration_CompilerC_Clang == Arcadia_Configuration_CompilerC
  #define C_WARN_UNUSED_RETURN_VALUE() __attribute__((warn_unused_result))
#elif Arcadia_Configuration_CompilerC_Msvc == Arcadia_Configuration_CompilerC
  #include <sal.h>
  #define C_WARN_UNUSED_RETURN_VALUE() _Check_return_
#else
  #define C_WARN_UNUSED_RETURN_VALUE()
#endif

#endif // R_CSTDLIB_H_INCLUDED
