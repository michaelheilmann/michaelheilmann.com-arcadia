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

#include "Arcadia/Visuals/VPL/Program.h"

#include "Arcadia/Languages/Include.h"
#include "Arcadia/Visuals/VPL/ConstantBlock.h"
#include "Arcadia/Visuals/VPL/Field.h"
#include "Arcadia/Visuals/VPL/Scalar.h"

static void
createConstantBlocks
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Program* self,
    Arcadia_List* constantBlocks
  )
{
  Arcadia_Visuals_VPL_ConstantBlock* constantBlock = NULL;
  Arcadia_List* fields = NULL;
  Arcadia_String* name = NULL, * type = NULL;

  {
    // create fields of block "viewer"
    fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    name = Arcadia_String_createFromCxxString(thread, u8"projection");
    type = self->MAT4;
    Arcadia_List_insertBackObjectReferenceValue(thread, fields, Arcadia_Visuals_VPL_Field_create(thread, name, type));
    name = Arcadia_String_createFromCxxString(thread, u8"view");
    type = self->MAT4;
    Arcadia_List_insertBackObjectReferenceValue(thread, fields, Arcadia_Visuals_VPL_Field_create(thread, name, type));
    constantBlock =
      Arcadia_Visuals_VPL_ConstantBlock_create
        (
          thread,
          Arcadia_String_createFromCxxString(thread, u8"viewer"),
          (Arcadia_List*)Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(fields))
        );
    Arcadia_List_insertBackObjectReferenceValue(thread, constantBlocks, (Arcadia_Object*)constantBlock);
  }
  {
    // create the fields of block "model"
    fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    // mat4 localToWorld;
    name = Arcadia_String_createFromCxxString(thread, u8"localToWorld");
    type = self->MAT4;
    Arcadia_List_insertBackObjectReferenceValue(thread, fields, Arcadia_Visuals_VPL_Field_create(thread, name, type));
    // create the constant block "mesh"
    constantBlock =
      Arcadia_Visuals_VPL_ConstantBlock_create
        (
          thread,
          Arcadia_String_createFromCxxString(thread, u8"model"),
          (Arcadia_List*)Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(fields))
        );
    Arcadia_List_insertBackObjectReferenceValue(thread, constantBlocks, (Arcadia_Object*)constantBlock);
  }
  {
    // create the fields of block "mesh"
    fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    // vec4 color;
    name = Arcadia_String_createFromCxxString(thread, u8"ambientColor");
    type = self->VEC4;
    Arcadia_List_insertBackObjectReferenceValue(thread, fields, Arcadia_Visuals_VPL_Field_create(thread, name, type));
    // create the constant block "mesh"
    constantBlock =
      Arcadia_Visuals_VPL_ConstantBlock_create
        (
          thread,
          Arcadia_String_createFromCxxString(thread, u8"mesh"),
          (Arcadia_List*)Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(fields))
        );
    Arcadia_List_insertBackObjectReferenceValue(thread, constantBlocks, (Arcadia_Object*)constantBlock);
  }
}

