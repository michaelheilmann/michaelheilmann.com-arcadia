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

#define ARCADIA_ENGINE_PRIVATE (1)
#include "Arcadia/Engine/Node.h"

static void
Arcadia_Engine_Node_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self
  );

static void
Arcadia_Engine_Node_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_NodeDispatch* self
  );

static void
Arcadia_Engine_Node_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self
  );

static void
Arcadia_Engine_Node_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Node_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_Engine_Node_construct,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Engine_Node_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Node_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Node_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Node_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcardia.Engine.Node", Arcadia_Engine_Node,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Engine_Node_typeOperations);

static void
Arcadia_Engine_Node_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Node_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Engine_Node_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_NodeDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Node_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Engine_Node_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self
  )
{/*Intentionally empty.*/}

void
Arcadia_Engine_Node_setAudialsBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self,
    Arcadia_Engine_Audials_BackendContext* backendContext
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Node, setAudialsBackendContext, self, backendContext); }

void
Arcadia_Engine_Node_setVisualsBackendContext
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Node* self,
    Arcadia_Engine_Visuals_BackendContext* backendContext
  )
{ Arcadia_VirtualCall(Arcadia_Engine_Node, setVisualsBackendContext, self, backendContext); }
