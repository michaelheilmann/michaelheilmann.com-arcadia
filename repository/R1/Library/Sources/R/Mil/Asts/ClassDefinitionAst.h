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

#if !defined(R_MIL_ASTS_CLASSDEFINITIONAST_H_INCLUDED)
#define R_MIL_ASTS_CLASSDEFINITIONAST_H_INCLUDED

#include "R.h"
#include "R/Mil/Asts/DefinitionAst.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ClassDefinitionAst extends R.Mil.DefinitionAst {
///   construct(className:R.String, extendedClassName:R.String, classBody:R.List)
/// }
/// @endcode
/// Represents
/// @code
/// classDefinition : 'class' name ('extends' name)? classBody
/// classBody : '{' classMemberDefinition* '}'
/// @endcode
Rex_declareObjectType(u8"R.Mil.ClassDefinitionAst", R_Mil_ClassDefinitionAst, u8"R.Mil.DefinitionAst");

struct R_Mil_ClassDefinitionAst {
  R_Mil_DefinitionAst _parent;
  R_String* className;
  R_String* extendedClassName;
  R_List* classBody;
};

/// @brief Create a MIL class definition AST.
/// @return A pointer to this MIL class definition AST.
R_Mil_ClassDefinitionAst*
R_Mil_ClassDefinitionAst_create
  (
    Arcadia_Process* process,
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_ASTS_CLASSDEFINITIONAST_H_INCLUDED
