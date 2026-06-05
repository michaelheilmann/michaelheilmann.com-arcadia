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

#include "Arcadia/MILC/AST/Visitor.h"

#include "Arcadia/MILC/Include.h"
#include <assert.h>

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VisitorDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.AST.Visitor", Arcadia_MILC_AST_Visitor,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_AST_Visitor);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_Visitor);
}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_VisitorDispatch* self
  )
{/*Intentionally empty.*/}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self
  )
{/*Intentionally empty.*/}

void
Arcadia_MILC_AST_Visitor_visitModuleNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self,
    Arcadia_MILC_AST_ModuleNode* node
  )
{ Arcadia_VirtualCall(Arcadia_MILC_AST_Visitor, visitModuleNode, self, node); }

void
Arcadia_MILC_AST_Visitor_visitModuleDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self,
    Arcadia_MILC_AST_ModuleDefinitionNode* node
  )
{ Arcadia_VirtualCall(Arcadia_MILC_AST_Visitor, visitModuleDefinitionNode, self, node); }

void
Arcadia_MILC_AST_Visitor_visitProcedureDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self,
    Arcadia_MILC_AST_ProcedureDefinitionNode* node
  )
{ Arcadia_VirtualCall(Arcadia_MILC_AST_Visitor, visitProcedureDefinitionNode, self, node); }

void
Arcadia_MILC_AST_Visitor_visitClassDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self,
    Arcadia_MILC_AST_ClassDefinitionNode* node
  )
{ Arcadia_VirtualCall(Arcadia_MILC_AST_Visitor, visitClassDefinitionNode, self, node); }

void
Arcadia_MILC_AST_Visitor_visitEnumerationDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_AST_Visitor* self,
    Arcadia_MILC_AST_EnumerationDefinitionNode* node
  )
{ Arcadia_VirtualCall(Arcadia_MILC_AST_Visitor, visitEnumerationDefinitionNode, self, node); }
