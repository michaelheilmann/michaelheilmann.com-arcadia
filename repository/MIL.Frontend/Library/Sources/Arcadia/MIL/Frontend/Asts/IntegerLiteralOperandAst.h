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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_INTEGERLITERALOPERANDAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_INTEGERLITERALOPERANDAST_H_INCLUDED

#include "Arcadia/MIL/Frontend/Asts/OperandAst.h"

/// @code
/// class Arcadia.MIL.IntegerLiteralOperandAst extends Arcadia.MIL.OperandAst
/// @endcode
/// represents
/// @code
/// integerLiteral : lexicalAnalysis.integerLiteral
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.IntegerLiteralOperandAst", Arcadia_MIL_IntegerLiteralOperandAst,
                          u8"Arcadia.MIL.OperandAst");

struct Arcadia_MIL_IntegerLiteralOperandAst {
  Arcadia_MIL_OperandAst parent;
  Arcadia_String* value;
};

/// @undefined @a value is not an integer literal
Arcadia_MIL_IntegerLiteralOperandAst*
Arcadia_MIL_IntegerLiteralOperandAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* value
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_INTEGERLITERALOPERANDAST_H_INCLUDED
