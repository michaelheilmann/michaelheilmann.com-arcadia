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

#include "Arcadia/Visuals/Implementation/VPL/GLSL/Transpiler.h"

#include "Arcadia/Languages/Include.h"
#include "Arcadia/Visuals/Include.h"
#include <string.h>


static const char ZEROTERMINATOR =
  '\0'
  ;

static const char* HEADER =
  "#version 330 core\n"
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
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_String* type,
    Arcadia_ByteBuffer* target
  );

static void
writeVariableScalar
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* symbols,
    Arcadia_Visuals_VPL_VariableScalar* variableScalar,
    Arcadia_ByteBuffer* target
  );

static void
writeConstantBlock
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* symbols,
    Arcadia_Visuals_VPL_ConstantBlock* constantBlock,
    Arcadia_ByteBuffer* target
  );

static void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self
  );

static void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_TranspilerDispatch* self
  );

static void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};


Arcadia_defineObjectType(u8"Arcadia.Visuals.VPL.Backends.GLSL.Transpiler", Arcadia_Visuals_VPL_Backends_GLSL_Transpiler,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Languages_StringTable* stringTable = Arcadia_Languages_StringTable_getOrCreate(thread);
  self->MAT4 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"mat4");
  self->VEC3 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec3");
  self->VEC4 = Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, stringTable, u8"vec4");
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_TranspilerDispatch* self
  )
{ }

static void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self
  )
{
  if (self->MAT4) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->MAT4);
  }
  if (self->VEC3) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->VEC3);
  }
  if (self->VEC4) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->VEC4);
  }
}

Arcadia_Visuals_VPL_Backends_GLSL_Transpiler*
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_VPL_Backends_GLSL_Transpiler);
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
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_String* type,
    Arcadia_ByteBuffer* target
  )
{
  Arcadia_Value v = Arcadia_Value_makeObjectReferenceValue(type);
  if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->MAT4, &v)) {
    emitString(thread, target, self->MAT4);
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->VEC3, &v)) {
    emitString(thread, target, self->VEC3);
  } else if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)self->VEC4, &v)) {
    emitString(thread, target, self->VEC4);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
}

static void
writeVariableScalar
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* symbols,
    Arcadia_Visuals_VPL_VariableScalar* variableScalar,
    Arcadia_ByteBuffer* target
  )
{
  switch (context) {
    case Context_VertexShader: {
      if (variableScalar->flags == Arcadia_Visuals_VPL_VariableScalarFlags_Vertex) {
        emitCxxString(thread, target, "layout(location = ");
        emitString(thread, target, Arcadia_String_createFromInteger32(thread, variableScalar->location));
        emitCxxString(thread, target, u8") ");
        emitCxxString(thread, target, u8"in");
        emitCxxString(thread, target, u8" ");
        writeType(thread, self, variableScalar->type, target);
        emitCxxString(thread, target, u8" ");
        emitString(thread, target, variableScalar->name);
        emitCxxString(thread, target, u8";\n");
      } else if (variableScalar->flags == Arcadia_Visuals_VPL_VariableScalarFlags_Fragment) {
        emitCxxString(thread, target, u8"out");
        emitCxxString(thread, target, u8" ");
        writeType(thread, self, variableScalar->type, target);
        emitCxxString(thread, target, u8" ");
        emitString(thread, target, variableScalar->name);
        emitCxxString(thread, target, u8";\n");
      }
    } break;
    case Context_FragmentShader: {
      if (variableScalar->flags == Arcadia_Visuals_VPL_VariableScalarFlags_Fragment) {
        emitCxxString(thread, target, u8"in");
        emitCxxString(thread, target, u8" ");
        writeType(thread, self, variableScalar->type, target);
        emitCxxString(thread, target, u8" ");
        emitString(thread, target, variableScalar->name);
        emitCxxString(thread, target, u8";\n");
      } else if (variableScalar->flags == Arcadia_Visuals_VPL_VariableScalarFlags_FrameBuffer) {
        emitCxxString(thread, target, u8"out");
        emitCxxString(thread, target, u8" ");
        writeType(thread, self, variableScalar->type, target);
        emitCxxString(thread, target, u8" ");
        emitString(thread, target, variableScalar->name);
        emitCxxString(thread, target, u8";\n");
      }
    } break;
  };
}

