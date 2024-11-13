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

// Last modified: 2024-10-27

#if !defined(R_FOREIGNPROCEDURE_H_INCLUDED)
#define R_FOREIGNPROCEDURE_H_INCLUDED

#include "R/Configure.h"

typedef void R_Type;

typedef void (*R_ForeignProcedureValue)();

#define R_ForeignProcedureValue_Null (NULL)

#define R_ForeignProcedureValue_NumberOfBytes (sizeof(void*))

#if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
  static_assert(R_ForeignProcedureValue_NumberOfBytes == 8, "R.ForeignProcedureValue.NumberOfBytes must be 8");
#elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
  static_assert(R_ForeignProcedureValue_NumberOfBytes == 4, "R.ForeignProcedureValue.NumberOfBytes must be 4");
#else
  #error("invalid/unknown value for R_Configuration_InstructionSetArchitecture")
#endif

#define R_ForeignProcedureValue_NumberOfBits (R_ForeignProcedureValue_NumberOfBytes * 8)

R_Type*
_R_ForeignProcedureValue_getType
  (
  );

#endif // R_FOREIGNPROCEDURE_H_INCLUDED
