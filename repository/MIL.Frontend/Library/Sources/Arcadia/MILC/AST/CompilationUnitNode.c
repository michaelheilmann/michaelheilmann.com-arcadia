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

#include "Arcadia/MILC/AST/CompilationUnitNode.h"

#include "Arcadia/MILC/AST/Include.h"

/// @code
/// constructor()
/// @endcode
static void
Arcadia_MILC_AST_CompilationUnitNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNode* self
  );

static void
Arcadia_MILC_AST_CompilationUnitNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNodeDispatch* self
  );

static void
Arcadia_MILC_AST_CompilationUnitNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNode* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MILC_AST_CompilationUnitNode_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_AST_CompilationUnitNode_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_AST_CompilationUnitNode_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_AST_CompilationUnitNode_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _Arcadia_MILC_AST_CompilationUnitNode_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MILC_AST_CompilationUnitNode_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.CompilationUnitNode", Arcadia_MILC_AST_CompilationUnitNode,
                         u8"Arcadia.MILC.AST.Node", Arcadia_MILC_AST_Node,
                         &_Arcadia_MILC_AST_CompilationUnitNode_typeOperations);

static void
Arcadia_MILC_AST_CompilationUnitNode_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNode* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_CompilationUnitNode);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->moduleNode = NULL;
  self->filePath = NULL;
  self->definitions = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_CompilationUnitNode);
}

static void
Arcadia_MILC_AST_CompilationUnitNode_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_AST_CompilationUnitNode_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNode* self
  )
{
  if (self->moduleNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->moduleNode);
  }
  if (self->filePath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->filePath);
  }
  if (self->definitions) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->definitions); 
  }
}

Arcadia_MILC_AST_CompilationUnitNode*
Arcadia_MILC_AST_CompilationUnitNode_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_AST_CompilationUnitNode);
}

void
Arcadia_MILC_AST_CompilationUnitNode_appendDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNode* self,
    Arcadia_MILC_AST_DefinitionNode* definition
  )
{
  Arcadia_List_insertBackObjectReferenceValue(thread, self->definitions, (Arcadia_ObjectReferenceValue)definition);
}

Arcadia_SizeValue
Arcadia_MILC_AST_CompilationUnitNode_getNumberOfDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNode* self
  )
{ return Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->definitions); }

Arcadia_MILC_AST_DefinitionNode*
Arcadia_MILC_AST_CompilationUnitNode_getDefinitionAt
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_CompilationUnitNode* self,
    Arcadia_SizeValue index
  )
{
  Arcadia_Value definitionAstValue = Arcadia_List_getAt(thread, self->definitions, index);
  Arcadia_MILC_AST_DefinitionNode* definitionAst = Arcadia_Value_getObjectReferenceValue(&definitionAstValue);
  return definitionAst;
}
