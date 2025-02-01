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

// Last modified: 2024-10-27

#if !defined(ARCADIA_RING1_IMPLEMENTATION_FOREIGNPROCEDURE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_FOREIGNPROCEDURE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/_declareScalarType.h"
#include "Arcadia/Ring1/Implementation/Size.h"
typedef struct Arcadia_Value Arcadia_Value;

typedef void (Arcadia_ForeignProcedure)(Arcadia_Process* process, Arcadia_Value* targetValue, Arcadia_SizeValue numberOfArgumentValues, Arcadia_Value* argumentValues);

typedef Arcadia_ForeignProcedure* Arcadia_ForeignProcedureValue;

#define Arcadia_ForeignProcedureValue_Null (NULL)

#define Arcadia_ForeignProcedureValue_NumberOfBytes (sizeof(void*))

#if Arcadia_Configuration_InstructionSetArchitecture == Arcadia_Configuration_InstructionSetArchitecture_X64
  Arcadia_StaticAssert(Arcadia_ForeignProcedureValue_NumberOfBytes == 8, "Arcadia.ForeignProcedureValue.NumberOfBytes must be 8");
#elif Arcadia_Configuration_InstructionSetArchitecture == Arcadia_Configuration_InstructionSetArchitecture_X86
  Arcadia_StaticAssert(Arcadia_ForeignProcedureValue_NumberOfBytes == 4, "Arcadia.ForeignProcedureValue.NumberOfBytes must be 4");
#else
  #error("invalid/unknown value for Arcadia_Configuration_InstructionSetArchitecture")
#endif

#define Arcadia_ForeignProcedureValue_NumberOfBits (Arcadia_ForeignProcedureValue_NumberOfBytes * 8)

Rex_declareScalarType(Arcadia_ForeignProcedure);

#endif // ARCADIA_RING1_IMPLEMENTATION_FOREIGNPROCEDURE_H_INCLUDED
