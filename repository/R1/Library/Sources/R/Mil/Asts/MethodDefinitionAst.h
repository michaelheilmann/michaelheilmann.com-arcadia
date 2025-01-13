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

// Last modified: 2024-10-04

#if !defined(R_MIL_ASTS_METHODDEFINITIONAST_H_INCLUDED)
#define R_MIL_ASTS_METHODDEFINITIONAST_H_INCLUDED

#include "R.h"
#include "R/Mil/Asts/ClassMemberDefinitionAst.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType(u8"R.Mil.MethodDefinitionAst", R_Mil_MethodDefinitionAst, u8"R.Mil.ClassMemberDefinitionAst");

struct R_Mil_MethodDefinitionAst {
  R_Mil_ClassMemberDefinitionAst _parent;
  Arcadia_String* nativeName;
  Arcadia_String* methodName;
  R_List* methodParameters;
  R_List* methodBody;
};

R_Mil_MethodDefinitionAst*
R_Mil_MethodDefinitionAst_create
  (
    Arcadia_Process* process,
    Arcadia_String* nativeName,
    Arcadia_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_ASTS_METHODDEFINITIONAST_H_INCLUDED
