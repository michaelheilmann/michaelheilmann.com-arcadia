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

#include "Tools/TemplateEngine/Ast.h"

static void
Ast_destruct
  (
    Arcadia_Thread* thread,
    Ast* self
  );

static void
Ast_visit
  (
    Arcadia_Thread* thread,
    Ast* self
  );

static void
Ast_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Ast_constructImpl,
  .destruct = &Ast_destruct,
  .visit = &Ast_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Tools.TemplateEngine.Ast", Ast, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Ast_destruct
  (
    Arcadia_Thread* thread,
    Ast* self
  )
{/*Intentionally empty.*/}

static void
Ast_visit
  (
    Arcadia_Thread* thread,
    Ast* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->argument) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->argument);
  }
}

static void
Ast_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Ast* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Ast_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->type = Arcadia_ArgumentsValidation_getInteger32Value(thread, &argumentValues[0]);
  _self->name = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_String_getType(thread));
  _self->argument = Arcadia_ArgumentsValidation_getObjectReferenceValueOrNull(thread, &argumentValues[2], _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

Ast*
Ast_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value type,
    Arcadia_String* name,
    Arcadia_String* argument
  )
{
  Arcadia_Value argumentValues[] = { Arcadia_Value_Initializer(),
                                     Arcadia_Value_Initializer(),
                                     Arcadia_Value_Initializer() };
  Arcadia_Value_setInteger32Value(&argumentValues[0], type);
  if (name) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[1], name);
  }
  if (argument) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[2], argument);
  }
  Ast* self = Arcadia_allocateObject(thread, _Ast_getType(thread), 3, &argumentValues[0]);
  return self;
}
