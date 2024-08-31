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

// Last modified: 2024-09-06

#if !defined(R_FOREIGNFUNCTION_H_INCLUDED)
#define R_FOREIGNFUNCTION_H_INCLUDED

typedef void (*R_ForeignFunctionReferenceValue)();

#define R_ForeignFunctionReferenceValue_Null (NULL)

#define R_ForeignFunctionReferenceValue_NumberOfBytes (sizeof(void*))

#if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
static_assert(R_ForeignFunctionReferenceValue_NumberOfBytes == 8, "R.ForeignFunctionReferenceValue.NumberOfBytes must be 8");
#elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
static_assert(R_ForeignFunctionReferenceValue_NumberOfBytes == 4, "R.ForeignFunctionReferenceValue.NumberOfBytes must be 4");
#else
#error("invalid/unknown value for R_Configuration_InstructionSetArchitecture")
#endif

#define R_ForeignFunctionReferenceValue_NumberOfBits (R_ForeignFunctionReferenceValue_NumberOfBytes * 8)

#endif // R_FOREIGNFUNCTION_H_INCLUDED
