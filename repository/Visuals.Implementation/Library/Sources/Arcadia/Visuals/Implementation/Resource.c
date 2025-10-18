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

#include "Arcadia/Visuals/Implementation/Resource.h"

#include "Arcadia/Visuals/Implementation/BackendContext.h"

static void
Arcadia_Visuals_Implementation_Resource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  );

static void
Arcadia_Visuals_Implementation_Resource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  );

static void
Arcadia_Visuals_Implementation_Resource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_Implementation_Resource_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Visuals_Implementation_Resource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_Resource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_Resource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_Resource_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->context = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Implementation_BackendContext_getType(thread));
  self->referenceCount = 0;
  self->unload = NULL;
  self->unlink = NULL;
  self->render = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_Resource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_Resource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  )
{/*Intentionally empty.*/}

void
Arcadia_Visuals_Implementation_Resource_unload
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  )
{ self->unload(thread, self); }

void
Arcadia_Visuals_Implementation_Resource_unlink
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  )
{ self->unlink(thread, self); }

void
Arcadia_Visuals_Implementation_Resource_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  )
{ self->render(thread, self); }
