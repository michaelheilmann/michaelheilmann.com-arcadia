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

#include "Arcadia/VPL/GLSL/Transpiler.h"

#include "Arcadia/Languages/Include.h"
#include "Arcadia/VPL/SemanticalAnalysis.h"
#include "Arcadia/VPL/Include.h"
#include <string.h>

static const char ZEROTERMINATOR =
  '\0'
  ;

static const char* HEADER =
  "#version 420 core\n"
  ;

static void
emitCxxString
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* target,
    const char* p
  );

static void
emitString
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* target,
    Arcadia_String* p
  );

static void
writeType
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_String* type,
    Arcadia_ByteBuffer* target
  );

static void
writeVariableScalar
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* symbols,
    Arcadia_VPL_VariableScalar* variableScalar,
    Arcadia_ByteBuffer* target
  );

static void
writeConstantScalar
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* constantBlockMapping,
    Arcadia_Map* symbols,
    Arcadia_VPL_ConstantScalar* constantScalar,
    Arcadia_ByteBuffer* target
  );

static void
writeConstantRecord
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* constantBlockMapping,
    Arcadia_Map* symbols,
    Arcadia_VPL_ConstantRecord* constantBlock,
    Arcadia_ByteBuffer* target
  );

static void
Arcadia_VPL_Backends_GLSL_Transpiler_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self
  );

static void
Arcadia_VPL_Backends_GLSL_Transpiler_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_TranspilerDispatch* self
  );

static void
Arcadia_VPL_Backends_GLSL_Transpiler_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Backends_GLSL_Transpiler_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Backends_GLSL_Transpiler_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.VPL.Backends.GLSL.Transpiler", Arcadia_VPL_Backends_GLSL_Transpiler,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_VPL_Backends_GLSL_Transpiler_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_VPL_Backends_GLSL_Transpiler_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->semanticalAnalysis = Arcadia_VPL_SemanticalAnalysis_create(thread);
  Arcadia_Languages_StringTable* stringTable = Arcadia_Languages_StringTable_getOrCreate(thread);
  self->MAT4 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"mat4");
  self->VEC2 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec2");
  self->VEC3 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec3");
  self->VEC4 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec4");
  self->SAMPLER2D = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"sampler2D");
  self->names = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));

#define Define(vpl, glsl) \
  { \
    Arcadia_String* source = Arcadia_String_createFromCxxString(thread, vpl); \
    Arcadia_String* target = Arcadia_String_createFromCxxString(thread, glsl); \
    Arcadia_Map_set(thread, self->names, Arcadia_Value_makeObjectReferenceValue(source), Arcadia_Value_makeObjectReferenceValue(target), NULL, NULL); \
  }

  // Passes mesh information to the vertex program.
  Define("vertexProgram.inputs.mesh", "_mesh0");
  // Passes model information to the vertex program.
  Define("vertexProgram.inputs.model", "_model0");
  // Passes viewer information to the vertex program.
  Define("vertexProgram.inputs.viewer", "_viewer0");
  // Passses the per-vertex ambient color into to vertex program.
  Define("vertexProgram.inputs.vertex.ambientColor", "_0_vertexAmbientColor");

  // Passes the per-vertex ambient color texture coordinates into the vertex program.
  Define("vertexProgram.inputs.vertex.ambientColorTextureCoordinate", "_0_vertexAmbientColorTextureCoordinate");

  // Pass vertex program -> fragment program ambient color.
  Define("fragmentProgram.inputs.vertex.ambientColor", "_1_vertexAmbientColor");
  // Pass vertex program -> fragment program ambient color texture coordinates.
  Define("fragmentProgram.inputs.vertex.ambientColorTextureCoordinate", "_1_vertexAmbientColorTextureCoordinate");

  // Vertex position input of fragment program.
  // This is an output for the vertex program and an input for the fragment program.
  Define("fragmentProgram.inputs.vertex.position", "_1_vertexPosition");
  // Vertex position input of vertex program.
  // This is an input for the vertex program.
  Define("vertexProgram.inputs.vertex.position", "_0_vertexPosition");
  // Output of fragment program to rasterizer.
  Define("rasterizerProgram.inputs.fragmentColor", "_2_fragmentColor");

