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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_PROCEDUREDEFINITIONAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_PROCEDUREDEFINITIONAST_H_INCLUDED

#include "Arcadia/MIL/Frontend/Asts/Ast.h"

/// @code
/// class Arcadia.MIL.ProcedureDefinitionAst extends Arcadia.MIL.Ast
/// @endcode
/// Represents
/// @code
/// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters
///                     | 'procedure' 'entry'? name procedureParameters procedureBody
/// procedureBody : '{' statements '}'
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.ProcedureDefinitionAst", Arcadia_MIL_ProcedureDefinitionAst,
                          u8"Arcadia.MIL.Ast");

struct Arcadia_MIL_ProcedureDefinitionAst {
  Arcadia_MIL_Ast _parent;
  Arcadia_BooleanValue entry;
  Arcadia_String* nativeName;
  Arcadia_String* procedureName;
  Arcadia_List* procedureParameters;
  Arcadia_List* procedureBody;
};

/// @brief Create a MIL procedure definition AST.
/// @return A pointer to this MIL procedure definition AST.
Arcadia_MIL_ProcedureDefinitionAst*
Arcadia_MIL_ProcedureDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue entry,
    Arcadia_String* nativeName,
    Arcadia_String* procedureName,
    Arcadia_List* procedureParameters,
    Arcadia_List* procedureBody
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_PROCEDUREDEFINITIONAST_H_INCLUDED
