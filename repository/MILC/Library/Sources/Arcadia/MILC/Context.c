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
#include "Arcadia/MILC/Context.h"

#include "Arcadia/Logging/Include.h"
#include "Arcadia/MILC/Environment.h"
#include "Arcadia/MILC/MemberEnterPhase/ClassCompleter.h"
#include "Arcadia/MILC/MemberEnterPhase/EnumerationCompleter.h"
#include "Arcadia/MILC/Backend/Implementation.h"
#include "Arcadia/MILC/Scanner.h"

static void
Arcadia_MILC_Context_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* self
  );

static void
Arcadia_MILC_Context_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_ContextDispatch* self
  );

static void
Arcadia_MILC_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* self
  );

static void
Arcadia_MILC_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_Context_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_Context_destruct,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_Context_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_Context_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.Context", Arcadia_MILC_Context,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_MILC_Context_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Context);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->instances = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));

  self->stringTable = Arcadia_Languages_StringTable_getOrCreate(thread);
  self->log = (Arcadia_Log*)Arcadia_ConsoleLog_create(thread);
  self->diagnostics = Arcadia_Languages_Diagnostics_create(thread, self->log);

  self->workingDirectoryPath = NULL;

  self->moduleNodes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->scope = NULL;
  self->environments = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));

  Arcadia_LeaveConstructor(Arcadia_MILC_Context);
}

static void
Arcadia_MILC_Context_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_ContextDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_Context_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* self
  )
{
  if (self->instances) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->instances);
  }
  
  if (self->stringTable) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->stringTable);
  }
  if (self->log) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->log);
  }
  if (self->diagnostics) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->diagnostics);
  }

  if (self->workingDirectoryPath) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->workingDirectoryPath);
  }
  if (self->moduleNodes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->moduleNodes);
  }

  if (self->scope) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scope);
  }

  if (self->environments) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->environments);
  }
}

static void
Arcadia_MILC_Context_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* self
  )
{/*Intentionally empty.*/}

Arcadia_MILC_Context*
Arcadia_MILC_Context_create
  (
    Arcadia_Thread* thread
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_Context);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  _Arcadia_EndCreate(Arcadia_MILC_Context);
}