#undef Define

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static Arcadia_String* mapName(Arcadia_Thread* thread, Arcadia_VPL_Backends_GLSL_Transpiler* self, Arcadia_String* name) {
  return (Arcadia_String*)Arcadia_Map_getObjectReferenceValueChecked(thread, self->names, Arcadia_Value_makeObjectReferenceValue(name), _Arcadia_String_getType(thread));
}

static void
Arcadia_VPL_Backends_GLSL_Transpiler_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_TranspilerDispatch* self
  )
{ }

static void
Arcadia_VPL_Backends_GLSL_Transpiler_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self
  )
{
  if (self->semanticalAnalysis) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->semanticalAnalysis);
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
  if (self->names) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->names);
  }
}

Arcadia_VPL_Backends_GLSL_Transpiler*
Arcadia_VPL_Backends_GLSL_Transpiler_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Backends_GLSL_Transpiler);
}

static void
emitCxxString
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* target,
    const char* p
  )
{
  Arcadia_ByteBuffer_insertBackBytes(thread, target, p, strlen(p));
}

static void
emitString
  (
    Arcadia_Thread* thread,
    Arcadia_ByteBuffer* target,
    Arcadia_String* p
  )
{
  Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, p),
                                                     Arcadia_String_getNumberOfBytes(thread, p));
}

static void
writeType
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_String* type,
    Arcadia_ByteBuffer* target
  )
{
  Arcadia_Value v = Arcadia_Value_makeObjectReferenceValue(type);
  if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->MAT4, &v)) {
    emitString(thread, target, self->MAT4);
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->VEC2, &v)) {
    emitString(thread, target, self->VEC2);
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->VEC3, &v)) {
    emitString(thread, target, self->VEC3);
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->VEC4, &v)) {
    emitString(thread, target, self->VEC4);
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->SAMPLER2D, &v)) {
    emitString(thread, target, self->SAMPLER2D);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
}

static void
writeVariableScalar
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* symbols,
    Arcadia_VPL_VariableScalar* variableScalar,
    Arcadia_ByteBuffer* target
  )
{
  switch (context) {
    case Context_VertexShader: {
      if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_Vertex) == Arcadia_VPL_ScalarFlags_Vertex) {
        if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_Constant) == Arcadia_VPL_ScalarFlags_Constant) {
          emitCxxString(thread, target, "layout(binding = ");
          emitString(thread, target, Arcadia_String_createFromInteger32(thread, variableScalar->location));
          emitCxxString(thread, target, u8") ");
          emitCxxString(thread, target, u8"uniform");
        } else {
          emitCxxString(thread, target, "layout(location = ");
          emitString(thread, target, Arcadia_String_createFromInteger32(thread, variableScalar->location));
          emitCxxString(thread, target, u8") ");
          emitCxxString(thread, target, u8"in");
        }
        emitCxxString(thread, target, u8" ");
        writeType(thread, self, variableScalar->type, target);
        emitCxxString(thread, target, u8" ");
        emitString(thread, target, variableScalar->name);
        emitCxxString(thread, target, u8";\n");
      } else if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_Fragment) == Arcadia_VPL_ScalarFlags_Fragment) {
        if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_Constant) == 0) {
          emitCxxString(thread, target, u8"out");
          emitCxxString(thread, target, u8" ");
          writeType(thread, self, variableScalar->type, target);
          emitCxxString(thread, target, u8" ");
          emitString(thread, target, variableScalar->name);
          emitCxxString(thread, target, u8";\n");
        }
      } else if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_FrameBuffer) == Arcadia_VPL_ScalarFlags_FrameBuffer) {
        /*Intentionally empty.*/
      } else {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
    } break;
    case Context_FragmentShader: {
      if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_Vertex) == Arcadia_VPL_ScalarFlags_Vertex) {
        /*Intentionally empty.*/
      } else if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_Fragment) == Arcadia_VPL_ScalarFlags_Fragment) {
        if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_Constant) == Arcadia_VPL_ScalarFlags_Constant) {
          emitCxxString(thread, target, "layout(binding = ");
          emitString(thread, target, Arcadia_String_createFromInteger32(thread, variableScalar->location));
          emitCxxString(thread, target, u8") ");
          emitCxxString(thread, target, u8"uniform");
        } else {
          emitCxxString(thread, target, u8"in");
        }
        emitCxxString(thread, target, u8" ");
        writeType(thread, self, variableScalar->type, target);
        emitCxxString(thread, target, u8" ");
        emitString(thread, target, variableScalar->name);
        emitCxxString(thread, target, u8";\n");
      } else if ((variableScalar->flags & Arcadia_VPL_ScalarFlags_FrameBuffer) == Arcadia_VPL_ScalarFlags_FrameBuffer) {
        emitCxxString(thread, target, u8"out");
        emitCxxString(thread, target, u8" ");
        writeType(thread, self, variableScalar->type, target);
        emitCxxString(thread, target, u8" ");
        emitString(thread, target, variableScalar->name);
        emitCxxString(thread, target, u8";\n");
      } else {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static void
writeConstantScalar
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* constantBlockMapping,
    Arcadia_Map* symbols,
    Arcadia_VPL_ConstantScalar* constantScalar,
    Arcadia_ByteBuffer* target
  )
{ }

