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

#include "Arcadia/Visuals/VPL/Backends/GLSL/Program.h"

#include "Arcadia/Visuals/VPL/Backends/GLSL/ConstantBlock.h"
#include "Arcadia/Visuals/VPL/Backends/GLSL/Field.h"
#include "Arcadia/Visuals/VPL/Backends/GLSL/VariableScalar.h"
#include <string.h>

static void
Arcadia_Visuals_VPL_Backends_GLSL_Program_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Program* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Visuals_VPL_Backends_GLSL_Program_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};


Arcadia_defineObjectType(u8"Arcadia.Visuals.VPL.Backends.GLSL.Program", Arcadia_Visuals_VPL_Backends_GLSL_Program,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_VPL_Backends_GLSL_Program_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Program* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_VPL_Backends_GLSL_Program_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

Arcadia_Visuals_VPL_Backends_GLSL_Program*
Arcadia_Visuals_VPL_Backends_GLSL_Program_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_VPL_Backends_GLSL_Program);
}

static void
writeVariableScalar
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Program* self,
    Arcadia_Map* symbols,
    Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar* variableScalar,
    Arcadia_ByteBuffer* target
  )
{
  if (variableScalar->isInput) {
    Arcadia_ByteBuffer_insertBackBytes(thread, target, u8"in", strlen(u8"in"));
  } else {
    Arcadia_ByteBuffer_insertBackBytes(thread, target, u8"out", strlen(u8"out"));
  }
  Arcadia_ByteBuffer_insertBackBytes(thread, target, u8" ", strlen(u8" "));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, variableScalar->type), Arcadia_String_getNumberOfBytes(thread, variableScalar->type));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, u8" ", strlen(u8" "));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, variableScalar->name), Arcadia_String_getNumberOfBytes(thread, variableScalar->name));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, u8";\n", strlen(u8";\n"));
}

static void
writeConstantBlock
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Program* self,
    Arcadia_Map* symbols,
    Arcadia_Visuals_VPL_Backends_GLSL_ConstantBlock* constantBlock,
    Arcadia_ByteBuffer* target
  )
{
  // <constant block> : 'layout(std140)' 'uniform' <name> '{' <fields> '} '_'<name> ';'
  // <fields>: <field> ';' <fields>
  //         |
  // <field> : <type> <name>

  // - the index of a member of an uniform block definition `'uniform' <block name> <block definition> <instance name> ';'`
  // is obtained by `glGetProgramUniformLocation(program, "<block name>.<member name>")`.
  //
  // - the uniform block definition `'uniform' <block name> <block definition> <instance name> ';'`
  // is obtained by `glGetUniformBlockIndex(program, "<block name>")`.
  //
  // - <instance name> is like a namespace. If there are to uniform blocks of block names A and B and
  // both have a member of name x, then there would be a naming conflict as x is declared in global
  // namespace. You can avoid this conflict by asssigning different instance names to A and  B.
  // If you assign instance names a to A and b to B then x of A is defined in namespace a and x of B is defined in namespace b.
  // Note that no two uniform blocks may have the same instance name.
  //
  // - <instance name> and <block name> of a block must be different.

  Arcadia_String* name = constantBlock->name;

  // ensure there is no block in the blocks visited so far with the same name.
  // create an unique numeric id for that block.
  Arcadia_Value id = Arcadia_Map_get(thread, symbols, Arcadia_Value_makeObjectReferenceValue(name));
  if (!Arcadia_Value_isVoidValue(&id)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  id = Arcadia_Value_makeSizeValue(Arcadia_Collection_getSize(thread, (Arcadia_Collection*)symbols));
  Arcadia_Map_set(thread, symbols, Arcadia_Value_makeObjectReferenceValue(name), id, NULL, NULL);

  Arcadia_List* fields = Arcadia_Visuals_VPL_Backends_GLSL_ConstantBlock_getFields(thread, constantBlock);
  Arcadia_ByteBuffer_insertBackBytes(thread, target, u8"layout(std140) uniform ", strlen(u8"layout(std140) uniform "));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, name), Arcadia_String_getNumberOfBytes(thread, name));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, u8" {\n", strlen(u8" {\n"));
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)fields); i < n; ++i) {
    Arcadia_Visuals_VPL_Backends_GLSL_Field* field = Arcadia_List_getObjectReferenceValueAt(thread, fields, i);
    Arcadia_ByteBuffer_insertBackBytes(thread, target, u8"  ", strlen(u8"  "));
    Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, field->type), Arcadia_String_getNumberOfBytes(thread, field->type));
    Arcadia_ByteBuffer_insertBackBytes(thread, target, u8" ", strlen(u8" "));
    Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, field->name), Arcadia_String_getNumberOfBytes(thread, field->name));
    Arcadia_ByteBuffer_insertBackBytes(thread, target, u8";\n", strlen(u8";\n"));
  }
  Arcadia_ByteBuffer_insertBackBytes(thread, target, u8"}", strlen(u8"}"));
  Arcadia_String* temporary = Arcadia_String_createFromSize(thread, Arcadia_Value_getSizeValue(&id));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, u8"_", strlen(u8"_"));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, constantBlock->name), Arcadia_String_getNumberOfBytes(thread, constantBlock->name));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, temporary), Arcadia_String_getNumberOfBytes(thread, temporary));
  Arcadia_ByteBuffer_insertBackBytes(thread, target, u8";\n", strlen(u8";\n"));
}

