// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// assert
#include <assert.h>

// FILE, stdout, stderr, (v)fprintf
#include <stdio.h>

// va_list, va_start, va_aend
#include <stdarg.h>

// https://en.cppreference.com/w/c/error/assert
#define c_assert(expression) assert(expression)

// https://en.cppreference.com/w/c/program/exit
__declspec(noreturn) void c_exit(int code);

// https://en.cppreference.com/w/c/string/byte/memcpy
void* c_memcpy(void* restrict dst, const void* restrict src, size_t count);

// https://en.cppreference.com/w/c/string/byte/memmove
void* c_memmove(void* dst, const void* src, size_t count);

// https://en.cppreference.com/w/c/string/byte/memcmp
int c_memcmp(const void* lhs, const void* rhs, size_t count);

// https://en.cppreference.com/w/c/io/fprintf
int c_fprintf(FILE* restrict stream, const char* restrict format, ...);

// https://en.cppreference.com/w/c/io/vfprintf
int c_vfprintf(FILE* restrict stream, const char* restrict format, va_list arguments);

// https://en.cppreference.com/w/c/memory/malloc
void* c_malloc(size_t size);

// https://en.cppreference.com/w/c/memory/realloc
void* c_realloc(void* ptr, size_t new_size);

// https://en.cppreference.com/w/c/memory/free
void c_free(void* ptr);

// https://en.cppreference.com/w/c/string/byte/strlen
size_t c_strlen(const char *w);

/// @since 1.0
/// @brief
/// Function annotation indicating indicating its return value shall be used.
#if defined(C_WARN_UNUSED_RETURN_VALUE)
  #error("C_WARN_UNUSED_RETURN_VALUE() already defined")
#endif
#if R_Configuration_CompilerC_Gcc == R_Configuration_CompilerC || \
    R_Configuration_CompilerC_Clang == R_Configuration_CompilerC
  #define C_WARN_UNUSED_RETURN_VALUE() __attribute__((warn_unused_result))
#elif R_Configuration_CompilerC_Msvc == R_Configuration_CompilerC
  #include <sal.h>
  #define C_WARN_UNUSED_RETURN_VALUE() _Check_return_
#else
  #define C_WARN_UNUSED_RETURN_VALUE()
#endif

/// @since 1.0
/// @brief
/// Function annotation indicating a function does not return normally.
#if defined(C_NO_RETURN)
  #error("C_NO_RETURN() already defined")
#endif
#if R_Configuration_CompilerC_Msvc == R_Configuration_CompilerC
  #define C_NO_RETURN() __declspec(noreturn)
#else
  #define C_NO_RETURN()
#endif

#include <stdbool.h>

/**
 * @brief Perform safe addition.
 * @param a The 1st operand.
 * @param b The 2nd operand.
 * @param result A pointer to the result variable.
 * @return @a true if there was an overflow, @a false otherwise.
 */
bool c_safe_add_sz(size_t a, size_t b, size_t* r);

/**
 * @brief Perform safe addition.
 * @param a The 1st operand.
 * @param b The 2nd operand.
 * @param result A pointer to the result variable.
 * @return @a true if there was an overflow, @a false otherwise.
 */
bool c_safe_mul_sz(size_t a, size_t b, size_t* r);

#endif // R_CSTDLIB_H_INCLUDED
