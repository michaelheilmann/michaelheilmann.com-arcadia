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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_CLASSDEFINITIONAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_CLASSDEFINITIONAST_H_INCLUDED

#include "Arcadia/MIL/Frontend/Asts/Ast.h"

/// @code
/// class Arcadia.MIL.ClassDefinitionAst extends Arcadia.MIL.Ast {
///   construct(className:Arcadia.String, extendedClassName:Arcadia.String, classBody:Arcadia.List)
/// }
/// @endcode
/// Represents
/// @code
/// classDefinition : 'class' name ('extends' name)? classBody
/// classBody : '{' classMemberDefinition* '}'
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.ClassDefinitionAst", Arcadia_MIL_ClassDefinitionAst,
                          u8"Arcadia.MIL.Ast");

struct Arcadia_MIL_ClassDefinitionAst {
  Arcadia_MIL_Ast _parent;
  Arcadia_String* className;
  Arcadia_String* extendedClassName;
  Arcadia_List* classBody;
};

/// @brief Create a MIL class definition AST.
/// @return A pointer to this MIL class definition AST.
Arcadia_MIL_ClassDefinitionAst*
Arcadia_MIL_ClassDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* className,
    Arcadia_String* extendedClassName,
    Arcadia_List* classBody
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_CLASSDEFINITIONAST_H_INCLUDED
