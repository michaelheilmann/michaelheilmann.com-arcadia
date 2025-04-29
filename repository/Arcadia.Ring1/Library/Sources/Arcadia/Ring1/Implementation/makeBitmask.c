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

// Last modified: 2025-01-26

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/makeBitmask.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_Natural16Value
Arcadia_makeBitmaskN16
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue i,
    Arcadia_SizeValue n
  )
{
  static const Arcadia_SizeValue width = 16;
  if (i >= width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // i = <width of type> - 1 and n = 1 is valid.
  if (i + n > width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // "mask" is initially empty.
  Arcadia_Natural8Value mask = 0;
  // set the to be cleared bits in "mask" to 1.
  for (Arcadia_SizeValue j = i, m = i + n; j < m; ++j) {
    mask |= UINT16_C(1) << (width - j - 1);
  }
  return mask;
}

Arcadia_Natural32Value
Arcadia_makeBitmaskN32
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue i,
    Arcadia_SizeValue n
  )
{
  static const Arcadia_SizeValue width = 32;
  if (i >= width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // i = <width of type> - 1 and n = 1 is valid.
  if (i + n > width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // "mask" is initially empty.
  Arcadia_Natural8Value mask = 0;
  // set the to be cleared bits in "mask" to 1.
  for (Arcadia_SizeValue j = i, m = i + n; j < m; ++j) {
    mask |= UINT32_C(1) << (width - j - 1);
  }
  return mask;
}

Arcadia_Natural64Value
Arcadia_makeBitmaskN64
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue i,
    Arcadia_SizeValue n
  )
{
  static const Arcadia_SizeValue width = 64;
  if (i >= width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // i = <width of type> - 1 and n = 1 is valid.
  if (i + n > width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // "mask" is initially empty.
  Arcadia_Natural8Value mask = 0;
  // set the to be cleared bits in "mask" to 1.
  for (Arcadia_SizeValue j = i, m = i + n; j < m; ++j) {
    mask |= UINT64_C(1) << (width - j - 1);
  }
  return mask;
}

Arcadia_Natural8Value
Arcadia_makeBitmaskN8
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue i,
    Arcadia_SizeValue n
  )
{
  static const Arcadia_SizeValue width = 8;
  if (i >= width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // i = <width of type> - 1 and n = 1 is valid.
  if (i + n > width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  // "mask" is initially empty.
  Arcadia_Natural8Value mask = 0;
  // set the to be cleared bits in "mask" to 1.
  for (Arcadia_SizeValue j = i, m = i + n; j < m; ++j) {
    mask |= UINT8_C(1) << (width - j - 1);
  }
  return mask;
}