static void
writeConstantRecord
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* constantBlockMapping,
    Arcadia_Map* symbols,
    Arcadia_VPL_ConstantRecord* constantBlock,
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

  // Add the VPL constant block name to GL uniform block name to the map.
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertBackString(thread, stringBuffer, name);
  Arcadia_StringBuffer_insertCodePointBack(thread, stringBuffer, '\0');
  Arcadia_String* glBlockName = Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuffer));
  Arcadia_Map_set(thread, constantBlockMapping, Arcadia_Value_makeObjectReferenceValue(constantBlock->name), Arcadia_Value_makeObjectReferenceValue(glBlockName), NULL, NULL);

  // ensure there is no block in the blocks visited so far with the same name.
  // create an unique numeric id for that block.
  Arcadia_Value id = Arcadia_Map_get(thread, symbols, Arcadia_Value_makeObjectReferenceValue(name));
  if (!Arcadia_Value_isVoidValue(&id)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  id = Arcadia_Value_makeSizeValue(Arcadia_Collection_getSize(thread, (Arcadia_Collection*)symbols));
  Arcadia_Map_set(thread, symbols, Arcadia_Value_makeObjectReferenceValue(name), id, NULL, NULL);

  Arcadia_List* fields = Arcadia_VPL_ConstantRecord_getFields(thread, constantBlock);
  emitCxxString(thread, target, u8"layout(std140) uniform ");
  Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, name), Arcadia_String_getNumberOfBytes(thread, name));
  emitCxxString(thread, target, u8" {\n");
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)fields); i < n; ++i) {
    Arcadia_VPL_ConstantRecordField* field = Arcadia_List_getObjectReferenceValueAt(thread, fields, i);
    emitCxxString(thread, target, u8"  ");
    writeType(thread, self, field->type, target);
    emitCxxString(thread, target, u8" ");
    emitString(thread, target, field->name);
    emitCxxString(thread, target, u8";\n");
  }
  emitCxxString(thread, target, u8"}");
  Arcadia_String* temporary = Arcadia_String_createFromSize(thread, Arcadia_Value_getSizeValue(&id));
  emitCxxString(thread, target, u8"_");
  emitString(thread, target, constantBlock->name);
  emitString(thread, target, temporary);
  emitCxxString(thread, target, u8";\n");
}

static void
onParameterVaribleDefinitionTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  );

static void
onExpressionTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  );

static void
onNameTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  );

static void
onStatementListTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  );

static void
onFunctionDefinitionTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  );

static void
onParameterVaribleDefinitionTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  )
{
  if (tree->flags != Arcadia_VPL_Tree_NodeFlags_ParameterVariableDefinition) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  onNameTree(thread, self, tree->parameterVariableDefinition.type, target);
  emitCxxString(thread, target, " ");
  onNameTree(thread, self, tree->parameterVariableDefinition.name, target);
}

