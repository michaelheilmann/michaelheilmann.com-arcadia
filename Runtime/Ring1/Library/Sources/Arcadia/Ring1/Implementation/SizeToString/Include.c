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
#include "Arcadia/Ring1/Implementation/NaturalToString/Include.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_SizeValue_toUtf8String
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue sizeValue,
    void* context,
    void (*function)(Arcadia_Thread* thread, void* context, const Arcadia_Natural8Value* bytes, Arcadia_SizeValue numberOfBytes)
  )
{
#if Arcadia_Configuration_InstructionSetArchitecture_X64 == Arcadia_Configuration_InstructionSetArchitecture
  Arcadia_Natural64Value_toUtf8String(thread, sizeValue, context, function);
#elif Arcadia_Configuration_InstructionSetArchitecture_X86 == Arcadia_Configuration_InstructionSetArchitecture
  Arcadia_Natural32Value_toUtf8String(thread, sizeValue, context, function);
#else
  #error("environemnt not (yet) supported");
#endif
}
