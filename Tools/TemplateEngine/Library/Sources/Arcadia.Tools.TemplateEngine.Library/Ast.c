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

#include "Arcadia.Tools.TemplateEngine.Library/Ast.h"

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
    Ast* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Ast_constructImpl,
  .destruct = &Ast_destruct,
  .visit = &Ast_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.TemplateEngine.Ast", Ast,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

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
  if (self->arguments) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->arguments);
  }
}

static void
Ast_constructImpl
  (
    Arcadia_Thread* thread,
    Ast* self
  )
{
  Arcadia_TypeValue _type = _Ast_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->type = Arcadia_ValueStack_getInteger32Value(thread, 2);
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  self->arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 3);
}

Ast*
Ast_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value type,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, type);
  if (name) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Ast);
}
