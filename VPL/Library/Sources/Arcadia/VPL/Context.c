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
#include "Arcadia/VPL/Context.h"

#include "Arcadia/VPL/EnterPhase.h"
#include "Arcadia/VPL/ResolvePhase.h"

static void
Arcadia_VPL_Context_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Context* self
  );

static void
Arcadia_VPL_Context_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ContextDispatch* self
  );

static void
Arcadia_VPL_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Context* self
  );

static void
Arcadia_VPL_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Context* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Context_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_VPL_Context_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Context_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_VPL_Context_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.Context", Arcadia_VPL_Context,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_VPL_Context_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Context* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Context);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->diagnostics = Arcadia_Languages_Diagnostics_create(thread, (Arcadia_Log*)Arcadia_ConsoleLog_create(thread));
  self->enterPhase = NULL;
  self->resolvePhase = NULL;
  Arcadia_LeaveConstructor(Arcadia_VPL_Context);
}

static void
Arcadia_VPL_Context_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_ContextDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_VPL_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Context* self
  )
{
  if (self->diagnostics) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->diagnostics);
  }
  if (self->enterPhase) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->enterPhase);
  }
  if (self->resolvePhase) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->resolvePhase);
  }
}

static void
Arcadia_VPL_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Context* self
  )
{/*Intentionally empty.*/}

Arcadia_VPL_Context*
Arcadia_VPL_Context_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Context);
}
