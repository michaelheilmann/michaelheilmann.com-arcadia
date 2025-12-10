// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/setPowerOfTwo.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_BigInteger_shiftLeftInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  )
{ Arcadia_BigInteger_shiftLeftInteger64(thread, self, other); }

void
Arcadia_BigInteger_shiftLeftInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  )
{ Arcadia_BigInteger_shiftLeftInteger64(thread, self, other); }

void
Arcadia_BigInteger_shiftLeftInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  )
{
  // If the integer is negative, then simply take its positive value and shift right.
  if (other < Arcadia_Integer64Value_Literal(0)) {
    if (other == Arcadia_Integer64Value_Minimum) {
      Arcadia_BigInteger_shiftRightNatural64(thread, self, ((Arcadia_Natural64Value)(-(other + 1))) + 1);
    } else {
      Arcadia_BigInteger_shiftRightNatural64(thread, self, (Arcadia_Natural64Value)(-other));
    }
  } else {
    Arcadia_BigInteger_shiftLeftNatural64(thread, self, (Arcadia_Natural64Value)other);
  }
}

void
Arcadia_BigInteger_shiftLeftInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  )
{ Arcadia_BigInteger_shiftLeftInteger64(thread, self, other); }

void
Arcadia_BigInteger_shiftLeftNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{ Arcadia_BigInteger_shiftLeftNatural64(thread, self, other); }

void
Arcadia_BigInteger_shiftLeftNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{ Arcadia_BigInteger_shiftLeftNatural64(thread, self, other); }

void
Arcadia_BigInteger_shiftLeftNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  )
{
  if (other == 0) {
    return;
  }
  if (Arcadia_BigInteger_isZero(thread, self)) {
    return;
  }
  Arcadia_SizeValue limpShift = other / Arcadia_BigInteger_BitsPerLimp;
  Arcadia_SizeValue bitShift = other % Arcadia_BigInteger_BitsPerLimp;

  Arcadia_SizeValue sourceIndex = self->numberOfLimps - 1;
  Arcadia_SizeValue targetIndex = sourceIndex + limpShift;

  Arcadia_SizeValue limpsToAllocate = self->numberOfLimps;
  Arcadia_SizeValue temporary;
  Arcadia_safeAddFullSizeValue(thread, limpsToAllocate, limpShift, &temporary, &limpsToAllocate);
  if (temporary) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }

  if (!bitShift) {
    // If the shift is limp-aligned.
    if (limpsToAllocate > Arcadia_BigInteger_MaximumNumberOfLimps) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Memory_reallocateUnmanaged(thread,
                                       &self->limps,
                                       sizeof(Arcadia_BigInteger_Limp) * (limpsToAllocate));
    // Shift the limps [0, n) up by limpShift.
    while (sourceIndex > 0) {
      self->limps[targetIndex] = self->limps[sourceIndex];
      --targetIndex;
      --sourceIndex;
    }
    self->limps[targetIndex] = self->limps[sourceIndex];
    self->numberOfLimps += limpShift;
    // Set the newly inserted limps [0, limpShift) inserted limps to 0.
    for (size_t i = 0; i < limpShift; ++i) {
      self->limps[i] = 0;
    }
  } else {
    // If the shift is not limp-aligned.
    targetIndex++;
    Arcadia_safeAddFullSizeValue(thread, limpsToAllocate, 1, &temporary, &limpsToAllocate);
    if (temporary) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (limpsToAllocate > Arcadia_BigInteger_MaximumNumberOfLimps) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Memory_reallocateUnmanaged(thread,
                                       &self->limps,
                                       sizeof(Arcadia_BigInteger_Limp) * (limpsToAllocate));

    //
    Arcadia_SizeValue lowBitsShift = (Arcadia_BigInteger_BitsPerLimp - bitShift);
    Arcadia_SizeValue highBits = 0;
    Arcadia_SizeValue block = self->limps[sourceIndex];
    //These are the bits from the source block which are added as the low bits to the target block.
    Arcadia_SizeValue lowBits = block >> lowBitsShift;
    while (sourceIndex > 0) {
      self->limps[targetIndex] = highBits | lowBits;
      highBits = block << bitShift;

      --sourceIndex;
      --targetIndex;

      block = self->limps[sourceIndex];
      lowBits = block >> lowBitsShift;
    }

    // Output the final blocks
    self->limps[targetIndex] = highBits | lowBits;
    self->limps[targetIndex - 1] = block << bitShift;

    self->numberOfLimps += limpShift + 1;

    // Set the newly inserted limps [0, numberOfLimpsToShift) inserted limps to 0.
    for (size_t i = 0; i < limpShift; ++i) {
      self->limps[i] = 0;
    }

    _Arcadia_BigInteger_stripLeadingZeroes(thread, &self->limps, &self->numberOfLimps);
    if (self->numberOfLimps == 0) self->sign = 0;
  }
}

void
Arcadia_BigInteger_shiftLeftNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{ Arcadia_BigInteger_shiftLeftNatural64(thread, self, other); }
