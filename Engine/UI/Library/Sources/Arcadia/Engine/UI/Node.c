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

#define ARCADIA_ENGINE_UI_PRIVATE (1)
#include "Arcadia/Engine/UI/Node.h"

static void
Arcadia_Engine_UI_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_Node* self
  );

static void
Arcadia_Engine_UI_Node_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_NodeDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Engine_UI_Node_constructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Engine_UI_Node_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.UI.Node", Arcadia_Engine_UI_Node,
                         u8"Arcadia.Engine.Node", Arcadia_Engine_Node,
                         &_typeOperations);

static void
Arcadia_Engine_UI_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_Node* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Engine_UI_Node);
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_AST_DefinitionStatementNode);
}

static void
Arcadia_Engine_UI_Node_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_UI_NodeDispatch* self
  )
{/*Intentionally empty.*/}
