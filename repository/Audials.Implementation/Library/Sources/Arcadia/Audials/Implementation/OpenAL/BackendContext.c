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

#define ARCADIA_AUDIALS_IMPLEMENTATION_PRIVATE (1)
#include "Arcadia/Audials/Implementation/OpenAL/BackendContext.h"

#include "Arcadia/Audials/Implementation/Configure.h"
#include "Arcadia/Audials/Implementation/OpenAL/Backend.h"
#include "Arcadia/Audials/Implementation/OpenAL/Resources/SoundSourceResource.h"
#include "Arcadia/Audials/Implementation/Synthesis/sine.h"
#include <assert.h>

static Arcadia_Audials_Implementation_OpenAL_BackendContext* g_instance = NULL;

// @brief Update resources.
// @remmarks
// If a resource has a reference count of 0
// - unload the resource
// - unlink the resource
// - remove the resource from the list
// @return The number of removed resources
static Arcadia_SizeValue
Arcadia_Audials_Implementation_OpenAL_BackendContext_updateResourcesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self,
    Arcadia_BooleanValue force
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static Arcadia_Audials_Implementation_OpenAL_SoundSourceResource*
Arcadia_Audials_Implementation_OpenAL_BackendContext_createSoundSourceResouceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContextDispatch* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_BackendContext_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_BackendContext_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Audials_Implementation_OpenAL_BackendContext_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Audials.Implementation.OpenAL.BackendContext", Arcadia_Audials_Implementation_OpenAL_BackendContext,
                         u8"Arcadia.Audials.Implementation.BackendContext", Arcadia_Audials_Implementation_BackendContext,
                         &_typeOperations);

static Arcadia_SizeValue
Arcadia_Audials_Implementation_OpenAL_BackendContext_updateResourcesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self,
    Arcadia_BooleanValue force
  )
{
  Arcadia_SizeValue removed = 0;
  Arcadia_SizeValue removedNow = 0;
  do {
    removedNow = 0;
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)((Arcadia_Audials_Implementation_OpenAL_BackendContext*)self)->resources); i < n;) {
      Arcadia_Audials_Implementation_Resource* resource = (Arcadia_Audials_Implementation_Resource*)Arcadia_List_getObjectReferenceValueAt(thread, ((Arcadia_Audials_Implementation_OpenAL_BackendContext*)self)->resources, i);
      if (!resource->referenceCount || force) {
        Arcadia_Audials_Implementation_Resource_unload(thread, resource);
        Arcadia_Audials_Implementation_Resource_unlink(thread, resource);
        Arcadia_List_removeAt(thread, ((Arcadia_Audials_Implementation_OpenAL_BackendContext*)self)->resources, i, 1);
        n--;
        removedNow++;
      } else {
        i++;
      }
    }
    removed += removedNow;
  } while (removedNow);
  return removed;
}

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_updateImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{
  // (1) Update the resources.
  Arcadia_Audials_Implementation_OpenAL_BackendContext_updateResourcesImpl(thread, self, Arcadia_BooleanValue_False);
}

static Arcadia_Audials_Implementation_OpenAL_SoundSourceResource*
Arcadia_Audials_Implementation_OpenAL_BackendContext_createSoundSourceResouceImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{
  Arcadia_Audials_Implementation_OpenAL_SoundSourceResource* resource = Arcadia_Audials_Implementation_OpenAL_SoundSourceResource_create(thread, (Arcadia_Audials_Implementation_OpenAL_BackendContext*)self);
  assert(((Arcadia_Audials_Implementation_Resource*)resource)->referenceCount == 0);
  Arcadia_List_insertBackObjectReferenceValue(thread, self->resources, (Arcadia_Object*)resource);
  return resource;
}

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Audials_Implementation_OpenAL_BackendContext_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  // Create and lock the list of resources.
  self->resources = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_Object_lock(thread, (Arcadia_Object*)self->resources);

  self->alcDevice = NULL;
  self->alcContext = NULL;

  // Select the default audio device on the system.
  self->alcDevice = alcOpenDevice(NULL);
  if (!self->alcDevice) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  // Create a context on the device.
  self->alcContext = alcCreateContext(self->alcDevice, NULL);
  if (!self->alcContext) {
    alcCloseDevice(self->alcDevice);
    self->alcDevice = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  alcMakeContextCurrent(self->alcContext);
  if (alGetError()) {
    alcCloseDevice(self->alcDevice);
    self->alcDevice = NULL;
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

void
Arcadia_Audials_Implementation_OpenAL_BackendContext_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContextDispatch* self
  )
{
  ((Arcadia_Audials_Implementation_BackendContextDispatch*)self)->createSoundSourceResource = (Arcadia_Audials_Implementation_SoundSourceResource * (*)(Arcadia_Thread*, Arcadia_Audials_Implementation_BackendContext*)) & Arcadia_Audials_Implementation_OpenAL_BackendContext_createSoundSourceResouceImpl;
  ((Arcadia_Audials_BackendContextDispatch*)self)->update = (void(*)(Arcadia_Thread*, Arcadia_Audials_BackendContext*)) & Arcadia_Audials_Implementation_OpenAL_BackendContext_updateImpl;
}

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{
  // (1) Update resources until no resources are left.
  while (Arcadia_Audials_Implementation_OpenAL_BackendContext_updateResourcesImpl(thread, self, Arcadia_BooleanValue_True)) {
    /*Intentionally empty.*/
  }

  // Unlock the list of resources.
  Arcadia_Object_unlock(thread, (Arcadia_Object*)self->resources);
  self->resources = NULL;

  if (self->alcContext) {
    if (alcGetCurrentContext() == self->alcContext) {
      alcMakeContextCurrent(NULL);
    }
    if (self->alcContext) {
      alcDestroyContext(self->alcContext);
      self->alcContext = NULL;
    }
  }
  if (self->alcDevice) {
    alcCloseDevice(self->alcDevice);
    self->alcDevice = NULL;
  }
}

static void
Arcadia_Audials_Implementation_OpenAL_BackendContext_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_OpenAL_BackendContext* self
  )
{/*Intentionally empty.*/}

static void
destroyCallback
  (
    void* argument1,
    void* argument2
  )
{
  g_instance = NULL;
}

Arcadia_Audials_Implementation_OpenAL_BackendContext*
Arcadia_Audials_Implementation_OpenAL_BackendContext_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Audials_Implementation_OpenAL_BackendContext);
}

Arcadia_Audials_Implementation_OpenAL_BackendContext*
Arcadia_Audials_Implementation_OpenAL_BackendContext_getOrCreate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_instance) {
    Arcadia_Audials_Implementation_OpenAL_BackendContext* instance = Arcadia_Audials_Implementation_OpenAL_BackendContext_create(thread);
    Arcadia_Object_addNotifyDestroyCallback(thread, (Arcadia_Object*)instance, NULL, &destroyCallback);
    g_instance = instance;
  }
  return g_instance;
}