static void
onExpressionTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  )
{
  switch (tree->flags) {
    case Arcadia_VPL_Tree_NodeFlags_BinaryExpr: {
      Arcadia_VPL_Tree_BinaryExprNode* binaryExpressionNode = (Arcadia_VPL_Tree_BinaryExprNode*)tree;

      switch (binaryExpressionNode->kind) {
        case Arcadia_VPL_Tree_BinaryExprNodeFlags_Access: {
          emitCxxString(thread, target, "(");
          onExpressionTree(thread, self, binaryExpressionNode->lhs, target);
          emitCxxString(thread, target, ".");
          onExpressionTree(thread, self, binaryExpressionNode->rhs, target);
          emitCxxString(thread, target, ")");
        } break;
        case Arcadia_VPL_Tree_BinaryExprNodeFlags_Add: {
          emitCxxString(thread, target, "(");
          onExpressionTree(thread, self, binaryExpressionNode->lhs, target);
          emitCxxString(thread, target, " + ");
          onExpressionTree(thread, self, binaryExpressionNode->rhs, target);
          emitCxxString(thread, target, ")");
        } break;
        case Arcadia_VPL_Tree_BinaryExprNodeFlags_Subtract: {
          emitCxxString(thread, target, "(");
          onExpressionTree(thread, self, binaryExpressionNode->lhs, target);
          emitCxxString(thread, target, " - ");
          onExpressionTree(thread, self, binaryExpressionNode->rhs, target);
          emitCxxString(thread, target, ")");
        } break;
        case Arcadia_VPL_Tree_BinaryExprNodeFlags_Multiply: {
          emitCxxString(thread, target, "(");
          onExpressionTree(thread, self, binaryExpressionNode->lhs, target);
          emitCxxString(thread, target, " * ");
          onExpressionTree(thread, self, binaryExpressionNode->rhs, target);
          emitCxxString(thread, target, ")");
        } break;
        case Arcadia_VPL_Tree_BinaryExprNodeFlags_Divide: {
          emitCxxString(thread, target, "(");
          onExpressionTree(thread, self, binaryExpressionNode->lhs, target);
          emitCxxString(thread, target, " / ");
          onExpressionTree(thread, self, binaryExpressionNode->rhs, target);
          emitCxxString(thread, target, ")");
        } break;
        case Arcadia_VPL_Tree_BinaryExprNodeFlags_Assignment: {
          emitCxxString(thread, target, u8"  ");
          onExpressionTree(thread, self, binaryExpressionNode->lhs, target);
          emitCxxString(thread, target, u8" = ");
          onExpressionTree(thread, self, binaryExpressionNode->rhs, target);
          emitCxxString(thread, target, ";\n");
        } break;
      };
    } break;

    case Arcadia_VPL_Tree_NodeFlags_Name: {
      emitString(thread, target, tree->name.name);
    } break;
    case Arcadia_VPL_Tree_NodeFlags_Number: {
      emitCxxString(thread, target, "(");
      emitString(thread, target, tree->literal);
      emitCxxString(thread, target, ")");
    } break;
    case Arcadia_VPL_Tree_NodeFlags_Call: {
      //emitCxxString(thread, target, "(");
      onExpressionTree(thread, self, tree->call.target, target);
      //emitCxxString(thread, target, ")");
      emitCxxString(thread, target, "(");
      if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->call.arguments) > 0) {
        Arcadia_VPL_Tree_Node* argument;
        argument = (Arcadia_VPL_Tree_Node*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->call.arguments, 0, _Arcadia_VPL_Tree_Node_getType(thread));
        onExpressionTree(thread, self, argument, target);
        for (Arcadia_SizeValue i = 1, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->call.arguments); i < n; ++i) {
          argument = (Arcadia_VPL_Tree_Node*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->call.arguments, i, _Arcadia_VPL_Tree_Node_getType(thread));
          emitCxxString(thread, target, ", ");
          onExpressionTree(thread, self, argument, target);
        }
      }
      emitCxxString(thread, target, ")");
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static void
onNameTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  )
{
  if (tree->flags != Arcadia_VPL_Tree_NodeFlags_Name) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  emitString(thread, target, tree->name.name);
}

