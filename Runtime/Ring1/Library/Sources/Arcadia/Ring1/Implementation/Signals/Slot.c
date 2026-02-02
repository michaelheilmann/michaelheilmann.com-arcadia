// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Signals/Slot.h"

#include "Arcadia/Ring1/Implementation/Thread.h"
#include "Arcadia/Ring1/Implementation/ThreadExtensions.h"
#include "Arcadia/Ring1/Implementation/WeakReference.h"
#include "Arcadia/Ring1/Implementation/Signals/Signal.h"

#include "Arcadia/Ring1/Implementation/Signals/Internal.h"

static void
Arcadia_Slot_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Slot* self
  );

static void
Arcadia_Slot_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Slot* self
  );

static void
Arcadia_Slot_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Slot* self
  );

static void
Arcadia_Slot_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_SlotDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Slot_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*) & Arcadia_Slot_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_Slot_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Slot", Arcadia_Slot,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Slot_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Slot* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Slot_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Slot* self
  )
{
  if (self->signal) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->receiver);
  }
  if (self->receiver) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->receiver);
  }
}

static void
Arcadia_Slot_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Slot* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Slot_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (3 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  //
  self->signal = Arcadia_WeakReference_create(thread, Arcadia_Value_makeObjectReferenceValue(Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_Signal_getType(thread))));
  self->receiver = Arcadia_WeakReference_create(thread, Arcadia_Value_makeObjectReferenceValue(Arcadia_ValueStack_getObjectReferenceValue(thread, 2)));
  self->procedure = Arcadia_ValueStack_getForeignProcedureValue(thread, 1);
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Slot_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_SlotDispatch* self
  )
{ }

Arcadia_Slot*
Arcadia_Slot_create
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* signal,
    Arcadia_Object* receiver,
    Arcadia_ForeignProcedure* procedure
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)signal);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, receiver);
  Arcadia_ValueStack_pushForeignProcedureValue(thread, procedure);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_Slot);
}

void
Arcadia_Slot_disconnect
  (
    Arcadia_Thread* thread,
    Arcadia_Slot* self
  )
{
  self->signal = NULL;
  self->receiver = NULL;
  self->procedure = NULL;
}
