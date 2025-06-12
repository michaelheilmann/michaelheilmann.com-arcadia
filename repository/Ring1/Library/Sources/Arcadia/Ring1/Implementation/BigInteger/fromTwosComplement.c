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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/toTwosComplement.h"

#include "Arcadia/Ring1/Include.h"
#include <assert.h>

void
Arcadia_BigInteger_fromTwosComplement
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger_Limp const* limps,
    Arcadia_SizeValue numberOfLimps
  )
{
  // Currently assumes and only supports little endian.
  Arcadia_BigInteger_Limp mostSignificandLimp = limps[numberOfLimps - 1];

  // If the most significand limp is zero, then the number is positive or zero.
  // We strip of trailing zero limps.
  if (mostSignificandLimp == 0) {
    while (numberOfLimps > 1 && limps[numberOfLimps - 1] == 0) {
      numberOfLimps--;
    }
    mostSignificandLimp = limps[numberOfLimps - 1];
    if (mostSignificandLimp == 0) {
      // The number is zero.
      Arcadia_BigInteger_setZero(thread, self);
    } else {
      // We can copy the limps.
      Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->limps, sizeof(Arcadia_BigInteger_Limp) * numberOfLimps);
      #if Arcadia_Configuration_BigInteger_LimpOrder == Arcadia_Configuration_BigInteger_LimpOrder_BigEndian
        Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), self->limps, limps, sizeof(Arcadia_BigInteger_Limp) * numberOfLimps);
        #if Arcadia_Configuration_BigInteger_LimpSize == 1
          Arcadia_Process_reverseMemory8(Arcadia_Thread_getProcess(thread), self->limps, numberOfLimps);
        #elif Arcadia_Configuration_BigInteger_LimpSize == 2
          Arcadia_Process_reverseMemory16(Arcadia_Thread_getProcess(thread), self->limps, numberOfLimps);
        #elif Arcadia_Configuration_BigInteger_LimpSize == 4
          Arcadia_Process_reverseMemory32(Arcadia_Thread_getProcess(thread), self->limps, numberOfLimps);
        #else
          #error("unknown/unsupported limp size")
        #endif
      #elif Arcadia_Configuration_BigInteger_LimpOrder == Arcadia_Configuration_BigInteger_LimpOrder_LittleEndian
        Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), self->limps, limps, sizeof(Arcadia_BigInteger_Limp) * numberOfLimps);
      #else
        #error("unknown/unsupported limp order")
      #endif
      self->numberOfLimps = numberOfLimps;
      self->sign = 1;
    }
  } else {
    Arcadia_BigInteger_Limp* p = NULL;
    Arcadia_SizeValue n = numberOfLimps;  
    Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &p, sizeof(Arcadia_BigInteger_Limp) * n);
    Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), p, limps, sizeof(Arcadia_BigInteger_Limp) * n);
    // The value is positive or negative.
    Arcadia_BooleanValue isNegative = mostSignificandLimp & (1 << (Arcadia_BigInteger_BitsPerLimp - 1));
    if (isNegative) {
      Arcadia_SizeValue i = 0;
      // copy the zero limps
      while (p[i] == 0) { // This is fine as there must be a at least one non-zero limp.
        i++;
      }
      p[i] = -(Arcadia_Integer32Value)p[i];
      i++;
      while (i < n) {
        p[i] = ~(p[i]);
      }
      if (p[n - 1] & (1 << (Arcadia_BigInteger_BitsPerLimp - 1)) == 0) {
        n++;
        Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &p, sizeof(Arcadia_BigInteger_Limp) * n);
        p[n - 1] = Arcadia_BigInteger_Limp_Maximum;
      }
    }
    self->sign = isNegative ? -1 : +1;
    self->limps = p;
    self->numberOfLimps = n;
  }
}
