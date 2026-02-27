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

#define ARCADIA_VPL_PRIVATE (1)
#include "Arcadia/VPL/Program.h"

#include "Arcadia/Languages/Include.h"
#include "Arcadia/VPL/Symbols/ConstantRecord.h"
#include "Arcadia/VPL/Symbols/ConstantRecordField.h"
#include "Arcadia/VPL/Symbols/Scalar.h"
#include "Arcadia/VPL/Symbols/BuiltinType.h"

static void
createConstants
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self,
    Arcadia_List* constantBlocks
  )
{
  Arcadia_VPL_ConstantRecord* constantRecord = NULL;
  Arcadia_List* fields = NULL;
  Arcadia_String* name = NULL, * type = NULL;

  {
    // create fields of block "viewer"
    fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    constantRecord =
      Arcadia_VPL_ConstantRecord_create
        (
          thread,
          Arcadia_String_createFromCxxString(thread, u8"viewer"),
          self,
          (Arcadia_List*)(fields)
        );

    name = Arcadia_String_createFromCxxString(thread, u8"viewToProjection");
    type = self->MAT4->name;
    Arcadia_List_insertBackObjectReferenceValue(thread, constantRecord->fields, Arcadia_VPL_ConstantRecordField_create(thread, name, type, constantRecord));

    name = Arcadia_String_createFromCxxString(thread, u8"worldToView");
    type = self->MAT4->name;
    Arcadia_List_insertBackObjectReferenceValue(thread, constantRecord->fields, Arcadia_VPL_ConstantRecordField_create(thread, name, type, constantRecord));

    Arcadia_List_insertBackObjectReferenceValue(thread, constantBlocks, (Arcadia_Object*)constantRecord);
  }
  {
    // create the fields of block "model"
    fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    constantRecord =
      Arcadia_VPL_ConstantRecord_create
        (
          thread,
          Arcadia_String_createFromCxxString(thread, u8"model"),
          self,
          (Arcadia_List*)(fields)
        );
 
    name = Arcadia_String_createFromCxxString(thread, u8"localToWorld");
    type = self->MAT4->name;
    Arcadia_List_insertBackObjectReferenceValue(thread, constantRecord->fields, Arcadia_VPL_ConstantRecordField_create(thread, name, type, constantRecord));
 
    Arcadia_List_insertBackObjectReferenceValue(thread, constantBlocks, (Arcadia_Object*)constantRecord);
  }
  {
    // create the fields of block "mesh"
    fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    constantRecord =
      Arcadia_VPL_ConstantRecord_create
        (
          thread,
          Arcadia_String_createFromCxxString(thread, u8"mesh"),
          self,
          (Arcadia_List*)(fields)
        );

    name = Arcadia_String_createFromCxxString(thread, u8"ambientColor");
    type = self->VEC4->name;
    Arcadia_List_insertBackObjectReferenceValue(thread, constantRecord->fields, Arcadia_VPL_ConstantRecordField_create(thread, name, type, constantRecord));

    Arcadia_List_insertBackObjectReferenceValue(thread, constantBlocks, (Arcadia_Object*)constantRecord);
  }
}

