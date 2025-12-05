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

#include "Arcadia/DDLS/Symbols/Scope.h"

static void
Arcadia_DDLS_Scope_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Scope* self
  );

static void
Arcadia_DDLS_Scope_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Scope* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_DDLS_Scope_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DDLS_Scope_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_DDLS_Scope_visitImpl,
};

static const Arcadia_Type_Operations _Arcadia_DDLS_Scope_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_DDLS_Scope_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DDLS.Scope", Arcadia_DDLS_Scope,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_DDLS_Scope_typeOperations);

static void
Arcadia_DDLS_Scope_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Scope* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DDLS_Scope_getType(thread);
  //
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  Arcadia_Value v = Arcadia_ValueStack_getValue(thread, 1);
  if (Arcadia_Value_isInstanceOf(thread, &v, _Arcadia_DDLS_Scope_getType(thread))) {
    self->enclosing = (Arcadia_DDLS_Scope*)Arcadia_Value_getObjectReferenceValue(&v);
  } else if (Arcadia_Value_isInstanceOf(thread, &v, _Arcadia_VoidValue_getType(thread))) {
    self->enclosing = NULL;
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->symbols = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_DDLS_Scope_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Scope* self
  )
{
  if (self->symbols) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->symbols);
  }
  if (self->enclosing) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->enclosing);
  }
}

Arcadia_DDLS_Scope*
Arcadia_DDLS_Scope_create
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Scope* enclosing
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (enclosing) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)enclosing);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_DDLS_Scope);
}
