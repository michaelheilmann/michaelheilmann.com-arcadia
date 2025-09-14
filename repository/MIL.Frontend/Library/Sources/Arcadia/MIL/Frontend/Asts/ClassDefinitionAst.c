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

#include "Arcadia/MIL/Frontend/Asts/ClassDefinitionAst.h"

#include "Arcadia/MIL/Frontend/Include.h"

static void
Arcadia_MIL_ClassDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_ClassDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ClassDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_ClassDefinitionAst_objectTypeOperations = {
  .construct = &Arcadia_MIL_ClassDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_ClassDefinitionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_ClassDefinitionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_ClassDefinitionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.ClassDefinitionAst", Arcadia_MIL_ClassDefinitionAst,
                         u8"Arcadia.MIL.Ast", Arcadia_MIL_Ast,
                         &_Arcadia_MIL_ClassDefinitionAst_typeOperations);

static void
Arcadia_MIL_ClassDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_ClassDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_ClassDefinitionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 3 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  _self->className = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_String_getType(thread));
  if (Arcadia_ValueStack_isObjectReferenceValue(thread, 2)) {
    _self->extendedClassName = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  } else if (Arcadia_ValueStack_isVoidValue(thread, 2)) {
    _self->extendedClassName = NULL;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->classBody = (Arcadia_List*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 3 + 1);
}

static void
Arcadia_MIL_ClassDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ClassDefinitionAst* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->className);
  if (self->extendedClassName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->extendedClassName);
  }
  if (self->classBody) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->classBody);
  }
}

Arcadia_MIL_ClassDefinitionAst*
Arcadia_MIL_ClassDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* className,
    Arcadia_String* extendedClassName,
    Arcadia_List* classBody
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (className) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, className);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (extendedClassName) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, extendedClassName);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  if (classBody) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, classBody);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_ClassDefinitionAst);
}
