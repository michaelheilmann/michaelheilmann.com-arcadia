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

#include "Arcadia/MIL/Frontend/Asts/ModuleAst.h"

#include "Arcadia/MIL/Frontend/Include.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct()
/// @endcode
static void
Arcadia_MIL_ModuleAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_ModuleAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ModuleAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_ModuleAst_objectTypeOperations = {
  .construct = &Arcadia_MIL_ModuleAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_ModuleAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_ModuleAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_ModuleAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.ModuleAst", Arcadia_MIL_ModuleAst,
                         u8"Arcadia.MIL.Ast", Arcadia_MIL_Ast,
                         &_Arcadia_MIL_ModuleAst_typeOperations);

static void
Arcadia_MIL_ModuleAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_ModuleAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_ModuleAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->path = NULL;
  _self->definitions = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_MIL_ModuleAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ModuleAst* self
  )
{
  if (self->path) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->path);
  }
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitions);
}

Arcadia_MIL_ModuleAst*
Arcadia_MIL_ModuleAst_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_ModuleAst);
}

void
Arcadia_MIL_ModuleAst_appendDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ModuleAst* self,
    Arcadia_MIL_DefinitionAst* definition
  )
{
  Arcadia_List_insertBackObjectReferenceValue(thread, self->definitions, (Arcadia_ObjectReferenceValue)definition);
}

Arcadia_SizeValue
Arcadia_MIL_ModuleAst_getNumberOfDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ModuleAst* self
  )
{ return Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->definitions); }

Arcadia_MIL_DefinitionAst*
Arcadia_MIL_ModuleAst_getDefinitionAt
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ModuleAst* self,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value definitionAstValue = Arcadia_List_getAt(thread, self->definitions, index);
  Arcadia_MIL_DefinitionAst* definitionAst = Arcadia_Value_getObjectReferenceValue(&definitionAstValue);
  return definitionAst;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
