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

#include "R/Mil/Asts/ModuleAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct()
/// @endcode
static void
R_Mil_ModuleAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Mil_ModuleAst_visit
  (
    Arcadia_Process* process,
    R_Mil_ModuleAst* self
  );

static const R_ObjectType_Operations _R_Mil_ModuleAst_objectTypeOperations = {
  .construct = &R_Mil_ModuleAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_ModuleAst_visit,
};

static const Arcadia_Type_Operations _R_Mil_ModuleAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ModuleAst_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"R.Mil.ModuleAst", R_Mil_ModuleAst, u8"R.Object", R_Object, &_R_Mil_ModuleAst_typeOperations);

static void
R_Mil_ModuleAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Mil_ModuleAst* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_ModuleAst_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->definitions = R_List_create(process);
  R_Object_setType(_self, _type);
}

static void
R_Mil_ModuleAst_visit
  (
    Arcadia_Process* process,
    R_Mil_ModuleAst* self
  )
{
  R_Object_visit(self->definitions);
}

R_Mil_ModuleAst*
R_Mil_ModuleAst_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Mil_ModuleAst* self = R_allocateObject(process, _R_Mil_ModuleAst_getType(process), 0, &argumentValues[0]);
  return self;
}

void
R_Mil_ModuleAst_appendDefinition
  (
    Arcadia_Process* process,
    R_Mil_ModuleAst* self,
    R_Mil_DefinitionAst* definition
  )
{ 
  R_List_appendObjectReferenceValue(process, self->definitions, (R_ObjectReferenceValue)definition);
}

Arcadia_SizeValue
R_Mil_ModuleAst_getNumberOfDefinitions
  (
    R_Mil_ModuleAst* self
  )
{ return R_List_getSize(self->definitions); }

R_Mil_DefinitionAst*
R_Mil_ModuleAst_getDefinitionAt
  (
    Arcadia_Process* process,
    R_Mil_ModuleAst* self,
    Arcadia_SizeValue index
  )
{
  R_Value definitionAstValue = R_List_getAt(process, self->definitions, index);
  R_Mil_DefinitionAst* definitionAst = R_Value_getObjectReferenceValue(&definitionAstValue);
  return definitionAst;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
