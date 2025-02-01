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

// Last modified: 2025-01-26

#if !defined(ARCADIA_RING1_SAFEMULTIPLY_H_INCLUDED)
#define ARCADIA_RING1_SAFEMULTIPLY_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"

#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Ring1/Implementation/Size.h"

void
Arcadia_safeMultiply_n16
  (
    Arcadia_Process1* process,
    Arcadia_Natural16Value multiplier,
    Arcadia_Natural16Value multiplicand,
    Arcadia_Natural16Value* productHigh,
    Arcadia_Natural16Value* productLow
  );

void
Arcadia_safeMultiply_n32
  (
    Arcadia_Process1* process,
    Arcadia_Natural32Value multiplier,
    Arcadia_Natural32Value multiplicand,
    Arcadia_Natural32Value* productHigh,
    Arcadia_Natural32Value* productLow
  );

#if Arcadia_Configuration_CompilerC_Msvc == Arcadia_Configuration_CompilerC && \
    Arcadia_Configuration_InstructionSetArchitecture_X64 == Arcadia_Configuration_InstructionSetArchitecture

void
Arcadia_safeMultiply_n64_x64msvc
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  );

#endif

#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_Compiler

void
Arcadia_safeMultiply_n64_gcc
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  );

#endif

void
Arcadia_safeMultiply_n64_default
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  );

void
Arcadia_safeMultiply_n64
  (
    Arcadia_Process1* process,
    Arcadia_Natural64Value multiplier,
    Arcadia_Natural64Value multiplicand,
    Arcadia_Natural64Value* productHigh,
    Arcadia_Natural64Value* productLow
  );

void
Arcadia_safeMultiply_n8
  (
    Arcadia_Process1* process,
    Arcadia_Natural8Value multiplier,
    Arcadia_Natural8Value multiplicand,
    Arcadia_Natural8Value* productHigh,
    Arcadia_Natural8Value* productLow
  );

void
Arcadia_safeMultiply_sz
  (
    Arcadia_Process1* process,
    Arcadia_SizeValue multiplier,
    Arcadia_SizeValue multiplicand,
    Arcadia_SizeValue* productHigh,
    Arcadia_SizeValue* productLow
  );

#endif // ARCADIA_RING1_SAFEMULTIPLY_H_INCLUDED
