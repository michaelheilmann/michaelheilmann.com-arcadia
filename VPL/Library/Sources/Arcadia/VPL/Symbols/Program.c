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
#include "Arcadia/VPL/Symbols/Program.h"

#include "Arcadia/Languages/Include.h"
#include "Arcadia/VPL/Tree/Include.h"
#include "Arcadia/VPL/SemanticalAnalysis.h"
#include "Arcadia/VPL/Symbols/Include.h"

static Arcadia_String*
S
  (
    Arcadia_Thread* thread,
    const char* string
  )
{
  return Arcadia_Languages_StringTable_getOrCreateStringFromCxxString(thread, Arcadia_Languages_StringTable_getOrCreate(thread), string);
}

// Create the syntactic form for the builtin procedures of the default program.
// The procedures are program-scope.
static Arcadia_List*
createBuiltinProcedureDefns
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{
  Arcadia_List* defns = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  {
    Arcadia_List* modifiers = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    Arcadia_List_insertBackObjectReferenceValue(thread, modifiers, S(thread, "builtin"));
    Arcadia_List* parameters = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    Arcadia_List* body = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    Arcadia_VPL_Tree_ProcedureDefnNode* defn = Arcadia_VPL_Tree_ProcedureDefnNode_create(thread, modifiers,
                                                                                                 Arcadia_VPL_Tree_NameExprNode_create(thread, self->VEC2->name),
                                                                                                 S(thread, u8"texture2D"),
                                                                                                 parameters,
                                                                                                 body);
    Arcadia_List_insertBackObjectReferenceValue(thread, defns, (Arcadia_Object*)defn);
  }
  return defns;
}

// Create the syntactic form for the constant variable of the default program.
static Arcadia_List*
createConstantScalarDefns
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{
  Arcadia_List* defns = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  {
    Arcadia_VPL_Tree_VariableDefnNode* defn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"ambientColorTexture"),
                                                                                               self->SAMPLER2D->name);
    Arcadia_String* CONSTANT = S(thread, u8"constant");
    Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, (Arcadia_Object*)CONSTANT);
    Arcadia_List_insertBackObjectReferenceValue(thread, defns, (Arcadia_Object*)defn);
  }
  return defns;
}

// Create the syntactic form for the constant records of the default program.
static Arcadia_List*
createConstantRecordDefns
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{
  Arcadia_List* defns = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_VPL_Tree_ConstantRecordDefnNode* defn = NULL;
  Arcadia_VPL_Tree_VariableDefnNode* varDefn = NULL;
  {
    // "viewer" constant block
    defn = Arcadia_VPL_Tree_ConstantRecordDefnNode_create(thread, S(thread, u8"viewer"));
    // "viewer.viewToProjection" field
    varDefn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"viewToProjection"),
                                                               self->MAT4->name);
    Arcadia_List_insertBackObjectReferenceValue(thread, defn->fields, varDefn);
    // "viewer.worldToView" field
    varDefn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"worldToView"),
                                                               self->MAT4->name);
    Arcadia_List_insertBackObjectReferenceValue(thread, defn->fields, varDefn);

    Arcadia_List_insertBackObjectReferenceValue(thread, defns, (Arcadia_Object*)defn);
  }
  {
    // "model" constant block
    defn = Arcadia_VPL_Tree_ConstantRecordDefnNode_create(thread, S(thread, u8"model"));
    // "model.localToWorld" field
    varDefn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"localToWorld"),
                                                               self->MAT4->name);
    Arcadia_List_insertBackObjectReferenceValue(thread, defn->fields, varDefn);

    Arcadia_List_insertBackObjectReferenceValue(thread, defns, (Arcadia_Object*)defn);
  }
  {
    // "mesh" constant block
    defn = Arcadia_VPL_Tree_ConstantRecordDefnNode_create(thread, S(thread, u8"mesh"));

    // "mesh.ambientColor" field
    varDefn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"ambientColor"),
                                                               self->VEC4->name);
    Arcadia_List_insertBackObjectReferenceValue(thread, defn->fields, varDefn);

    Arcadia_List_insertBackObjectReferenceValue(thread, defns, (Arcadia_Object*)defn);
  }
  return defns;
}

