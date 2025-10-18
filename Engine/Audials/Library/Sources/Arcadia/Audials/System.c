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

#include "Arcadia/Audials/System.h"

#include "Arcadia/Engine/SystemEvent.h"
#include "Arcadia/Audials/BackendContext.h"

static void
Arcadia_Audials_System_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self
  );

static void
Arcadia_Audials_System_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self
  );

static Arcadia_Audials_BackendContext*
Arcadia_Audials_System_getBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self
  );

static void
Arcadia_Audials_System_setBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self,
    Arcadia_Audials_BackendContext* backendContext
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Audials_System_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Audials_System_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Audials.System", Arcadia_Audials_System,
                         u8"Arcadia.Engine.System", Arcadia_Engine_System,
                         &_typeOperations);

static void
Arcadia_Audials_System_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Audials_System_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->backendContext = NULL;
  self->playSine = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Audials_System_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self
  )
{/*Intentionally empty.*/}

static Arcadia_Audials_BackendContext*
Arcadia_Audials_System_getBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self
  )
{ return self->backendContext; }

static void
Arcadia_Audials_System_setBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self,
    Arcadia_Audials_BackendContext* backendContext
  )
{
  if (self->backendContext != backendContext) {
    Arcadia_Engine_SystemEvent_create(thread, Arcadia_TimeStamp_getNow(thread), Arcadia_Engine_ResourceEventKind_PreDetach, (Arcadia_Engine_System*)self);
    Arcadia_Engine_SystemEvent_create(thread, Arcadia_TimeStamp_getNow(thread), Arcadia_Engine_ResourceEventKind_PostAttach, (Arcadia_Engine_System*)self);
  }
}

void
Arcadia_Audials_System_playSine
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_System* self
  )
{ self->playSine(thread, self); }
