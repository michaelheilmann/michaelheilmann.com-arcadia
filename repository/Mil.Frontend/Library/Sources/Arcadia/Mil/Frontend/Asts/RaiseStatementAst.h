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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_RAISESTATEMENTAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_RAISESTATEMENTAST_H_INCLUDED

#include "Arcadia/Mil/Frontend/Asts/StatementAst.h"
typedef struct Arcadia_Mil_OperandAst Arcadia_Mil_OperandAst;

/// @code
/// class Arcadia.Mil.RaiseStatementAst extends Arcadia.Mil.Statement
/// @endcode
/// Represents
/// @code
/// 'raise'
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Mil.RaiseStatementAst", Arcadia_Mil_RaiseStatementAst, u8"Arcadia.Mil.StatementAst");

struct Arcadia_Mil_RaiseStatementAst {
  Arcadia_Mil_StatementAst parent;
  Arcadia_Mil_OperandAst* operand;
};

/// @brief Create a Mil raise statement AST.
/// @return A pointer to this Mil raise statement AST.
Arcadia_Mil_RaiseStatementAst*
Arcadia_Mil_RaiseStatementAst_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_RAISESTATEMENTAST_H_INCLUDED