static void
onStatementListTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  )
{
  if (tree->flags != Arcadia_VPL_Tree_NodeFlags_StatementList) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->statementList); i < n; ++i) {
    Arcadia_VPL_Tree_Node* a = (Arcadia_VPL_Tree_Node*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->statementList, i,
                                                                                                                     _Arcadia_VPL_Tree_Node_getType(thread));
    switch (a->flags) {
      case Arcadia_VPL_Tree_NodeFlags_VariableDefinition: {
        emitCxxString(thread, target, u8"  ");
        onNameTree(thread, self, a->variableDefinition.type, target);
        emitCxxString(thread, target, u8" ");
        onNameTree(thread, self, a->variableDefinition.name, target);
        emitCxxString(thread, target, ";\n");
      } break;
      case Arcadia_VPL_Tree_NodeFlags_BinaryExpr:
      case Arcadia_VPL_Tree_NodeFlags_Call:
      case Arcadia_VPL_Tree_NodeFlags_Number: {
        onExpressionTree(thread, self, a, target);
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
  }
}

static void
onFunctionDefinitionTree
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Tree_Node* tree,
    Arcadia_ByteBuffer* target
  )
{
  onNameTree(thread, self, tree->functionDefinition.returnValueType, target);
  emitCxxString(thread, target, " ");
  onNameTree(thread, self, tree->functionDefinition.name, target);
  emitCxxString(thread, target, "(");

  if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->functionDefinition.parameters) > 0) {
    Arcadia_VPL_Tree_Node* parameter;
    parameter = (Arcadia_VPL_Tree_Node*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->functionDefinition.parameters, 0, _Arcadia_VPL_Tree_Node_getType(thread));
    onParameterVaribleDefinitionTree(thread, self, parameter, target);
    for (Arcadia_SizeValue i = 1, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->functionDefinition.parameters); i < n; ++i) {
      parameter = (Arcadia_VPL_Tree_Node*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->functionDefinition.parameters, i, _Arcadia_VPL_Tree_Node_getType(thread));
      emitCxxString(thread, target, ", ");
      onParameterVaribleDefinitionTree(thread, self, parameter, target);
    }
  }

  emitCxxString(thread, target, ")");
  emitCxxString(thread, target, " ");
  emitCxxString(thread, target, "{\n");
  onStatementListTree(thread, self, tree->functionDefinition.body, target);
  emitCxxString(thread, target, "}\n");
}

static void
OnCall1
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* tree,
    va_list arguments
  )
{
  Arcadia_VPL_Tree_Node* argument = va_arg(arguments, Arcadia_VPL_Tree_Node*);
  while (argument) {
    Arcadia_List_insertBackObjectReferenceValue(thread, tree->call.arguments, (Arcadia_Object*)argument);
    argument = va_arg(arguments, Arcadia_VPL_Tree_Node*);
  }
}

static Arcadia_VPL_Tree_Node*
OnCall0
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* target,
    ...
  )
{
  va_list arguments;
  va_start(arguments, target);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_VPL_Tree_Node* tree = Arcadia_VPL_Tree_makeCall(thread, target);
    OnCall1(thread, tree, arguments);
    va_end(arguments);
    Arcadia_Thread_popJumpTarget(thread);
    return tree;
  } else {
    va_end(arguments);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

static void
OnStatementList1
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Tree_Node* tree,
    va_list arguments
  )
{
  Arcadia_VPL_Tree_Node* argument = va_arg(arguments, Arcadia_VPL_Tree_Node*);
  while (argument) {
    Arcadia_List_insertBackObjectReferenceValue(thread, tree->statementList, (Arcadia_Object*)argument);
    argument = va_arg(arguments, Arcadia_VPL_Tree_Node*);
  }
}