static Arcadia_List*
createVariableScalarDefns
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{
  Arcadia_List* defns = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_VPL_Tree_VariableDefnNode* defn = NULL;

  // the xyz position of the vertex
  defn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"vertexProgram_inputs_vertex_position"),
                                                          self->VEC3->name);
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"vertex"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"variable"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defns, defn);

  // the rgba ambient color of the vertex
  defn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"vertexProgram_inputs_vertex_ambientColor"),
                                                          self->VEC4->name);
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"vertex"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"variable"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defns, defn);

  // the texture coordinate of the vertex adressing the ambient color texture
  defn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"vertexProgram_inputs_vertex_ambientColorTextureCoordinate"),
                                                          self->VEC2->name);
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"vertex"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"variable"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defns, defn);

  // the xyzw coordinate of the vertex (gl_Position) in the vertex shader
  // the xyzw coordinates of the fragment (gl_FragCoord) in the fragment shader
  defn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"fragmentProgram_inputs_vertex_position"),
                                                          self->VEC4->name);
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"fragment"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"variable"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"position"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defns, defn);


  // the texture coordinate of the vertex adressing the ambient color texture
  defn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"fragmentProgram_inputs_vertex_ambientColorTextureCoordinate"),
                                                          self->VEC2->name);
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"fragment"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"variable"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defns, defn);

  // the rgba ambient color of the vertex
  defn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"fragmentProgram_inputs_vertex_ambientColor"),
                                                          self->VEC4->name);
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"fragment"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"variable"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defns, defn);


  // the rgba ambient color of the fragment
  defn = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, u8"rasterizerProgram_inputs_fragmentColor"),
                                                          self->VEC4->name);
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"pixel"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defn->modifiers, S(thread, u8"variable"));
  Arcadia_List_insertBackObjectReferenceValue(thread, defns, defn);


  return defns;
}

static void
createVertexShaderMainFunction
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{
  Arcadia_List* modifiers = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, modifiers, (Arcadia_Object*)S(thread, u8"vertex"));
  Arcadia_VPL_Tree_ProcedureDefnNode* procedureDefnNode = Arcadia_VPL_Tree_ProcedureDefnNode_create(thread, modifiers,
                                                                                                            Arcadia_VPL_Tree_NameExprNode_create(thread, S(thread, u8"void")),
                                                                                                            S(thread, u8"main"),
                                                                                                            (Arcadia_List*)Arcadia_ArrayList_create(thread),
                                                                                                            (Arcadia_List*)Arcadia_ArrayList_create(thread));
  Arcadia_VPL_Symbols_Procedure* procedure = Arcadia_VPL_Symbols_Procedure_create(thread, 0, procedureDefnNode->name, (Arcadia_VPL_Symbols_Symbol*)self->vertexStage, (Arcadia_VPL_Tree_Node*)procedureDefnNode);
  (NULL != procedure);
}

static void
createFragmentShaderMainFunction
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{
  Arcadia_List* modifiers = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, modifiers, (Arcadia_Object*)S(thread, u8"fragment"));
  Arcadia_VPL_Tree_ProcedureDefnNode* procedureDefnNode = Arcadia_VPL_Tree_ProcedureDefnNode_create(thread, modifiers,
                                                                                                            Arcadia_VPL_Tree_NameExprNode_create(thread, S(thread, u8"void")),
                                                                                                            S(thread, u8"main"),
                                                                                                            (Arcadia_List*)Arcadia_ArrayList_create(thread),
                                                                                                            (Arcadia_List*)Arcadia_ArrayList_create(thread));
  Arcadia_VPL_Symbols_Procedure* procedure = Arcadia_VPL_Symbols_Procedure_create(thread, 0, procedureDefnNode->name, (Arcadia_VPL_Symbols_Symbol*)self->fragmentStage, (Arcadia_VPL_Tree_Node*)procedureDefnNode);
  (NULL != procedure);
}

static void
Arcadia_VPL_Symbols_Program_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  );

static void
Arcadia_VPL_Symbols_Program_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_ProgramDispatch* self
  );

static void
Arcadia_VPL_Symbols_Program_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  );

static void
Arcadia_VPL_Symbols_Program_resolveTypesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Symbols_Program_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Symbols_Program_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.Symbols.Program", Arcadia_VPL_Symbols_Program,
                         u8"Arcadia.VPL.Symbols.Symbol", Arcadia_VPL_Symbols_Symbol,
                         &_typeOperations);

