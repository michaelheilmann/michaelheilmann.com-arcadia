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
#include "Arcadia/MILC/Diagnostics/SymbolNotDefinedDiagnostic.h"

#include "Arcadia/MILC/Include.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnosticDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic* self
  );

static Arcadia_String*
getMessageImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic* self
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

Arcadia_defineObjectType(u8"Arcadia.MILC.Diagnostics.SymbolNotDefinedDiagnostic", Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic,
                         u8"Arcadia.Languages.Diagnostic", Arcadia_Languages_Diagnostic,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic);
  if (3 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value value = Arcadia_ValueStack_getValue(thread, 3);
    Arcadia_ValueStack_pushValue(thread,  &value);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->name = (Arcadia_String*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_String_getType(thread));
  self->file = (Arcadia_FilePath*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_FilePath_getType(thread));
  self->file = Arcadia_FilePath_clone(thread, self->file);
  Arcadia_LeaveConstructor(Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic);
}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnosticDispatch* self
  )
{
  ((Arcadia_Languages_DiagnosticDispatch*)self)->getMessage = (Arcadia_String* (*)(Arcadia_Thread*, Arcadia_Languages_Diagnostic*)) & getMessageImpl;
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->file) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->file);
  }
}

static Arcadia_String*
getMessageImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic* self
  )
{
  Arcadia_StringBuilder* stringBuffer = Arcadia_StringBuilder_create(thread);
  Arcadia_StringBuilder_insertBackString(thread, stringBuffer, Arcadia_FilePath_toNative(thread, self->file, Arcadia_BooleanValue_False));
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuffer, u8": semantical error: symbol `");
  Arcadia_StringBuilder_insertBackString(thread, stringBuffer, self->name);
  Arcadia_StringBuilder_insertBackCxxString(thread, stringBuffer, u8"` not defined\n");
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuffer));
}

Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic*
Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticType type,
    Arcadia_String* name,
    Arcadia_FilePath* file
  )
{ 
  _Arcadia_BeginCreate(Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic);
  Arcadia_ValueStack_pushEnumerationValue(thread, Arcadia_EnumerationValue_make(_Arcadia_Languages_DiagnosticType_getType(thread), type));
  Arcadia_ValueStack_pushObjectReferenceValue(thread, name);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, file);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  _Arcadia_EndCreate(Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic);
}
