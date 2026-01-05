#include "Arcadia/Visuals/VPL/Tree.h"

static void
Arcadia_Visuals_VPL_Tree_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* self
  );

static void
Arcadia_Visuals_VPL_Tree_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_TreeDispatch* self
  );

static void
Arcadia_Visuals_VPL_Block_Field_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_VPL_Tree_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};


Arcadia_defineObjectType(u8"Arcadia.Visuals.VPL.Tree", Arcadia_Visuals_VPL_Tree,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_VPL_Tree_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_VPL_Tree_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Empty;
  self->functionDefinition.name = NULL;
  self->functionDefinition.returnValueType = NULL;
  self->functionDefinition.parameters = NULL;
  self->functionDefinition.body = NULL;
  self->parameterVariableDefinition.name = NULL;
  self->parameterVariableDefinition.type = NULL;
  self->literal = NULL;
  self->statementList = NULL;
  self->name = NULL;
  self->call.arguments = NULL;
  self->call.target = NULL;
  self->access.lhs = NULL;
  self->access.rhs = NULL;
  self->add.lhs = NULL;
  self->add.rhs = NULL;
  self->subtract.lhs = NULL;
  self->subtract.rhs = NULL;
  self->multiply.lhs = NULL;
  self->multiply.rhs = NULL;
  self->divide.lhs = NULL;
  self->divide.rhs = NULL;
  self->variableDefinition.type = NULL; self->variableDefinition.name = NULL;
  self->assignment.lhs = NULL; self->assignment.rhs = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Visuals_VPL_Tree_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_TreeDispatch* self
  )
{ }

static void
Arcadia_Visuals_VPL_Block_Field_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* self
  )
{
  if (self->functionDefinition.name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->functionDefinition.name);
  }
  if (self->functionDefinition.returnValueType) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->functionDefinition.returnValueType);
  }
  if (self->functionDefinition.parameters) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->functionDefinition.parameters);
  }
  if (self->functionDefinition.body) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->functionDefinition.body);
  }


  if (self->parameterVariableDefinition.name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parameterVariableDefinition.name);
  }
  if (self->parameterVariableDefinition.type) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->parameterVariableDefinition.type);
  }

  if (self->call.arguments) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->call.arguments);
  }
  if (self->call.target) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->call.target);
  }

  if (self->literal) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->literal);
  }

  if (self->access.lhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->access.lhs);
  }
  if (self->access.rhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->access.rhs);
  }

  if (self->add.lhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->add.lhs);
  }
  if (self->add.rhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->add.rhs);
  }

  if (self->subtract.lhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->subtract.lhs);
  }
  if (self->subtract.rhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->subtract.rhs);
  }

  if (self->multiply.lhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->multiply.lhs);
  }
  if (self->multiply.rhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->multiply.rhs);
  }

  if (self->divide.lhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->divide.lhs);
  }
  if (self->divide.rhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->divide.rhs);
  }

  if (self->statementList) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->statementList);
  }

  if (self->assignment.lhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->assignment.lhs);
  }
  if (self->assignment.rhs) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->assignment.rhs);
  }

  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }

  if (self->variableDefinition.type) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableDefinition.type);
  }
  if (self->variableDefinition.name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableDefinition.name);
  }
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_Visuals_VPL_Tree);
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeCall
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* target
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->call.target = target;
  self->call.arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Call;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeNumber
  (
    Arcadia_Thread* thread,
    Arcadia_String* literal
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->literal = literal;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Number;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeAccess
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->access.lhs = lhs;
  self->access.rhs = rhs;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Access;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeAdd
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->add.lhs = lhs;
  self->add.rhs = rhs;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Add;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeSubtract
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->subtract.lhs = lhs;
  self->subtract.rhs = rhs;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Subtract;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeMultiply
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->multiply.lhs = lhs;
  self->multiply.rhs = rhs;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Multiply;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeDivide
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->divide.lhs = lhs;
  self->divide.rhs = rhs;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Divide;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeName
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->name = name;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Name;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeStatementList
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->statementList = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->flags = Arcadia_Visuals_VPL_TreeFlags_StatementList;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeAssignment
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* lhs,
    Arcadia_Visuals_VPL_Tree* rhs
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->assignment.lhs = lhs;
  self->assignment.rhs = rhs;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_Assignment;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* type,
    Arcadia_Visuals_VPL_Tree* name
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->variableDefinition.type = type;
  self->variableDefinition.name = name;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_VariableDefinition;
  return self;
}

Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeParameterVariableDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* type,
    Arcadia_Visuals_VPL_Tree* name
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->parameterVariableDefinition.type = type;
  self->parameterVariableDefinition.name = name;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_ParameterVariableDefinition;
  return self;
}


Arcadia_Visuals_VPL_Tree*
Arcadia_Visuals_VPL_Tree_makeFunctionDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_Tree* returnValueType,
    Arcadia_Visuals_VPL_Tree* name,
    Arcadia_List* parameters,
    Arcadia_Visuals_VPL_Tree* body
  )
{
  Arcadia_Visuals_VPL_Tree* self = Arcadia_Visuals_VPL_Tree_create(thread);
  self->functionDefinition.name = name;
  self->functionDefinition.returnValueType = returnValueType;
  self->functionDefinition.parameters = parameters;
  self->functionDefinition.body = body;
  self->flags = Arcadia_Visuals_VPL_TreeFlags_FunctionDefinition;
  return self;
}
