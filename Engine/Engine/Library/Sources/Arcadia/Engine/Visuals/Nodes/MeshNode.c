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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Visuals/Nodes/MeshNode.h"

#include "Arcadia/Engine/Include.h"
#include "Arcadia/Engine/Visuals/VertexDescriptorBuilder.h"

static void
Arcadia_Engine_Visuals_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self
  );

static void
Arcadia_Engine_Visuals_MeshNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNodeDispatch* self
  );

static void
Arcadia_Engine_Visuals_MeshNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self
  );

static void
Arcadia_Engine_Visuals_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_Visuals_MeshNode_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Visuals_MeshNode_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Visuals_MeshNode_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Visuals.MeshNode", Arcadia_Engine_Visuals_MeshNode,
                         u8"Arcadia.Engine.Visuals.Node", Arcadia_Engine_Visuals_Node,
                         &_typeOperations);

static void
Arcadia_Engine_Visuals_MeshNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Visuals_MeshNode_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  Arcadia_Engine_Visuals_VertexDescriptorBuilder* vertexDescriptorBuilder = Arcadia_Engine_Visuals_VertexDescriptorBuilder_create(thread);

  Arcadia_List_insertBackObjectReferenceValue
    (
      thread,
      vertexDescriptorBuilder->vertexElementDescriptors,
      (Arcadia_ObjectReferenceValue)
      Arcadia_Engine_Visuals_VertexElementDescriptor_create
        (
          thread,
          sizeof(Arcadia_Real32Value) * 0,
          Arcadia_Engine_Visuals_VertexElementSemantics_PositionXYZ,
          Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32Real32
        )
    );
  Arcadia_List_insertBackObjectReferenceValue
    (
      thread,
      vertexDescriptorBuilder->vertexElementDescriptors,
      Arcadia_Engine_Visuals_VertexElementDescriptor_create
        (
          thread,
          sizeof(Arcadia_Real32Value) * 3,
          Arcadia_Engine_Visuals_VertexElementSemantics_AmbientRGBA,
          Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32Real32Real32
        )
    );
  Arcadia_List_insertBackObjectReferenceValue
    (
      thread,
      vertexDescriptorBuilder->vertexElementDescriptors,
      (Arcadia_ObjectReferenceValue)
      Arcadia_Engine_Visuals_VertexElementDescriptor_create
        (
          thread,
          sizeof(Arcadia_Real32Value) * 7,
          Arcadia_Engine_Visuals_VertexElementSemantics_AmbientUV,
          Arcadia_Engine_Visuals_VertexElementSyntactics_Real32Real32
        )
    );
  Arcadia_ADL_MeshDefinition* source = (Arcadia_ADL_MeshDefinition*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_ADL_MeshDefinition_getType(thread));
  Arcadia_ADL_Definition_link(thread, (Arcadia_ADL_Definition*)source);
  Arcadia_ADL_ColorDefinition* ambientColorDefinition = (Arcadia_ADL_ColorDefinition*)source->ambientColor->definition;
  self->source = source;
  // TODO:
  // Each mesh creates its own material node for an ADL material definition.
  // This is wasteful.
  // Meshes using the same ADL material definition should use the material node.
  self->vertexDescriptor = Arcadia_Engine_Visuals_VertexDescriptorBuilder_build(thread, vertexDescriptorBuilder);
  self->ambientColor = Arcadia_Math_Color4Real32_create4(thread, ambientColorDefinition->red / 255.f,
                                                                 ambientColorDefinition->green / 255.f,
                                                                 ambientColorDefinition->blue / 255.f,
                                                                 1.f);
  self->numberOfVertices = Arcadia_ADL_MeshDefinition_getNumberOfVertices(thread, source);
  Arcadia_SizeValue numberOfBytes = self->vertexDescriptor->stride * self->numberOfVertices;
  self->vertices = Arcadia_Memory_allocateUnmanaged(thread, numberOfBytes);

  Arcadia_InternalImmutableByteArray* vertexXZZ = Arcadia_ADL_MeshDefinition_getVertexPositions(thread, source);
  Arcadia_Real32Value const* vertexYZBytes = (Arcadia_Real32Value const*)Arcadia_InternalImmutableByteArray_getBytes(thread, vertexXZZ);

  Arcadia_InternalImmutableByteArray* vertexAmbientRGBA = Arcadia_ADL_MeshDefinition_getVertexAmbientColors(thread, source);
  Arcadia_Real32Value const* vertexAmbientRGBBytes = (Arcadia_Real32Value const*)Arcadia_InternalImmutableByteArray_getBytes(thread, vertexAmbientRGBA);

  Arcadia_InternalImmutableByteArray* vertexAmbientUV = Arcadia_ADL_MeshDefinition_getVertexAmbientTextureCoordinates(thread, source);
  Arcadia_Real32Value const* vertexAmbientUVBytes = (Arcadia_Real32Value const*)Arcadia_InternalImmutableByteArray_getBytes(thread, vertexAmbientUV);

  Arcadia_ByteBuffer* temporary = Arcadia_ByteBuffer_create(thread);
  for (Arcadia_SizeValue i = 0, n = self->numberOfVertices; i < n; ++i) {
    Arcadia_ByteBuffer_insertBackBytes(thread, temporary, &vertexYZBytes[i * 3], sizeof(Arcadia_Real32Value) * 3);
    Arcadia_ByteBuffer_insertBackBytes(thread, temporary, &vertexAmbientRGBBytes[i * 4], sizeof(Arcadia_Real32Value) * 4);
    Arcadia_ByteBuffer_insertBackBytes(thread, temporary, &vertexAmbientUVBytes[i * 2], sizeof(Arcadia_Real32Value) * 2);
  }
  Arcadia_Memory_copy(thread, self->vertices, Arcadia_ByteBuffer_getBytes(thread, temporary),
                                              Arcadia_ByteBuffer_getNumberOfBytes(thread, temporary));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Engine_Visuals_MeshNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNodeDispatch* self
  )
{ }

static void
Arcadia_Engine_Visuals_MeshNode_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self
  )
{
  if (self->source) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
  }
  if (self->ambientColor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->ambientColor);
  }
  if (self->vertexDescriptor) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexDescriptor);
  }
}

static void
Arcadia_Engine_Visuals_MeshNode_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self
  )
{
  if (self->vertices) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->vertices);
    self->vertices = NULL;
  }
}

void
Arcadia_Engine_Visuals_MeshNode_getNumberOfVertices
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self,
    Arcadia_SizeValue* numberOfVertices
  )
{ *numberOfVertices = self->numberOfVertices; }

void
Arcadia_Engine_Visuals_MeshNode_setAmbientColor
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self,
    Arcadia_Math_Color4Real32* ambientColor
  )
{
  Arcadia_Math_Color4Real32_assign(thread, self->ambientColor, ambientColor);
}

Arcadia_Math_Color4Real32*
Arcadia_Engine_Visuals_MeshNode_getAmbientColor
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Visuals_MeshNode* self
  )
{
  return Arcadia_Math_Color4Real32_create4v(thread, self->ambientColor->components);
}
