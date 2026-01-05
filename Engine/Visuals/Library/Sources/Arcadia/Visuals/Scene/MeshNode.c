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
#include "Arcadia/Visuals/Scene/MeshNode.h"

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/VertexDescriptorBuilder.h"

#define Arcadia_Visuals_Scene_MeshNode_WithVertexColors (1)

static void
Arcadia_Visuals_Scene_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  );

static void
Arcadia_Visuals_Scene_MeshNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNodeDispatch* self
  );

static void
Arcadia_Visuals_Scene_MeshNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  );

static void
Arcadia_Visuals_Scene_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Scene_MeshNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Scene_MeshNode_destructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Scene.MeshNode", Arcadia_Visuals_Scene_MeshNode,
                         u8"Arcadia.Visuals.Scene.Node", Arcadia_Visuals_Scene_Node,
                         &_typeOperations);

static void
Arcadia_Visuals_Scene_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Scene_MeshNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Visuals_VertexDescriptorBuilder* vertexDescriptorBuilder = Arcadia_Visuals_VertexDescriptorBuilder_create(thread);

  Arcadia_List_insertBackObjectReferenceValue
    (
      thread,
      vertexDescriptorBuilder->vertexElementDescriptors,
      (Arcadia_ObjectReferenceValue)
      Arcadia_Visuals_VertexElementDescriptor_create
        (
          thread,
          sizeof(Arcadia_Real32Value) * 0,
          Arcadia_Visuals_VertexElementSemantics_PositionXYZ,
          Arcadia_Visuals_VertexElementSyntactics_Real32Real32Real32
        )
    );
#if Arcadia_Visuals_Scene_MeshNode_WithVertexColors == 1
  Arcadia_List_insertBackObjectReferenceValue
    (
      thread,
      vertexDescriptorBuilder->vertexElementDescriptors,
      (Arcadia_ObjectReferenceValue)
      Arcadia_Visuals_VertexElementDescriptor_create
        (
          thread,
          sizeof(Arcadia_Real32Value) * 3,
          Arcadia_Visuals_VertexElementSemantics_AmbientRGBA,
          Arcadia_Visuals_VertexElementSyntactics_Real32Real32Real32Real32
        )
    );
#endif
  self->material = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Visuals_Scene_MaterialNode_getType(thread));
  self->vertexDescriptor = Arcadia_Visuals_VertexDescriptorBuilder_build(thread, vertexDescriptorBuilder);
  self->baseColor = Arcadia_Math_Color4Real32_create4(thread, 1.f, 1.f, 1.f, 1.f);
  self->numberOfVertices = 3;
  Arcadia_SizeValue numberOfBytes = self->vertexDescriptor->stride * self->numberOfVertices;
  self->vertices = Arcadia_Memory_allocateUnmanaged(thread, numberOfBytes);
  Arcadia_ByteBuffer* temporary = Arcadia_ByteBuffer_create(thread);
  static const Arcadia_Real32Value POSITIONS[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
  };
  static const Arcadia_Real32Value COLORS[] = {
    1.f, 0.f, 0.f, 1.f,
    0.f, 1.f, 0.f, 1.f,
    0.f, 0.f, 1.f, 1.f,
  };
  Arcadia_ByteBuffer_clear(thread, temporary);
  for (Arcadia_SizeValue i = 0, n = 3; i < n; ++i) {
    Arcadia_ByteBuffer_insertBackBytes(thread, temporary, &POSITIONS[i * 3], sizeof(Arcadia_Real32Value) * 3);
  #if Arcadia_Visuals_Scene_MeshNode_WithVertexColors == 1
    Arcadia_ByteBuffer_insertBackBytes(thread, temporary, &COLORS[i * 4], sizeof(Arcadia_Real32Value) * 4);
  #endif
  }
  Arcadia_Memory_copy(thread, self->vertices, Arcadia_ByteBuffer_getBytes(thread, temporary),
                                              Arcadia_ByteBuffer_getNumberOfBytes(thread, temporary));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Scene_MeshNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNodeDispatch* self
  )
{ }

static void
Arcadia_Visuals_Scene_MeshNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  )
{
  if (self->material) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->material);
  }
  if (self->baseColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->baseColor);
  }
  if (self->vertexDescriptor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexDescriptor);
  }
}

static void
Arcadia_Visuals_Scene_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  )
{
  if (self->vertices) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->vertices);
    self->vertices = NULL;
  }
}

void
Arcadia_Visuals_Scene_MeshNode_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self,
    Arcadia_SizeValue* numberOfVertices
  )
{ *numberOfVertices = self->numberOfVertices; }

void
Arcadia_Visuals_Scene_MeshNode_setBaseColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self,
    Arcadia_Math_Color4Real32* baseColor
  )
{
  Arcadia_Math_Color4Real32_assign(thread, self->baseColor, baseColor);
}

Arcadia_Math_Color4Real32*
Arcadia_Visuals_Scene_MeshNode_getBaseColor
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Scene_MeshNode* self
  )
{
  return Arcadia_Math_Color4Real32_create4v(thread, self->baseColor->components);
}
