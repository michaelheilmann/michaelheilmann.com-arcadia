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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Engine/Visuals/VertexDescriptor.h"

static void
Arcadia_Engine_Visuals_VertexDescriptor_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptor* self
  );

static void
Arcadia_Engine_Visuals_VertexDescriptor_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorDispatch* self
  );

static void
Arcadia_Engine_Visuals_VertexDescriptor_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptor* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Visuals_VertexDescriptor_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Engine_Visuals_VertexDescriptor_construct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_VertexDescriptor_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Visuals_VertexDescriptor_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Visuals_VertexDescriptor_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcardia.Engine.Visuals.VertexDescriptor", Arcadia_Engine_Visuals_VertexDescriptor,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Engine_Visuals_VertexDescriptor_typeOperations);

static void
Arcadia_Engine_Visuals_VertexDescriptor_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptor* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_VertexDescriptor_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  
  self->stride = Arcadia_ValueStack_getSizeValue(thread, 2);
  self->vertexElementDescriptors = Arcadia_ValueStack_getObjectReferenceValue(thread, 1);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}

static void
Arcadia_Engine_Visuals_VertexDescriptor_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorDispatch* self
  )
{ }

static void
Arcadia_Engine_Visuals_VertexDescriptor_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptor* self
  )
{
  if (self->vertexElementDescriptors) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexElementDescriptors);
  }
}

Arcadia_Engine_Visuals_VertexDescriptor*
Arcadia_Engine_Visuals_VertexDescriptor_create
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue stride,
    Arcadia_ImmutableList* vertexElementDescriptors
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushSizeValue(thread, stride);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)vertexElementDescriptors);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_VertexDescriptor);
}