static void
Arcadia_VPL_Symbols_Program_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Symbols_Program);
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

  self->MAT4 = Arcadia_VPL_Symbols_BuiltinType_create(thread, S(thread, u8"mat4"));
  self->SAMPLER2D = Arcadia_VPL_Symbols_BuiltinType_create(thread, S(thread, u8"sampler2D"));
  self->VEC2 = Arcadia_VPL_Symbols_BuiltinType_create(thread, S(thread, u8"vec2"));
  self->VEC3 = Arcadia_VPL_Symbols_BuiltinType_create(thread, S(thread, u8"vec3"));
  self->VEC4 = Arcadia_VPL_Symbols_BuiltinType_create(thread, S(thread, u8"vec4"));
  self->VOID = Arcadia_VPL_Symbols_BuiltinType_create(thread, S(thread, u8"void"));

  Arcadia_VPL_Symbols_Variable* symbol;
  Arcadia_VPL_Tree_VariableDefnNode* defnNode;
  {
    self->VEC2->scope = Arcadia_Languages_Scope_create(thread, NULL);
    {
      defnNode = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, "xy"), self->VEC2->name);
      symbol = Arcadia_VPL_Symbols_Variable_create(thread, defnNode->name, (Arcadia_VPL_Symbols_Symbol*)self->VEC2, (Arcadia_VPL_Symbols_Symbol*)self->VEC2,
                                                   (Arcadia_VPL_Tree_Node*)defnNode);
      Arcadia_Languages_Scope_enter(thread, self->VEC2->scope, symbol->name, (Arcadia_Object*)symbol);
    }
  }
  {
    self->VEC3->scope = Arcadia_Languages_Scope_create(thread, NULL);
    Arcadia_VPL_Symbols_Variable* symbol;
    {
      defnNode = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, "xy"), self->VEC2->name);
      symbol = Arcadia_VPL_Symbols_Variable_create(thread, defnNode->name, (Arcadia_VPL_Symbols_Symbol*)self->VEC2, (Arcadia_VPL_Symbols_Symbol*)self->VEC3,
                                                   (Arcadia_VPL_Tree_Node*)defnNode);
      Arcadia_Languages_Scope_enter(thread, self->VEC3->scope, symbol->name, (Arcadia_Object*)symbol);
    }
    {
      defnNode = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, "xyz"), self->VEC3->name);
      symbol = Arcadia_VPL_Symbols_Variable_create(thread, defnNode->name, (Arcadia_VPL_Symbols_Symbol*)self->VEC3, (Arcadia_VPL_Symbols_Symbol*)self->VEC3,
                                                   (Arcadia_VPL_Tree_Node*)defnNode);
      Arcadia_Languages_Scope_enter(thread, self->VEC3->scope, symbol->name, (Arcadia_Object*)symbol);
    }
  }
  {
    self->VEC4->scope = Arcadia_Languages_Scope_create(thread, NULL);
    Arcadia_VPL_Symbols_Variable* symbol;
    {
      defnNode = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, "xy"), self->VEC2->name);
      symbol = Arcadia_VPL_Symbols_Variable_create(thread, defnNode->name, (Arcadia_VPL_Symbols_Symbol*)self->VEC2, (Arcadia_VPL_Symbols_Symbol*)self->VEC4,
                                                   (Arcadia_VPL_Tree_Node*)defnNode);
      Arcadia_Languages_Scope_enter(thread, self->VEC4->scope, symbol->name, (Arcadia_Object*)symbol);
    }
    {
      defnNode = Arcadia_VPL_Tree_VariableDefnNode_create(thread, S(thread, "xyz"), self->VEC3->name);
      symbol = Arcadia_VPL_Symbols_Variable_create(thread, defnNode->name, (Arcadia_VPL_Symbols_Symbol*)self->VEC3, (Arcadia_VPL_Symbols_Symbol*)self->VEC4,
                                                   (Arcadia_VPL_Tree_Node*)defnNode);
      Arcadia_Languages_Scope_enter(thread, self->VEC4->scope, symbol->name, (Arcadia_Object*)symbol);
    }
  }

  self->vertexStage = NULL;
  self->fragmentStage = NULL;

  self->constants = (Arcadia_List*)Arcadia_ArrayList_create(thread);

  Arcadia_LeaveConstructor(Arcadia_VPL_Symbols_Program);
}

static void
Arcadia_VPL_Symbols_Program_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_ProgramDispatch* self
  )
{ 
  ((Arcadia_VPL_Symbols_SymbolDispatch*)self)->resolveTypes = (void (*)(Arcadia_Thread*, Arcadia_VPL_Symbols_Symbol*)) & Arcadia_VPL_Symbols_Program_resolveTypesImpl;
}

static void
Arcadia_VPL_Symbols_Program_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{
  if (self->vertexStage) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->vertexStage);
  }
  if (self->fragmentStage) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->fragmentStage);
  }
  if (self->scope) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scope);
  }
  if (self->MAT4) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->MAT4);
  }
  if (self->SAMPLER2D) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->SAMPLER2D);
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
  if (self->VOID) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->VOID);
  }
  if (self->constants) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->constants);
  }
  if (self->programDefnNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->programDefnNode);
  }
}

