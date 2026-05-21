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

#include "Arcadia/Languages/Diagnostics.h"

#include "Arcadia/Languages/Include.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticsDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
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

Arcadia_defineObjectType(u8"Arcadia.Languages.Diagnostics", Arcadia_Languages_Diagnostics,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Languages_Diagnostics);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->log = (Arcadia_Log*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Log_getType(thread));
  self->diagnostics = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_LeaveConstructor(Arcadia_Languages_Diagnostics);
}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticsDispatch* self
  )
{/*Intentionally empty.*/}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  )
{
  if (self->diagnostics) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->diagnostics); 
  }
  if (self->log) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->log);
  }
}

Arcadia_Languages_Diagnostics*
Arcadia_Languages_Diagnostics_create
  (
    Arcadia_Thread* thread,
    Arcadia_Log* log
  )
{ 
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (log) Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)log); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Languages_Diagnostics);
}

Arcadia_BooleanValue
Arcadia_Languages_Diagnostics_hasErrors
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  )
{ 
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->diagnostics); i < n; ++i) {
    Arcadia_Languages_Diagnostic* diagnostic = (Arcadia_Languages_Diagnostic*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, self->diagnostics, i, _Arcadia_Languages_Diagnostic_getType(thread));
    if (Arcadia_Languages_DiagnosticType_Error == Arcadia_Languages_Diagnostic_getType(thread, diagnostic)) {
      return Arcadia_BooleanValue_True;
    }
  }
  return Arcadia_BooleanValue_False;
}

void
Arcadia_Languages_Diagnostics_add
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self,
    Arcadia_Languages_Diagnostic* diagnostic
  )
{
  Arcadia_List_insertBackObjectReferenceValue(thread, self->diagnostics, diagnostic);    
}

void
Arcadia_Languages_Diagnostics_emit
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostics* self
  )
{ 
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->diagnostics); i < n; ++i) {
    Arcadia_Languages_Diagnostic* diagnostic = (Arcadia_Languages_Diagnostic*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, self->diagnostics, i, _Arcadia_Languages_Diagnostic_getType(thread));
    switch (diagnostic->type) {
      case Arcadia_Languages_DiagnosticType_Error: {
        Arcadia_Log_error(thread, self->log, Arcadia_Languages_Diagnostic_getMessage(thread, diagnostic));
      } break;
      case Arcadia_Languages_DiagnosticType_Warning: {
        Arcadia_Log_warning(thread, self->log, Arcadia_Languages_Diagnostic_getMessage(thread, diagnostic));
      } break;
      case Arcadia_Languages_DiagnosticType_Information: {
        Arcadia_Log_information(thread, self->log, Arcadia_Languages_Diagnostic_getMessage(thread, diagnostic));
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
  }
}
