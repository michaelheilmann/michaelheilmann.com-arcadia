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

// Last modified: 2025-01-01

#if !defined(ARCADIA_RING1_IMPLEMENTATION_OBJECTREFERENCE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_OBJECTREFERENCE_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Configure.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"

typedef void* Arcadia_ObjectReferenceValue;

#define Arcadia_ObjectReferenceValue_Null (NULL)

#define Arcadia_ObjectReferenceValue_NumberOfBytes (sizeof(void*))

#if Arcadia_Configuration_InstructionSetArchitecture == Arcadia_Configuration_InstructionSetArchitecture_X64
  Arcadia_StaticAssert(Arcadia_ObjectReferenceValue_NumberOfBytes == 8, "Arcadia.ObjectReferenceValue.NumberOfBytes must be 8");
#elif Arcadia_Configuration_InstructionSetArchitecture == Arcadia_Configuration_InstructionSetArchitecture_X86
  Arcadia_StaticAssert(Arcadia_ObjectReferenceValue_NumberOfBytes == 4, "Arcadia.ObjectReferenceValue.NumberOfBytes must be 4");
#else
  #error("invalid/unknown value for Arcadia_Configuration_InstructionSetArchitecture")
#endif

#define Arcadia_ObjectReferenceValue_NumberOfBits (Arcadia_ObjectReferenceValue_NumberOfBytes * 8)

#endif // ARCADIA_RING1_IMPLEMENTATION_OBJECTREFERENCE_H_INCLUDED