static void
Arcadia_VPL_Symbols_Program_resolveTypesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{/*Intentionally empty.*/}

Arcadia_VPL_Symbols_Program*
Arcadia_VPL_Symbols_Program_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, flags);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Symbols_Program);
}

Arcadia_VPL_Symbols_ConstantRecord*
Arcadia_VPL_Symbols_Program_getConstantRecordByName
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self,
    Arcadia_String* name
  )
{ 
  Arcadia_Value temporary = Arcadia_Value_makeObjectReferenceValue(name);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->constants); i < n; ++i) {
    Arcadia_VPL_Symbols_Constant* e = (Arcadia_VPL_Symbols_Constant*)Arcadia_List_getObjectReferenceValueAt(thread, self->constants, i);
    if (Arcadia_VPL_Symbols_Constant_getKind(thread, e) == Arcadia_VPL_ConstantKind_Record) {
      if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)Arcadia_VPL_Symbols_Symbol_getName(thread, (Arcadia_VPL_Symbols_Symbol*)e), &temporary)) {
        return (Arcadia_VPL_Symbols_ConstantRecord*)e;
      }
    }
  }
  return NULL;
}

Arcadia_List*
Arcadia_VPL_Symbols_Program_getConstants
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{ 
  Arcadia_List* clone = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->constants); i < n; ++i) {
    Arcadia_List_insertBack(thread, clone, Arcadia_List_getAt(thread, self->constants, i));
  }
  return clone;
}

Arcadia_VPL_Symbols_Program*
Arcadia_VPL_Symbols_Program_createProgram
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags
  )
{
  Arcadia_VPL_Symbols_Program* program = Arcadia_VPL_Symbols_Program_create(thread, flags);

  // (1) Create the semantical analysis.
  Arcadia_VPL_SemanticalAnalysis* semanticalAnalysis = Arcadia_VPL_SemanticalAnalysis_create(thread);

  program->programDefnNode = Arcadia_VPL_Tree_ProgramDefnNode_create(thread);

  // (2.1) Create the syntactic forms for the constant records
  {
    Arcadia_List* source = createConstantRecordDefns(thread, program);
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)source); i < n; ++i) {
      Arcadia_List_insertBackObjectReferenceValue(thread, program->programDefnNode->elements, Arcadia_List_getObjectReferenceValueCheckedAt(thread, source, i, _Arcadia_VPL_Tree_Node_getType(thread)));
    }
  }
  // (2.2) Create the syntactic forms for the constant scalars.
  {
    Arcadia_List* source = createConstantScalarDefns(thread, program);
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)source); i < n; ++i) {
      Arcadia_List_insertBackObjectReferenceValue(thread, program->programDefnNode->elements, Arcadia_List_getObjectReferenceValueCheckedAt(thread, source, i, _Arcadia_VPL_Tree_Node_getType(thread)));
    }
  }
  // (2.3) Create the syntactic forms for the variable scalars.
  {
    Arcadia_List* source = createVariableScalarDefns(thread, program);
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)source); i < n; ++i) {
      Arcadia_List_insertBackObjectReferenceValue(thread, program->programDefnNode->elements, Arcadia_List_getObjectReferenceValueCheckedAt(thread, source, i, _Arcadia_VPL_Tree_Node_getType(thread)));
    }
  }
  // (2.4) Create the syntactic forms for the builtin procedures.
  {
    Arcadia_List* source = createBuiltinProcedureDefns(thread, program);
    for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)source); i < n; ++i) {
      Arcadia_List_insertBackObjectReferenceValue(thread, program->programDefnNode->elements, Arcadia_List_getObjectReferenceValueCheckedAt(thread, source, i, _Arcadia_VPL_Tree_Node_getType(thread)));
    }
  }

  // (3) See description of method for more information.
  Arcadia_VPL_SemanticalAnalysis_step1(thread, semanticalAnalysis, program);
  //Arcadia_VPL_SemanticalAnalysis_step2(thread, semanticalAnalysis, program);

  Arcadia_VPL_Symbols_Symbol_resolveTypes(thread, (Arcadia_VPL_Symbols_Symbol*)program);
  Arcadia_VPL_SemanticalAnalysis_run(thread, semanticalAnalysis, program);
  return program;
}

void
Arcadia_VPL_Symbols_Program_resolveTypes
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* self
  )
{/*Intentionally empty.*/}