static void
createVariableScalars
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self,
    Arcadia_List* variableScalars
  )
{
  Arcadia_VPL_VariableScalar* variableScalar;
  // the xyz position of the vertex
  variableScalar =
    Arcadia_VPL_VariableScalar_create
      (
        thread,
        0,
        Arcadia_VPL_ScalarFlags_Variable | Arcadia_VPL_ScalarFlags_Vertex,
        Arcadia_String_createFromCxxString(thread, u8"_0_vertexPosition"),
        self->VEC3->name
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the rgba ambient color of the vertex
  variableScalar =
    Arcadia_VPL_VariableScalar_create
      (
        thread,
        1,
        Arcadia_VPL_ScalarFlags_Variable | Arcadia_VPL_ScalarFlags_Vertex,
        Arcadia_String_createFromCxxString(thread, u8"_0_vertexAmbientColor"),
        self->VEC4->name
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the texture coordinate of the vertex adressing the ambient color texture
  variableScalar =
    Arcadia_VPL_VariableScalar_create
      (
        thread,
        2,
        Arcadia_VPL_ScalarFlags_Variable | Arcadia_VPL_ScalarFlags_Vertex,
        Arcadia_String_createFromCxxString(thread, u8"_0_vertexAmbientColorTextureCoordinate"),
        self->VEC2->name
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the texture coordinate of the vertex adressing the ambient color texture
  variableScalar =
    Arcadia_VPL_VariableScalar_create
    (
      thread,
      -1,
      Arcadia_VPL_ScalarFlags_Variable | Arcadia_VPL_ScalarFlags_Fragment,
      Arcadia_String_createFromCxxString(thread, u8"_1_vertexAmbientColorTextureCoordinate"),
      self->VEC2->name
    );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  variableScalar =
    Arcadia_VPL_VariableScalar_create
      (
        thread,
        0,
        Arcadia_VPL_ScalarFlags_Constant | Arcadia_VPL_ScalarFlags_Fragment,
        Arcadia_String_createFromCxxString(thread, u8"_0_ambientColorTexture"),
        self->SAMPLER2D->name
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the rgba ambient color of the vertex
  variableScalar =
    Arcadia_VPL_VariableScalar_create
      (
        thread,
        -1,
        Arcadia_VPL_ScalarFlags_Variable | Arcadia_VPL_ScalarFlags_Fragment,
        Arcadia_String_createFromCxxString(thread, u8"_1_vertexAmbientColor"),
        self->VEC4->name
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);

  // the rgba ambient color of the fragment
  variableScalar =
    Arcadia_VPL_VariableScalar_create
      (
        thread,
        -1,
        Arcadia_VPL_ScalarFlags_Variable | Arcadia_VPL_ScalarFlags_FrameBuffer,
        Arcadia_String_createFromCxxString(thread, u8"_2_fragmentColor"),
        self->VEC4->name
      );
  Arcadia_List_insertBackObjectReferenceValue(thread, variableScalars, (Arcadia_Object*)variableScalar);
}

static void
createVertexShaderMainFunction
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self
  )
{
}

static void
createFragmentShaderMainFunction
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self
  )
{
}

static void
Arcadia_VPL_Program_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self
  );

static void
Arcadia_VPL_Program_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ProgramDispatch* self
  );

static void
Arcadia_VPL_Program_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Program_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Program_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.Program", Arcadia_VPL_Program,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_VPL_Program_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Program);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->scope = NULL;
  self->flags = Arcadia_ValueStack_getNatural8Value(thread, 1);
  Arcadia_Languages_StringTable* stringTable = Arcadia_Languages_StringTable_getOrCreate(thread);
  self->MAT4 = Arcadia_VPL_BuiltinType_create(thread, Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"mat4"));
  self->VEC2 = Arcadia_VPL_BuiltinType_create(thread, Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec2"));
  self->VEC3 = Arcadia_VPL_BuiltinType_create(thread, Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec3"));
  self->VEC4 = Arcadia_VPL_BuiltinType_create(thread, Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec4"));
  self->SAMPLER2D = Arcadia_VPL_BuiltinType_create(thread, Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"sampler2D"));
  self->vertexProgramMain = NULL;
  self->fragmentProgramMain = NULL;
  self->constants = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->variableScalars = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_LeaveConstructor(Arcadia_VPL_Program);
}

static void
Arcadia_VPL_Program_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ProgramDispatch* self
  )
{ }

static void
Arcadia_VPL_Program_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self
  )
{
  if (self->vertexProgramMain) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexProgramMain);
  }
  if (self->fragmentProgramMain) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->fragmentProgramMain);
  }
  if (self->scope) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scope);
  }
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
  if (self->constants) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->constants);
  }
  if (self->variableScalars) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableScalars);
  }
}

Arcadia_VPL_Program*
Arcadia_VPL_Program_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, flags);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Program);
}

Arcadia_VPL_ConstantRecord*
Arcadia_VPL_Program_getConstantBlockByName
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self,
    Arcadia_String* name
  )
{ 
  Arcadia_Value temporary = Arcadia_Value_makeObjectReferenceValue(name);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->constants); i < n; ++i) {
    Arcadia_VPL_ConstantRecord* e = (Arcadia_VPL_ConstantRecord*)Arcadia_List_getObjectReferenceValueAt(thread, self->constants, i);
    if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)e->name, &temporary)) {
      return e;
    }
  }
  return NULL;
}

Arcadia_List*
Arcadia_VPL_Program_getConstantBlocks
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Program* self
  )
{ 
  Arcadia_List* clone = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->constants); i < n; ++i) {
    Arcadia_List_insertBack(thread, clone, Arcadia_List_getAt(thread, self->constants, i));
  }
  return clone;
}

Arcadia_VPL_Program*
Arcadia_VPL_Program_createProgram
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags
  )
{
  Arcadia_VPL_Program* program = Arcadia_VPL_Program_create(thread, flags);
  createVertexShaderMainFunction(thread, program);
  createFragmentShaderMainFunction(thread, program);
  createConstants(thread, program, program->constants);
  createVariableScalars(thread, program, program->variableScalars);
  return program;
}