static void
createVariableScalars
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Program* self,
    Arcadia_List* variableScalars
  )
{
  Arcadia_Visuals_VPL_VariableScalar* variableScalar;
  // the xyz position of the vertex
  variableScalar =
    Arcadia_Visuals_VPL_VariableScalar_create
      (
        thread,
        0,
        Arcadia_Visuals_VPL_ScalarFlags_Variable | Arcadia_Visuals_VPL_ScalarFlags_Vertex,
        Arcadia_String_createFromCxxString(thread, u8"_0_vertexPosition"),
        self->VEC3
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the rgba ambient color of the vertex
  variableScalar =
    Arcadia_Visuals_VPL_VariableScalar_create
      (
        thread,
        1,
        Arcadia_Visuals_VPL_ScalarFlags_Variable | Arcadia_Visuals_VPL_ScalarFlags_Vertex,
        Arcadia_String_createFromCxxString(thread, u8"_0_vertexAmbientColor"),
        self->VEC4
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the texture coordinate of the vertex adressing the ambient color texture
  variableScalar =
    Arcadia_Visuals_VPL_VariableScalar_create
      (
        thread,
        2,
        Arcadia_Visuals_VPL_ScalarFlags_Variable | Arcadia_Visuals_VPL_ScalarFlags_Vertex,
        Arcadia_String_createFromCxxString(thread, u8"_0_vertexAmbientColorTextureCoordinate"),
        self->VEC2
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the texture coordinate of the vertex adressing the ambient color texture
  variableScalar =
    Arcadia_Visuals_VPL_VariableScalar_create
    (
      thread,
      -1,
      Arcadia_Visuals_VPL_ScalarFlags_Variable | Arcadia_Visuals_VPL_ScalarFlags_Fragment,
      Arcadia_String_createFromCxxString(thread, u8"_1_vertexAmbientColorTextureCoordinate"),
      self->VEC2
    );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  variableScalar =
    Arcadia_Visuals_VPL_VariableScalar_create
      (
        thread,
        0,
        Arcadia_Visuals_VPL_ScalarFlags_Constant | Arcadia_Visuals_VPL_ScalarFlags_Fragment,
        Arcadia_String_createFromCxxString(thread, u8"_0_ambientColorTexture"),
        self->SAMPLER2D
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the rgba ambient color of the vertex
  variableScalar =
    Arcadia_Visuals_VPL_VariableScalar_create
      (
        thread,
        -1,
        Arcadia_Visuals_VPL_ScalarFlags_Variable | Arcadia_Visuals_VPL_ScalarFlags_Fragment,
        Arcadia_String_createFromCxxString(thread, u8"_1_vertexColor"),
        self->VEC4
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the rgba ambient color of the fragment
  variableScalar =
    Arcadia_Visuals_VPL_VariableScalar_create
      (
        thread,
        -1,
        Arcadia_Visuals_VPL_ScalarFlags_Variable | Arcadia_Visuals_VPL_ScalarFlags_FrameBuffer,
        Arcadia_String_createFromCxxString(thread, u8"_2_fragmentColor"),
        self->VEC4
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);
}

static void
Arcadia_Visuals_VPL_Program_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Program* self
  );

static void
Arcadia_Visuals_VPL_Program_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_ProgramDispatch* self
  );

static void
Arcadia_Visuals_VPL_Program_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Program* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_VPL_Program_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_VPL_Program_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.VPL.Program", Arcadia_Visuals_VPL_Program,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_VPL_Program_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Program* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_VPL_Program_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->flags = Arcadia_ValueStack_getNatural8Value(thread, 1);
  Arcadia_Languages_StringTable* stringTable = Arcadia_Languages_StringTable_getOrCreate(thread);
  self->MAT4 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"mat4");
  self->VEC2 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec2");
  self->VEC3 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec3");
  self->VEC4 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec4");
  self->SAMPLER2D = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"sampler2D");
  self->constantBlocks = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->variableScalars = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  createConstantBlocks(thread, self, self->constantBlocks);
  createVariableScalars(thread, self, self->variableScalars);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_Visuals_VPL_Program_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_ProgramDispatch* self
  )
{ }

static void
Arcadia_Visuals_VPL_Program_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Program* self
  )
{
  if (self->MAT4) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->MAT4);
  }
  if (self->VEC2) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->VEC2);
  }
  if (self->VEC3) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->VEC3);
  }
  if (self->VEC4) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->VEC4);
  }
  if (self->SAMPLER2D) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->SAMPLER2D);
  }
  if (self->constantBlocks) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->constantBlocks);
  }
  if (self->variableScalars) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableScalars);
  }
}

Arcadia_Visuals_VPL_Program*
Arcadia_Visuals_VPL_Program_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, flags);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_VPL_Program);
}
