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

#if !defined(R_MIL_ASTS_MODULEAST_H_INCLUDED)
#define R_MIL_ASTS_MODULEAST_H_INCLUDED

#include "R.h"
#include "R/Mil/Asts/ClassDefinitionAst.h"
#include "R/Mil/Asts/ClassMemberDefinitionAst.h"
#include "R/Mil/Asts/ConstructorDefinitionAst.h"
#include "R/Mil/Asts/DefinitionAst.h"
#include "R/Mil/Asts/ExpressionAst.h"
#include "R/Mil/Asts/MethodDefinitionAst.h"
#include "R/Mil/Asts/StatementAst.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.ModuleAst
/// @endcode
/// @code
/// module : definition*
/// @endcode
Rex_declareObjectType(u8"R.Mil.ModuleAst", R_Mil_ModuleAst, u8"Arcadia.Object");

struct R_Mil_ModuleAst {
  Arcadia_Object _parent;
  R_List* definitions;
};

R_Mil_ModuleAst*
R_Mil_ModuleAst_create
  (
    Arcadia_Process* process
  );

void
R_Mil_ModuleAst_appendDefinition
  (
    Arcadia_Process* process,
    R_Mil_ModuleAst* self,
    R_Mil_DefinitionAst* definition
  );

Arcadia_SizeValue
R_Mil_ModuleAst_getNumberOfDefinitions
  (
    R_Mil_ModuleAst* self
  );

R_Mil_DefinitionAst*
R_Mil_ModuleAst_getDefinitionAt
  (
    Arcadia_Process* process,
    R_Mil_ModuleAst* self,
    Arcadia_SizeValue index
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_ASTS_MODULEAST_H_INCLUDED
