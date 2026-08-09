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

#define ARCADIA_MILC_PRIVATE (1)
#include "Arcadia/MILC/Environment.h"

#include "Arcadia/MILC/Symbols/Include.h"

static void
Arcadia_MILC_Environment_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Environment* self
  );

static void
Arcadia_MILC_Environment_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Environment* self
  );

static void
Arcadia_MILC_Environment_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnvironmentDispatch* self
  );

static void
Arcadia_MILC_Environment_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Environment* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_Environment_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_Environment_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_Environment_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_Environment_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.Environment", Arcadia_MILC_Environment,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_MILC_Environment_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Environment* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Environment);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->symbol = (Arcadia_MILC_Symbol*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_MILC_Symbol_getType(thread));
  self->compilationUnitNode = (Arcadia_MILC_AST_CompilationUnitNode*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MILC_AST_CompilationUnitNode_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_MILC_Environment);
}

static void
Arcadia_MILC_Environment_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Environment* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_Environment_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnvironmentDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_Environment_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Environment* self
  )
{
  if (self->symbol) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->symbol);
  }
  if (self->compilationUnitNode) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->compilationUnitNode);
  }
}

Arcadia_MILC_Environment*
Arcadia_MILC_Environment_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbol* symbol,
    Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_Environment);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)symbol);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)compilationUnitNode);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  _Arcadia_EndCreate(Arcadia_MILC_Environment);
}
