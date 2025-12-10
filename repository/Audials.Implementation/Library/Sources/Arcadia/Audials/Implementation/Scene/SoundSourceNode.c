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

#include "Arcadia/Audials/Implementation/Scene/SoundSourceNode.h"

#include "Arcadia/Audials/Implementation/Resource.h"
#include "Arcadia/Audials/Implementation/Resources/SoundSourceResource.h"
#include "Arcadia/Audials/Implementation/BackendContext.h"

#define VolumeDirty (1)

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  );

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNodeDispatch* self
  );

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  );

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  );

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  );

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self,
    Arcadia_Audials_Implementation_BackendContext* backendContext
  );

static Arcadia_BooleanValue
Arcadia_Audials_Implementation_Scene_SoundSourceNode_isPlayingImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  );

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_playImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  );

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_stopImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  );

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_setVolumeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self,
    Arcadia_Real32Value volume
  );

static Arcadia_Real32Value
Arcadia_Audials_Implementation_Scene_SoundSourceNode_getVolumeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Audials_Implementation_Scene_SoundSourceNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Audials_Implementation_Scene_SoundSourceNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Audials_Implementation_Scene_SoundSourceNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Audials.Implementation.Scene.SoundSourceNode", Arcadia_Audials_Implementation_Scene_SoundSourceNode,
                         u8"Arcadia.Audials.Scene.SoundSourceNode", Arcadia_Audials_Scene_SoundSourceNode,
                         &_typeOperations);

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Audials_Implementation_Scene_SoundSourceNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  //
  if (Arcadia_ValueStack_isVoidValue(thread, 1)) {
    self->backendContext = NULL;
  } else {
    self->backendContext = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Audials_Implementation_BackendContext_getType(thread));
    Arcadia_Object_lock(thread, (Arcadia_Object*)self->backendContext);
  }
  //
  self->soundSourceResource = NULL;
  //
  self->dirtyBits = VolumeDirty;
  //
  self->volume = 1.f;
  //
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNodeDispatch* self
  )
{
  ((Arcadia_Audials_Scene_NodeDispatch*)self)->render = (void (*)(Arcadia_Thread*, Arcadia_Audials_Scene_Node*)) & Arcadia_Audials_Implementation_Scene_SoundSourceNode_renderImpl;
  ((Arcadia_Audials_Scene_NodeDispatch*)self)->setBackendContext = (void (*)(Arcadia_Thread*, Arcadia_Audials_Scene_Node*, Arcadia_Audials_BackendContext*)) & Arcadia_Audials_Implementation_Scene_SoundSourceNode_setBackendContextImpl;
  //
  ((Arcadia_Audials_Scene_SoundSourceNodeDispatch*)self)->isPlaying = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*)) & Arcadia_Audials_Implementation_Scene_SoundSourceNode_isPlayingImpl;
  ((Arcadia_Audials_Scene_SoundSourceNodeDispatch*)self)->play = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*)) & Arcadia_Audials_Implementation_Scene_SoundSourceNode_playImpl;
  ((Arcadia_Audials_Scene_SoundSourceNodeDispatch*)self)->stop = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*)) & Arcadia_Audials_Implementation_Scene_SoundSourceNode_stopImpl;
  ((Arcadia_Audials_Scene_SoundSourceNodeDispatch*)self)->setVolume = (void(*)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*, Arcadia_Real32Value)) & Arcadia_Audials_Implementation_Scene_SoundSourceNode_setVolumeImpl;
  ((Arcadia_Audials_Scene_SoundSourceNodeDispatch*)self)->getVolume = (Arcadia_Real32Value(*)(Arcadia_Thread*, Arcadia_Audials_Scene_SoundSourceNode*)) & Arcadia_Audials_Implementation_Scene_SoundSourceNode_getVolumeImpl;
}

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  )
{
  if (self->backendContext) {
    if (self->soundSourceResource) {
      Arcadia_Audials_Implementation_Resource_unref(thread, (Arcadia_Audials_Implementation_Resource*)self->soundSourceResource);
      self->soundSourceResource = NULL;
    }
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
    self->backendContext = NULL;
  }
}

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  )
{
  if (self->soundSourceResource) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->soundSourceResource);
  }
  if (self->backendContext) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->backendContext);
  }
}

Arcadia_Audials_Implementation_Scene_SoundSourceNode*
Arcadia_Audials_Implementation_Scene_SoundSourceNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_BackendContext* backendContext
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (backendContext) Arcadia_ValueStack_pushObjectReferenceValue(thread, backendContext); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Audials_Implementation_Scene_SoundSourceNode);
}

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_renderImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  )
{
  if (self->backendContext) {
    if (!self->soundSourceResource) {
      Arcadia_Audials_Implementation_BackendContext* backendContext = self->backendContext;
      // (1) sound source
      self->soundSourceResource =
        Arcadia_Audials_Implementation_BackendContext_createSoundSourceResource
          (
            thread,
            backendContext
          );
      Arcadia_Audials_Implementation_Resource_ref(thread, (Arcadia_Audials_Implementation_Resource*)self->soundSourceResource);
    }
    Arcadia_Audials_Implementation_Resource_render(thread, (Arcadia_Audials_Implementation_Resource*)self->soundSourceResource);
    if (self->dirtyBits & VolumeDirty) {
      Arcadia_Audials_Implementation_SoundSourceResource_setVolume(thread, self->soundSourceResource, self->volume);
      self->dirtyBits &= ~VolumeDirty;
    }
  }
}

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_setBackendContextImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self,
    Arcadia_Audials_Implementation_BackendContext* backendContext
  )
{
  if (backendContext == self->backendContext) {
    // Only change something if the backend context changes.
    return;
  }
  if (backendContext) {
    Arcadia_Object_lock(thread, (Arcadia_Object*)backendContext);
  }
  if (self->backendContext) {
    Arcadia_Object_unlock(thread, (Arcadia_Object*)self->backendContext);
  }
  if (self->backendContext) {
    if (self->soundSourceResource) {
      Arcadia_Audials_Implementation_Resource_unref(thread, (Arcadia_Audials_Implementation_Resource*)self->soundSourceResource);
      self->soundSourceResource = NULL;
    }
  }
  self->backendContext = backendContext;
}

static Arcadia_BooleanValue
Arcadia_Audials_Implementation_Scene_SoundSourceNode_isPlayingImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  )
{
  if (!self->soundSourceResource) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return Arcadia_Audials_Implementation_SoundSourceResource_isPlaying(thread, self->soundSourceResource);
}

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_playImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  )
{
  if (!self->soundSourceResource) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (self->dirtyBits & VolumeDirty) {
    Arcadia_Audials_Implementation_SoundSourceResource_setVolume(thread, self->soundSourceResource, self->volume);
    self->dirtyBits &= ~VolumeDirty;
  }
  Arcadia_Audials_Implementation_SoundSourceResource_play(thread, self->soundSourceResource);
}

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_stopImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  )
{
  if (!self->soundSourceResource) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Audials_Implementation_SoundSourceResource_stop(thread, self->soundSourceResource);
}

static void
Arcadia_Audials_Implementation_Scene_SoundSourceNode_setVolumeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self,
    Arcadia_Real32Value volume
  )
{
  self->dirtyBits |= self->volume != volume ? VolumeDirty : 0;
  self->volume = volume;
}

static Arcadia_Real32Value
Arcadia_Audials_Implementation_Scene_SoundSourceNode_getVolumeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Audials_Implementation_Scene_SoundSourceNode* self
  )
{ return self->volume; }