static void
writeConstantBlock
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Context context,
    Arcadia_Map* symbols,
    Arcadia_Visuals_VPL_ConstantBlock* constantBlock,
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

  Arcadia_List* fields = Arcadia_Visuals_VPL_ConstantBlock_getFields(thread, constantBlock);
  emitCxxString(thread, target, u8"layout(std140) uniform ");
  Arcadia_ByteBuffer_insertBackBytes(thread, target, Arcadia_String_getBytes(thread, name), Arcadia_String_getNumberOfBytes(thread, name));
  emitCxxString(thread, target, u8" {\n");
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)fields); i < n; ++i) {
    Arcadia_Visuals_VPL_Field* field = Arcadia_List_getObjectReferenceValueAt(thread, fields, i);
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
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  );

static void
onExpressionTree
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  );

static void
onNameTree
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  );

static void
onStatementListTree
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  );

static void
onFunctionDefinitionTree
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  );

static void
onParameterVaribleDefinitionTree
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  )
{
  if (tree->flags != Arcadia_Visuals_VPL_TreeFlags_ParameterVariableDefinition) {
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
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  )
{
  switch (tree->flags) {
    case Arcadia_Visuals_VPL_TreeFlags_Access: {
      emitCxxString(thread, target, "(");
      onExpressionTree(thread, self, tree->access.lhs, target);
      emitCxxString(thread, target, ".");
      onExpressionTree(thread, self, tree->access.rhs, target);
      emitCxxString(thread, target, ")");
    } break;
    case Arcadia_Visuals_VPL_TreeFlags_Add: {
      emitCxxString(thread, target, "(");
      onExpressionTree(thread, self, tree->add.lhs, target);
      emitCxxString(thread, target, " + ");
      onExpressionTree(thread, self, tree->add.rhs, target);
      emitCxxString(thread, target, ")");
    } break;
    case Arcadia_Visuals_VPL_TreeFlags_Subtract: {
      emitCxxString(thread, target, "(");
      onExpressionTree(thread, self, tree->subtract.lhs, target);
      emitCxxString(thread, target, " - ");
      onExpressionTree(thread, self, tree->subtract.rhs, target);
      emitCxxString(thread, target, ")");
    } break;
    case Arcadia_Visuals_VPL_TreeFlags_Multiply: {
      emitCxxString(thread, target, "(");
      onExpressionTree(thread, self, tree->multiply.lhs, target);
      emitCxxString(thread, target, " * ");
      onExpressionTree(thread, self, tree->multiply.rhs, target);
      emitCxxString(thread, target, ")");
    } break;
    case Arcadia_Visuals_VPL_TreeFlags_Divide: {
      emitCxxString(thread, target, "(");
      onExpressionTree(thread, self, tree->divide.lhs, target);
      emitCxxString(thread, target, " / ");
      onExpressionTree(thread, self, tree->divide.rhs, target);
      emitCxxString(thread, target, ")");
    } break;
    case Arcadia_Visuals_VPL_TreeFlags_Name: {
      emitString(thread, target, tree->name);
    } break;
    case Arcadia_Visuals_VPL_TreeFlags_Number: {
      emitCxxString(thread, target, "(");
      emitString(thread, target, tree->literal);
      emitCxxString(thread, target, ")");
    } break;
    case Arcadia_Visuals_VPL_TreeFlags_Call: {
      //emitCxxString(thread, target, "(");
      onExpressionTree(thread, self, tree->call.target, target);
      //emitCxxString(thread, target, ")");
      emitCxxString(thread, target, "(");
      if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->call.arguments) > 0) {
        Arcadia_Visuals_VPL_Tree* argument;
        argument = (Arcadia_Visuals_VPL_Tree*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->call.arguments, 0, _Arcadia_Visuals_VPL_Tree_getType(thread));
        onExpressionTree(thread, self, argument, target);
        for (Arcadia_SizeValue i = 1, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->call.arguments); i < n; ++i) {
          argument = (Arcadia_Visuals_VPL_Tree*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->call.arguments, i, _Arcadia_Visuals_VPL_Tree_getType(thread));
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
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  )
{
  if (tree->flags != Arcadia_Visuals_VPL_TreeFlags_Name) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  emitString(thread, target, tree->name);
}

static void
onStatementListTree
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  )
{
  if (tree->flags != Arcadia_Visuals_VPL_TreeFlags_StatementList) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->statementList); i < n; ++i) {
    Arcadia_Visuals_VPL_Tree* a = (Arcadia_Visuals_VPL_Tree*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->statementList, i,
                                                                                                           _Arcadia_Visuals_VPL_Tree_getType(thread));
    switch (a->flags) {
      case Arcadia_Visuals_VPL_TreeFlags_Assignment: {
        emitCxxString(thread, target, u8"  ");
        onExpressionTree(thread, self, a->assignment.lhs, target);
        emitCxxString(thread, target, u8" = ");
        onExpressionTree(thread, self, a->assignment.rhs, target);
        emitCxxString(thread, target, ";\n");
      } break;
      case Arcadia_Visuals_VPL_TreeFlags_VariableDefinition: {
        emitCxxString(thread, target, u8"  ");
        onNameTree(thread, self, a->variableDefinition.type, target);
        emitCxxString(thread, target, u8" ");
        onNameTree(thread, self, a->variableDefinition.name, target);
        emitCxxString(thread, target, ";\n");
      } break;
      case Arcadia_Visuals_VPL_TreeFlags_Access:
      case Arcadia_Visuals_VPL_TreeFlags_Add:
      case Arcadia_Visuals_VPL_TreeFlags_Call:
      case Arcadia_Visuals_VPL_TreeFlags_Divide:
      case Arcadia_Visuals_VPL_TreeFlags_Subtract:
      case Arcadia_Visuals_VPL_TreeFlags_Multiply:
      case Arcadia_Visuals_VPL_TreeFlags_Number: {
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
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Tree* tree,
    Arcadia_ByteBuffer* target
  )
{
  onNameTree(thread, self, tree->functionDefinition.returnValueType, target);
  emitCxxString(thread, target, " ");
  onNameTree(thread, self, tree->functionDefinition.name, target);
  emitCxxString(thread, target, "(");

  if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->functionDefinition.parameters) > 0) {
    Arcadia_Visuals_VPL_Tree* parameter;
    parameter = (Arcadia_Visuals_VPL_Tree*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->functionDefinition.parameters, 0, _Arcadia_Visuals_VPL_Tree_getType(thread));
    onParameterVaribleDefinitionTree(thread, self, parameter, target);
    for (Arcadia_SizeValue i = 1, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)tree->functionDefinition.parameters); i < n; ++i) {
      parameter = (Arcadia_Visuals_VPL_Tree*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, tree->functionDefinition.parameters, i, _Arcadia_Visuals_VPL_Tree_getType(thread));
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
    Arcadia_Visuals_VPL_Tree* tree,
    va_list arguments
  )
{
  Arcadia_Visuals_VPL_Tree* argument = va_arg(arguments, Arcadia_Visuals_VPL_Tree*);
  while (argument) {
    Arcadia_List_insertBackObjectReferenceValue(thread, tree->call.arguments, (Arcadia_Object*)argument);
    argument = va_arg(arguments, Arcadia_Visuals_VPL_Tree*);
  }
}

