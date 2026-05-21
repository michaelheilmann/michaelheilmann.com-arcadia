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

#include "Arcadia/Languages/Diagnostic.h"

#include "Arcadia/Languages/Include.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
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

Arcadia_defineObjectType(u8"Arcadia.Languages.Diagnostic", Arcadia_Languages_Diagnostic,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Languages_Diagnostic);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_EnumerationValue enumerationValue = Arcadia_ValueStack_getEnumerationValue(thread, 1);
  if (enumerationValue.type != _Arcadia_Languages_DiagnosticType_getType(thread)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->type = (Arcadia_Languages_DiagnosticType)enumerationValue.value;
  Arcadia_LeaveConstructor(Arcadia_Languages_Diagnostic);
}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticDispatch* self
  )
{/*Intentionally empty.*/}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  )
{/*Intentionally empty.*/}

Arcadia_Languages_Diagnostic*
Arcadia_Languages_Diagnostic_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticType type,
    Arcadia_String* string
  )
{ 
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushEnumerationValue(thread, Arcadia_EnumerationValue_make(_Arcadia_Languages_DiagnosticType_getType(thread), type));
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Languages_Diagnostic);
}

Arcadia_Languages_DiagnosticType
Arcadia_Languages_Diagnostic_getType
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  )
{ return self->type; }

Arcadia_String*
Arcadia_Languages_Diagnostic_getMessage
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Diagnostic* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Languages_Diagnostic, getMessage, self); }
