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
Arcadia_Mil_ModuleAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_ModuleAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ModuleAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_ModuleAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_ModuleAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_ModuleAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_ModuleAst_typeOperations = {
  .objectTypeOperations = &_Arcadia_Mil_ModuleAst_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.ModuleAst", Arcadia_Mil_ModuleAst, u8"Arcadia.Mil.Ast", Arcadia_Mil_Ast, &_Arcadia_Mil_ModuleAst_typeOperations);

static void
Arcadia_Mil_ModuleAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_ModuleAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_ModuleAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->path = NULL;
  _self->definitions = Arcadia_List_create(thread);
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Arcadia_Mil_ModuleAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ModuleAst* self
  )
{
  if (self->path) {
    Arcadia_Object_visit(thread, self->path);
  }
  Arcadia_Object_visit(thread, self->definitions);
}

Arcadia_Mil_ModuleAst*
Arcadia_Mil_ModuleAst_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_Mil_ModuleAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_ModuleAst_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_Mil_ModuleAst_appendDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ModuleAst* self,
    Arcadia_Mil_DefinitionAst* definition
  )
{ 
  Arcadia_List_appendObjectReferenceValue(thread, self->definitions, (Arcadia_ObjectReferenceValue)definition);
}

Arcadia_SizeValue
Arcadia_Mil_ModuleAst_getNumberOfDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ModuleAst* self
  )
{ return Arcadia_List_getSize(thread, self->definitions); }

Arcadia_Mil_DefinitionAst*
Arcadia_Mil_ModuleAst_getDefinitionAt
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ModuleAst* self,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value definitionAstValue = Arcadia_List_getAt(thread, self->definitions, index);
  Arcadia_Mil_DefinitionAst* definitionAst = Arcadia_Value_getObjectReferenceValue(&definitionAstValue);
  return definitionAst;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
