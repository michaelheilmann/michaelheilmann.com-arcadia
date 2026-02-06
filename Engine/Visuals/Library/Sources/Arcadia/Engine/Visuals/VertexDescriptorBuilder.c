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
#include "Arcadia/Engine/Visuals/VertexDescriptorBuilder.h"

#include "Arcadia/Engine/Visuals/VertexDescriptor.module.h"

static void
Arcadia_Engine_Visuals_VertexDescriptorBuilder_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorBuilder* self
  );

static void
Arcadia_Engine_Visuals_VertexDescriptorBuilder_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorBuilderDispatch* self
  );

static void
Arcadia_Engine_Visuals_VertexDescriptorBuilder_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorBuilder* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Visuals_VertexDescriptorBuilder_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Engine_Visuals_VertexDescriptorBuilder_construct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_VertexDescriptorBuilder_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Visuals_VertexDescriptorBuilder_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Visuals_VertexDescriptorBuilder_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcardia.Engine.Visuals.VertexDescriptorBuilder", Arcadia_Engine_Visuals_VertexDescriptorBuilder,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Engine_Visuals_VertexDescriptorBuilder_typeOperations);

static void
Arcadia_Engine_Visuals_VertexDescriptorBuilder_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorBuilder* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_VertexDescriptorBuilder_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->stride = Arcadia_SizeValue_Literal(0);
  self->vertexElementDescriptors = (Arcadia_List*)Arcadia_ArrayList_create(thread);

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Engine_Visuals_VertexDescriptorBuilder_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorBuilderDispatch* self
  )
{ }

static void
Arcadia_Engine_Visuals_VertexDescriptorBuilder_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorBuilder* self
  )
{
  if (self->vertexElementDescriptors) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexElementDescriptors);
  }
}

Arcadia_Engine_Visuals_VertexDescriptorBuilder*
Arcadia_Engine_Visuals_VertexDescriptorBuilder_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Visuals_VertexDescriptorBuilder);
}

Arcadia_Engine_Visuals_VertexDescriptor*
Arcadia_Engine_Visuals_VertexDescriptorBuilder_build
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_VertexDescriptorBuilder* self
  )
{
  Arcadia_SizeValue stride = 0;
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->vertexElementDescriptors); i < n; ++i) {
    Arcadia_Engine_Visuals_VertexElementDescriptor* vertexElementDescriptor = (Arcadia_Engine_Visuals_VertexElementDescriptor*)Arcadia_List_getObjectReferenceValueAt(thread, self->vertexElementDescriptors, i);
    Arcadia_SizeValue newStride = vertexElementDescriptor->offset;
    switch (vertexElementDescriptor->syntactics) {
      case Arcadia_Engine_Visuals_VertexElementSyntactics_Real32: {
        newStride += 1 * sizeof(Arcadia_Real32Value);
      } break;
      case Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32: {
        newStride += 2 * sizeof(Arcadia_Real32Value);
      } break;
      case Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32Real32: {
        newStride += 3 * sizeof(Arcadia_Real32Value);
      } break;
      case Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32Real32Real32: {
        newStride += 4 * sizeof(Arcadia_Real32Value);
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
    if (newStride > stride) {
      stride = newStride;
    }
  };
  Arcadia_ImmutableList* vertexElementDescriptors = (Arcadia_ImmutableList*)Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(self->vertexElementDescriptors));
  Arcadia_Engine_Visuals_VertexDescriptor* vertexDescriptor = Arcadia_Engine_Visuals_VertexDescriptor_create(thread, stride, vertexElementDescriptors);
  return vertexDescriptor;
}
