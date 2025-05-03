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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_JUMPSTATEMENTAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_JUMPSTATEMENTAST_H_INCLUDED

#include "Arcadia/Mil/Frontend/Asts/StatementAst.h"
typedef struct Arcadia_Mil_LabelStatementAst Arcadia_Mil_LabelStatementAst;

/// @todo Use Arcadia_(declare/defined)EnumerationType.
typedef enum Arcadia_Mil_JumpStatementAstType Arcadia_Mil_JumpStatementAstType;

enum Arcadia_Mil_JumpStatementAstType {
  Arcadia_Mil_JumpStatementAstType_Jump = 1,
  Arcadia_Mil_JumpStatementAstType_JumpIfTrue = 2,
  Arcadia_Mil_JumpStatementAstType_JumpIfFalse = 3,
};

/// @code
/// class Arcadia.Mil.JumpStatementAst extends Arcadia.Mil.Statement
/// @endcode
/// Represents
/// @code
/// jumpStatement : 'jump'
///               | ('jumpIfTrue' | 'jumpIfFalse') labelName
/// labelName : string
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Mil.JumpStatementAst", Arcadia_Mil_JumpStatementAst, u8"Arcadia.Mil.StatementAst");

struct Arcadia_Mil_JumpStatementAst {
  Arcadia_Mil_StatementAst parent;
  Arcadia_Integer32Value type;
  /// The name of the label.
  Arcadia_String* labelName;
  /// The AST of the label if resolution of the label name was successful.
  /// NULL otherwise.
  Arcadia_Mil_LabelStatementAst* labelAst;
};

/// @brief Create a Mil jump statement AST.
/// @return A pointer to this Mil jump statement AST.
Arcadia_Mil_JumpStatementAst*
Arcadia_Mil_JumpStatementAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_JumpStatementAstType type,
    Arcadia_String* labelName
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_JUMPSTATEMENTAST_H_INCLUDED
