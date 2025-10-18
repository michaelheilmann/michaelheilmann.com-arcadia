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

#include "Arcadia/Engine/SystemEvent.h"

#include "Arcadia/Engine/System.h"

static const Arcadia_Type_Operations _Arcadia_Engine_SystemEventKind_typeOperations = {
  Arcadia_Type_Operations_Initializer,
};

Arcadia_defineEnumerationType(u8"Arcadia.Engine.SystemEventKind", Arcadia_Engine_SystemEventKind,
                              &_Arcadia_Engine_SystemEventKind_typeOperations);

static void
Arcadia_Engine_SystemEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_SystemEvent* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_SystemEvent_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Engine_SystemEvent_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _Arcadia_Engine_SystemEvent_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_SystemEvent_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.SystemEvent", Arcadia_Engine_SystemEvent,
                         u8"Arcadia.Engine.Event", Arcadia_Engine_Event,
                         &_Arcadia_Engine_SystemEvent_typeOperations);

static void
Arcadia_Engine_SystemEvent_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_SystemEvent* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_SystemEvent_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  Arcadia_ValueStack_popValues(thread, 1); // pop number of arguments
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural64Value(thread, Arcadia_ValueStack_getNatural64Value(thread, 2));
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  //
  self->kind = Arcadia_ValueStack_getInteger32Value(thread, 1);
  self->origin = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 0, _Arcadia_Engine_System_getType(thread));
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues);
}

Arcadia_Engine_SystemEvent*
Arcadia_Engine_SystemEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value timeStamp,
    Arcadia_Engine_SystemEventKind kind,
    Arcadia_Engine_System* origin
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural32Value(thread, timeStamp);
  Arcadia_ValueStack_pushInteger32Value(thread, kind);
  if (origin) Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)origin); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_SystemEvent);
}
