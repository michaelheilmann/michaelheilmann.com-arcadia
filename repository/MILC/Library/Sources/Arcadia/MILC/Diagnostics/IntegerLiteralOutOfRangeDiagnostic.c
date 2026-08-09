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
#include "Arcadia/MILC/Diagnostics/IntegerLiteralOutOfRangeDiagnostic.h"

#include "Arcadia/MILC/Include.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnosticDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic* self
  );

static Arcadia_String*
getMessageImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.Diagnostics.IntegerLiteralOutOfRangeDiagnostic", Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic,
                         u8"Arcadia.Languages.Diagnostic", Arcadia_Languages_Diagnostic,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic);
  if (3 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value value = Arcadia_ValueStack_getValue(thread, 3);
    Arcadia_ValueStack_pushValue(thread, &value);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->symbol = (Arcadia_MILC_EnumerationConstantSymbol*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_MILC_EnumerationConstantSymbol_getType(thread));
  self->value = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic);
}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnosticDispatch* self
  )
{
  ((Arcadia_Languages_DiagnosticDispatch*)self)->getMessage = (Arcadia_String* (*)(Arcadia_Thread*, Arcadia_Languages_Diagnostic*)) & getMessageImpl;
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic* self
  )
{
  if (self->symbol) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->symbol);
  }
  if (self->value) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->value);
  }
}

static Arcadia_String*
getMessageImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic* self
  )
{
  Arcadia_StringBuilder* stringBuilder = Arcadia_StringBuilder_create(thread);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, u8"error: value `");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, self->value);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, u8"` of initializer of enumeration constant `");
  Arcadia_StringBuilder_insertBackString(thread, stringBuilder, ((Arcadia_MILC_Symbol*)self->symbol)->name);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuilder, u8"` is out of range\n");
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuilder));
}

Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic*
Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticType type,
    Arcadia_MILC_EnumerationConstantSymbol* symbol,
    Arcadia_String* value
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic);
  Arcadia_ValueStack_pushEnumerationValue(thread, Arcadia_EnumerationValue_make(_Arcadia_Languages_DiagnosticType_getType(thread), type));
  if (symbol) Arcadia_ValueStack_pushObjectReferenceValue(thread, symbol); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (value) Arcadia_ValueStack_pushObjectReferenceValue(thread, value); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  _Arcadia_EndCreate(Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic);
}