static Arcadia_VPL_Tree_Node*
OnStatementList0
  (
    Arcadia_Thread* thread,
    ...
  )
{
  va_list arguments;
  va_start(arguments, thread);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_VPL_Tree_Node* tree = Arcadia_VPL_Tree_makeStatementList(thread);
    OnStatementList1(thread, tree, arguments);
    va_end(arguments);
    Arcadia_Thread_popJumpTarget(thread);
    return tree;
  } else {
    va_end(arguments);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

static void
OnParameterList1
  (
    Arcadia_Thread* thread,
    Arcadia_List* list,
    va_list arguments
  )
{
  Arcadia_VPL_Tree_Node* argument = va_arg(arguments, Arcadia_VPL_Tree_Node*);
  while (argument) {
    Arcadia_List_insertBackObjectReferenceValue(thread, list, (Arcadia_Object*)argument);
    argument = va_arg(arguments, Arcadia_VPL_Tree_Node*);
  }
}

static Arcadia_List*
OnParameterList0
  (
    Arcadia_Thread* thread,
    ...
  )
{
  va_list arguments;
  va_start(arguments, thread);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_List* list = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    OnParameterList1(thread, list, arguments);
    va_end(arguments);
    Arcadia_Thread_popJumpTarget(thread);
    return list;
  } else {
    va_end(arguments);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultVertexShader
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Program* program,
    Arcadia_Map* constantBlockMapping,
    Arcadia_ByteBuffer* target
  )
{
  // The global scope.
  if (!program->scope) {
    Arcadia_VPL_SemanticalAnalysis_run(thread, self->semanticalAnalysis, program);
  }

  emitCxxString(thread, target, HEADER);

  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->variableScalars); i < n; ++i) {
    Arcadia_VPL_VariableScalar* variableScalar =
      (Arcadia_VPL_VariableScalar*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->variableScalars, i,
                                                                                         _Arcadia_VPL_VariableScalar_getType(thread));
    writeVariableScalar(thread, self, Context_VertexShader, (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void)), variableScalar, target);
  }

  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->constants); i < n; ++i) {
    Arcadia_VPL_Constant* constant = (Arcadia_VPL_Constant*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->constants, i, _Arcadia_VPL_Constant_getType(thread));
    if (Arcadia_VPL_Constant_getKind(thread, constant) == Arcadia_VPL_ConstantKind_Record) {
      writeConstantRecord(thread, self, Context_VertexShader, constantBlockMapping, (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void)),
                          (Arcadia_VPL_ConstantRecord*)constant, target);
    }
  }

#define OnVariableDefinition(_type, _name) Arcadia_VPL_Tree_makeVariableDefinition(thread, _type, _name)
#define OnAssignment(_lhs, _rhs) Arcadia_VPL_Tree_makeAssignment(thread, _lhs, _rhs)
#define OnName(_name) Arcadia_VPL_Tree_makeName(thread, Arcadia_String_createFromCxxString(thread, _name))
#define OnName2(_name) Arcadia_VPL_Tree_makeName(thread, mapName(thread, self, Arcadia_String_createFromCxxString(thread, _name)))
#define OnMultiply(_lhs, _rhs) Arcadia_VPL_Tree_makeMultiply(thread, _lhs, _rhs)
#define OnDivide(_lhs, _rhs) Arcadia_VPL_Tree_makeDivide(thread, _lhs, _rhs)
#define OnAdd(_lhs, _rhs) Arcadia_VPL_Tree_makeAdd(thread, _lhs, _rhs)
#define OnSubtract(_lhs, _rhs) Arcadia_VPL_Tree_makeSubtract(thread, _lhs, _rhs)
#define OnAccess(_lhs, _rhs) Arcadia_VPL_Tree_makeAccess(thread, _lhs, _rhs)
#define OnNumber(_number) Arcadia_VPL_Tree_makeNumber(thread, Arcadia_String_createFromCxxString(thread, _number))
#define OnCall(_target, ...) OnCall0(thread, _target, __VA_ARGS__ __VA_OPT__(,) NULL)
#define OnStatementList(...) OnStatementList0(thread, __VA_ARGS__ __VA_OPT__(,) NULL)
#define OnParameterList(...) OnParameterList0(thread, __VA_ARGS__ __VA_OPT__(,) NULL)
#define OnFunctionDefinition(_returnValueType, _name, _parameters, _body) \
  Arcadia_VPL_Tree_makeFunctionDefinition(thread, _returnValueType, _name, _parameters, _body)

  static const char* DEFINES =
    "#define _1_vertexPosition gl_Position\n" // We use a #define to rename gl_Position to _1_vertexPosition.
    ;

  Arcadia_VPL_Tree_Node* vertexColorAssignmentTree = NULL;
  if (program->flags == Arcadia_VPL_ProgramFlags_MeshAmbientColor) {
    vertexColorAssignmentTree =
      OnAssignment
        (
          OnName2("fragmentProgram.inputs.vertex.ambientColor"),
          OnAccess
            (
              OnName2("vertexProgram.inputs.mesh"),
              OnName("ambientColor") // getGlobal("vertexProgram.inputs.mesh.ambientColor")
            )
        );
  } else if (program->flags == Arcadia_VPL_ProgramFlags_VertexAmbientColor) {
    vertexColorAssignmentTree =
      OnAssignment
        (
          OnName2("fragmentProgram.inputs.vertex.ambientColor"),
          OnName2("vertexProgram.inputs.vertex.ambientColor")
        );
  } else if (program->flags == Arcadia_VPL_ProgramFlags_TextureAmbientColor) {
    vertexColorAssignmentTree =
      OnAssignment
      (
        OnName2("fragmentProgram.inputs.vertex.ambientColor"),
        OnName2("vertexProgram.inputs.vertex.ambientColor")
      );
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_VPL_Tree_Node* mainFunctionDefinitionTree =
    OnFunctionDefinition
    (
      OnName("void"),
      OnName("main"),
      OnParameterList(),
      OnStatementList
        (
          OnVariableDefinition
            (
              OnName("mat4"),
              OnName("mvp")
            ),
          OnAssignment
            (
              OnName("mvp"),
              OnMultiply
                (
                  OnAccess
                    (
                      OnName2("vertexProgram.inputs.viewer"),
                      OnName("viewToProjection")
                    ),
                  OnMultiply
                    (
                      OnAccess
                        (
                          OnName2("vertexProgram.inputs.viewer"),
                          OnName("worldToView")
                        ),
                      OnAccess
                        (
                          OnName2("vertexProgram.inputs.model"),
                          OnName("localToWorld")
                        )
                    )
                )
            ),
          OnAssignment
            (
              OnName2("fragmentProgram.inputs.vertex.position"),
              OnMultiply
                (
                  OnName("mvp"),
                  OnCall
                    (
                      OnName("vec4"),
                      OnAccess(OnName2("vertexProgram.inputs.vertex.position"), OnName("xyz")), // getGlobal("vertexProgram.inputs.vertex.position")
                      OnName("1.0")
                    )
                )
            ),
          OnAssignment
            (
              OnName2("fragmentProgram.inputs.vertex.ambientColorTextureCoordinate"),
              OnName2("vertexProgram.inputs.vertex.ambientColorTextureCoordinate")
            ),
          vertexColorAssignmentTree                                  
        )
    );

  emitCxxString(thread, target, DEFINES);
  onFunctionDefinitionTree(thread, self, mainFunctionDefinitionTree, target);

  // the zero terminator
  Arcadia_ByteBuffer_insertBackBytes(thread, target, &ZEROTERMINATOR, 1);
}