void
Arcadia_Visuals_VPL_Backends_GLSL_Program_writeDefaultVertexShader
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Program* self,
    Arcadia_ByteBuffer* target
  )
{
  Arcadia_Visuals_VPL_Backends_GLSL_ConstantBlock* viewerBlock = NULL;
  Arcadia_Visuals_VPL_Backends_GLSL_ConstantBlock* meshBlock = NULL;
  Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar* variableScalar = NULL;
  Arcadia_List* fields = NULL;
  Arcadia_String* name = NULL, * type = NULL;
  // create fields of block "viewer"
  fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  name = Arcadia_String_createFromCxxString(thread, u8"projection");
  type = Arcadia_String_createFromCxxString(thread, u8"mat4");
  Arcadia_List_insertBackObjectReferenceValue(thread, fields, Arcadia_Visuals_VPL_Backends_GLSL_Field_create(thread, name, type));
  name = Arcadia_String_createFromCxxString(thread, u8"view");
  type = Arcadia_String_createFromCxxString(thread, u8"mat4");
  Arcadia_List_insertBackObjectReferenceValue(thread, fields, Arcadia_Visuals_VPL_Backends_GLSL_Field_create(thread, name, type));
  viewerBlock =
    Arcadia_Visuals_VPL_Backends_GLSL_ConstantBlock_create
    (
      thread,
      Arcadia_String_createFromCxxString(thread, u8"viewer"),
      (Arcadia_List*)Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(fields))
    );

  // create the fields of block "mesh"
  fields = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  name = Arcadia_String_createFromCxxString(thread, u8"model");
  type = Arcadia_String_createFromCxxString(thread, u8"mat4");
  Arcadia_List_insertBackObjectReferenceValue(thread, fields, Arcadia_Visuals_VPL_Backends_GLSL_Field_create(thread, name, type));
  // create the constantblock "matrices"
  meshBlock =
    Arcadia_Visuals_VPL_Backends_GLSL_ConstantBlock_create
      (
        thread,
        Arcadia_String_createFromCxxString(thread, u8"mesh"),
        (Arcadia_List*)Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(fields))
      );

  static const char* prefix =
    "#version 330 core\n"
    "layout(location = 0) in vec3 vertexPosition;\n"
    ;
  variableScalar =
    Arcadia_Visuals_VPL_Backends_GLSL_VariableScalar_create
      (
        thread,
        0,
        Arcadia_BooleanValue_True,
        Arcadia_String_createFromCxxString(thread, u8"vertexPosition"),
        Arcadia_String_createFromCxxString(thread, u8"vec3")
      );
  static const char* suffix =
    "void main() {\n"
    "  mat4 mvp = _viewer0.projection * _viewer0.view * _mesh0.model;"
    "  gl_Position = mvp * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);\n"
    "}\n"
    ;
  Arcadia_ByteBuffer_insertBackBytes(thread, target, prefix, strlen(prefix));
  writeConstantBlock(thread, self, (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void)), viewerBlock, target);
  writeConstantBlock(thread, self, (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void)), meshBlock, target);
  Arcadia_ByteBuffer_insertBackBytes(thread, target, suffix, strlen(suffix) + 1);
}

void
Arcadia_Visuals_VPL_Backends_GLSL_Program_writeDefaultFragmentShader
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Program* self,
    Arcadia_ByteBuffer* target
  )
{
  static const char* program =
    "#version 330 core\n"
    "out vec4 fragmentColor;\n"
    "\n"
    "void main() {\n"
    " fragmentColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n"
    ;
  Arcadia_ByteBuffer_insertBackBytes(thread, target, program, strlen(program) + 1);
}
