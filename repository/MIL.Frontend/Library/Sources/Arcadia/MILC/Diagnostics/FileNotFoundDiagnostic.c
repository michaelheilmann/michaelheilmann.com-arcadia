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
#include "Arcadia/MILC/Diagnostics/FileNotFoundDiagnostic.h"

#include "Arcadia/MILC/Include.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnosticDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self
  );

static Arcadia_String*
wordTypeToString
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self,
    Arcadia_MILC_WordType wordType
  );

static Arcadia_String*
getMessageImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self
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

Arcadia_defineObjectType(u8"Arcadia.MILC.Diagnostics.FileNotFoundDiagnostic", Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic,
                         u8"Arcadia.Languages.Diagnostic", Arcadia_Languages_Diagnostic,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic);
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
  Arcadia_EnumerationValue temporary = Arcadia_ValueStack_getEnumerationValue(thread, 2);
  if (temporary.type != _Arcadia_MILC_FileType_getType(thread)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->fileType = (Arcadia_MILC_FileType)temporary.value;
  self->path = Arcadia_FilePath_clone(thread, (Arcadia_FilePath*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_FilePath_getType(thread)));
  Arcadia_LeaveConstructor(Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic);
}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnosticDispatch* self
  )
{
  ((Arcadia_Languages_DiagnosticDispatch*)self)->getMessage = (Arcadia_String* (*)(Arcadia_Thread*, Arcadia_Languages_Diagnostic*)) & getMessageImpl;
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self
  )
{
  if (self->path) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->path);
  }
}

static Arcadia_String*
getMessageImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic* self
  )
{
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"error: ");
  switch (self->fileType) {
    case Arcadia_MILC_FileType_CompilationUnit: {
      Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"compilation unit file");
    } break;
    case Arcadia_MILC_FileType_ConfigurationFile: {
      Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"configuration file");
    } break;
    case Arcadia_MILC_FileType_ModuleDirectory: {
      Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"module directory");
    } break;
    default: {
      Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"file ");
    } break;
  }
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8" `");
  Arcadia_StringBuffer_insertBackString(thread, stringBuffer, Arcadia_FilePath_toNative(thread, self->path, Arcadia_BooleanValue_False));
  Arcadia_StringBuffer_insertBackCxxString(thread, stringBuffer, u8"` not found\n");
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuffer));
}

Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic*
Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic_create
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_DiagnosticType diagnosticType,
    Arcadia_MILC_FileType fileType,
    Arcadia_FilePath* path
  )
{ 
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushEnumerationValue(thread, Arcadia_EnumerationValue_make(_Arcadia_Languages_DiagnosticType_getType(thread), diagnosticType));
  Arcadia_ValueStack_pushEnumerationValue(thread, Arcadia_EnumerationValue_make(_Arcadia_MILC_FileType_getType(thread), fileType));
  if (path) Arcadia_ValueStack_pushObjectReferenceValue(thread, path); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 3);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_Diagnostics_FileNotFoundDiagnostic);
}
