// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_MEMORY_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_MEMORY_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Annotations/NoReturn.h"

#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC
#include <stddef.h>
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Status.h"
#include "Arcadia/Ring1/Implementation/Value.h"

#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <setjmp.h>
typedef struct Arcadia_JumpTarget Arcadia_JumpTarget; // Forward declaration.
typedef struct Arcadia_Thread Arcadia_Thread; // Forward declaration.
typedef struct Arcadia_Process Arcadia_Process; // Forward declaration.

/// @brief Fill a memory region with a specified value.
/// @param process A pointer to the Arcadia_Process object
/// @param p The starting address of the memory region
/// @param n The size, in Bytes, of the memory region
/// @param v The value to assign to the Bytes of the memory region
/// @remarks @a p can be a null pointer
/// @error Arcadia_Status_ArgumentValueInvalid p + n overflows
void
Arcadia_Memory_fill
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n,
    uint8_t v
  );

/// @brief Copy the contents of a memory region to another memory region.
/// @param process A pointer to the Arcadia_Process object
/// @param p The starting address of the target memory region
/// @param q The starting address of the source memory region
/// @param n The size, in Bytes, of the memory regions
/// @remarks The memory regions may overlap.
/// @remarks @a p and/or q can be a null pointers
/// @error Arcadia_Status_ArgumentValueInvalid p + n overflows
/// @error Arcadia_Status_ArgumentValueInvalid q + n overflows
void
Arcadia_Memory_copy
  (
    Arcadia_Thread* thread,
    void* p,
    const void* q,
    size_t n
  );

Arcadia_Integer8Value
Arcadia_Memory_compare
  (
    Arcadia_Thread* thread,
    const void *p,
    const void* q,
    Arcadia_SizeValue n
  );

/// @brief
/// Allocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process object
/// @param p
/// A pointer to a <code>void*</code> variable.
/// @param n
/// The size, in Bytes, of the memory region to allocate.
/// @post
/// On success, <code>*p</code> was assigned a pointer to a memory region of @a n Bytes.
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a p is a null pointer
/// @error #Arcadia_Status_AllocationFailed
/// the allocation failed
void*
Arcadia_Memory_allocateUnmanaged
  (
    Arcadia_Thread* thread,
    size_t n
  );

/// @brief
/// Deallocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process object
/// @param p
/// A pointer to a memory region of @a n Bytes.
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a p is a null pointer
void
Arcadia_Memory_deallocateUnmanaged
  (
    Arcadia_Thread* thread,
    void* p
  );

/// @brief
/// Reallocate unmanaged memory.
/// @param process
/// A pointer to the Arcadia_Process object
/// @param p A pointer to a <code>void*</code> variable.
/// The variable points to the memory region to reallocate.
/// @param n
/// The size to reallocate the memory region to.
/// @post
/// On success, <code>*p</code> was assigned a pointer to a new memory region of @a n Bytes. The old memory region was deallocated.
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a p is a null pointer
/// @error #Arcadia_Status_ArgumentValueInvalid
/// @a *p is a null pointer
/// @error #Arcadia_Status_AllocationFailed
/// the allocation failed
/// @remarks O
void
Arcadia_Memory_reallocateUnmanaged
  (
    Arcadia_Thread* thread,
    void** p,
    size_t n
  );

/// p pointer to an array with elements a[0], ..., a[n]. Each element is 16 bit wide.
/// These value of the array are swapped such that a[i] = a[n - 1 - i] holds for all 0 <= i < n.
void
Arcadia_Process_reverseMemory16
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  );

/// p pointer to an array with elements a[0], ..., a[n]. Each element is 32 bit wide.
/// These value of the array are swapped such that a[i] = a[n - 1 - i] holds for all 0 <= i < n.
void
Arcadia_Memory_reverseMemory32
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  );

/// p pointer to an array with elements a[0], ..., a[n]. Each element is 64 bit wide.
/// These value of the array are swapped such that a[i] = a[n - 1 - i] holds for all 0 <= i < n.
void
Arcadia_Memory_reverseMemory64
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  );

/// p pointer to an array with elements a[0], ..., a[n]. Each element is 8 bit wide.
/// These value of the array are swapped such that a[i] = a[n - 1 - i] holds for all 0 <= i < n.
void
Arcadia_Memory_reverseMemory8
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  );

void
Arcadia_Memory_swap
  (
    Arcadia_Thread* thread,
    void* p,
    void* q,
    size_t n
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_MEMORY_H_INCLUDED