static Arcadia_Visuals_VPL_Tree*
OnCall0
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* target,
    ...
  )
{
  va_list arguments;
  va_start(arguments, target);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Visuals_VPL_Tree* tree = Arcadia_Visuals_VPL_Tree_makeCall(thread, target);
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
    Arcadia_Visuals_VPL_Tree* tree,
    va_list arguments
  )
{
  Arcadia_Visuals_VPL_Tree* argument = va_arg(arguments, Arcadia_Visuals_VPL_Tree*);
  while (argument) {
    Arcadia_List_insertBackObjectReferenceValue(thread, tree->statementList, (Arcadia_Object*)argument);
    argument = va_arg(arguments, Arcadia_Visuals_VPL_Tree*);
  }
}

static Arcadia_Visuals_VPL_Tree*
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
    Arcadia_Visuals_VPL_Tree* tree = Arcadia_Visuals_VPL_Tree_makeStatementList(thread);
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
  Arcadia_Visuals_VPL_Tree* argument = va_arg(arguments, Arcadia_Visuals_VPL_Tree*);
  while (argument) {
    Arcadia_List_insertBackObjectReferenceValue(thread, list, (Arcadia_Object*)argument);
    argument = va_arg(arguments, Arcadia_Visuals_VPL_Tree*);
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
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_writeDefaultVertexShader
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Program* program,
    Arcadia_ByteBuffer* target
  )
{
  emitCxxString(thread, target, HEADER);

  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->variableScalars); i < n; ++i) {
    Arcadia_Visuals_VPL_VariableScalar* variableScalar =
      (Arcadia_Visuals_VPL_VariableScalar*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->variableScalars, i,
                                                                                         _Arcadia_Visuals_VPL_VariableScalar_getType(thread));
    writeVariableScalar(thread, self, Context_VertexShader, (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void)), variableScalar, target);
  }

  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->constantBlocks); i < n; ++i) {
    Arcadia_Visuals_VPL_ConstantBlock* constantBlock =
    (Arcadia_Visuals_VPL_ConstantBlock*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->constantBlocks, i,
                                                                                      _Arcadia_Visuals_VPL_ConstantBlock_getType(thread));
    writeConstantBlock(thread, self, Context_VertexShader, (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void)), constantBlock, target);
  }