void
Arcadia_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_VPL_Program* program,
    Arcadia_Map* constantBlockMapping,
    Arcadia_ByteBuffer* target
  )
{
  // The global scope.
  if (!program->scope) {
    Arcadia_VPL_SemanticalAnalysis_run(thread, self->semanticalAnalysis, program);
  }

  emitCxxString(thread, target, HEADER);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->variableScalars); i < n; ++i) {
    Arcadia_VPL_VariableScalar* variableScalar =
      (Arcadia_VPL_VariableScalar*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->variableScalars, i,
                                                                                         _Arcadia_VPL_VariableScalar_getType(thread));
    writeVariableScalar(thread, self, Context_FragmentShader, (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void)), variableScalar, target);
  }

  Arcadia_VPL_Tree_Node* fragmentColorAssignmentTree = NULL;
  if (program->flags == Arcadia_VPL_ProgramFlags_TextureAmbientColor) {
    fragmentColorAssignmentTree =
      OnAssignment
        (
          OnName2("rasterizerProgram.inputs.fragmentColor"),
          OnCall
            (
              OnName("texture2D"),
              OnName("_0_ambientColorTexture"),
              OnName2("fragmentProgram.inputs.vertex.ambientColorTextureCoordinate")
            )
        );
  } else {
    fragmentColorAssignmentTree = OnAssignment(OnName2("rasterizerProgram.inputs.fragmentColor"), OnName2("fragmentProgram.inputs.vertex.ambientColor"));
  }

  Arcadia_VPL_Tree_Node* mainFunctionDefinitionTree =
    OnFunctionDefinition
      (
        OnName("void"),
        OnName("main"),
        OnParameterList(),
        OnStatementList(fragmentColorAssignmentTree)
      );
  onFunctionDefinitionTree(thread, self, mainFunctionDefinitionTree, target);
  Arcadia_ByteBuffer_insertBackBytes(thread, target, &ZEROTERMINATOR, 1);
}