#define OnVariableDefinition(_type, _name) Arcadia_Visuals_VPL_Tree_makeVariableDefinition(thread, _type, _name)
#define OnAssignment(_lhs, _rhs) Arcadia_Visuals_VPL_Tree_makeAssignment(thread, _lhs, _rhs)
#define OnName(_name) Arcadia_Visuals_VPL_Tree_makeName(thread, Arcadia_String_createFromCxxString(thread, _name))
#define OnMultiply(_lhs, _rhs) Arcadia_Visuals_VPL_Tree_makeMultiply(thread, _lhs, _rhs)
#define OnDivide(_lhs, _rhs) Arcadia_Visuals_VPL_Tree_makeDivide(thread, _lhs, _rhs)
#define OnAdd(_lhs, _rhs) Arcadia_Visuals_VPL_Tree_makeAdd(thread, _lhs, _rhs)
#define OnSubtract(_lhs, _rhs) Arcadia_Visuals_VPL_Tree_makeSubtract(thread, _lhs, _rhs)
#define OnAccess(_lhs, _rhs) Arcadia_Visuals_VPL_Tree_makeAccess(thread, _lhs, _rhs)
#define OnNumber(_number) Arcadia_Visuals_VPL_Tree_makeNumber(thread, _number)
#define OnCall(_target, ...) OnCall0(thread, _target, __VA_ARGS__ __VA_OPT__(,) NULL)
#define OnStatementList(...) OnStatementList0(thread, __VA_ARGS__ __VA_OPT__(,) NULL)
#define OnParameterList(...) OnParameterList0(thread, __VA_ARGS__ __VA_OPT__(,) NULL)
#define OnFunctionDefinition(_returnValueType, _name, _parameters, _body) \
  Arcadia_Visuals_VPL_Tree_makeFunctionDefinition(thread, _returnValueType, _name, _parameters, _body)

  static const char* DEFINES =
    "#define _1_vertexPosition gl_Position\n" // We use a #define to rename gl_Position to _1_vertexPosition.
    ;

  Arcadia_Visuals_VPL_Tree* mainFunctionDefinitionTree =
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
                      OnName("_viewer0"),
                      OnName("projection")
                    ),
                  OnMultiply
                    (
                      OnAccess
                        (
                          OnName("_viewer0"),
                          OnName("view")
                        ),
                      OnAccess
                        (
                          OnName("_mesh0"),
                          OnName("model")
                        )
                    )
                )
            ),
          OnAssignment
            (
              OnName("_1_vertexPosition"),
              OnMultiply
                (
                  OnName("mvp"),
                  OnCall
                    (
                      OnName("vec4"),
                      OnAccess(OnName("_0_vertexPosition"), OnName("xyz")),
                      OnName("1.0")
                    )
                )
            ),
          OnAssignment
            (
              OnName("_1_vertexColor"),
              OnAccess
                (
                  OnName("_mesh0"),
                  OnName("color")
                )
            )                                       
        )
  );

  emitCxxString(thread, target, DEFINES);
  onFunctionDefinitionTree(thread, self, mainFunctionDefinitionTree, target);

  // the zero terminator
  Arcadia_ByteBuffer_insertBackBytes(thread, target, &ZEROTERMINATOR, 1);
}

void
Arcadia_Visuals_VPL_Backends_GLSL_Transpiler_writeDefaultFragmentShader
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Backends_GLSL_Transpiler* self,
    Arcadia_Visuals_VPL_Program* program,
    Arcadia_ByteBuffer* target
  )
{
  emitCxxString(thread, target, HEADER);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->variableScalars); i < n; ++i) {
    Arcadia_Visuals_VPL_VariableScalar* variableScalar =
      (Arcadia_Visuals_VPL_VariableScalar*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->variableScalars, i,
                                                                                         _Arcadia_Visuals_VPL_VariableScalar_getType(thread));
    writeVariableScalar(thread, self, Context_FragmentShader, (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void)), variableScalar, target);
  }

  Arcadia_Visuals_VPL_Tree* mainFunctionDefinitionTree =
    OnFunctionDefinition
      (
        OnName("void"),
        OnName("main"),
        OnParameterList(),
        OnStatementList(OnAssignment(OnName("_2_fragmentColor"), OnName("_1_vertexColor")))
      );
  onFunctionDefinitionTree(thread, self, mainFunctionDefinitionTree, target);
  Arcadia_ByteBuffer_insertBackBytes(thread, target, &ZEROTERMINATOR, 1);
}
