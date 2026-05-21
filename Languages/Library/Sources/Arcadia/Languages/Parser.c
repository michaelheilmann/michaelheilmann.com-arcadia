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

#define ARCADIA_LANGUAGES_MODULE (1)
#include "Arcadia/Languages/Parser.h"

static void
Arcadia_Languages_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  );

static void
Arcadia_Languages_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_ParserDispatch* self
  );

static void
Arcadia_Languages_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  );

static void
Arcadia_Languages_Parser_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Languages_Parser_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Languages_Parser_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Languages_Parser_visit,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_Languages_Parser_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Languages.Parser", Arcadia_Languages_Parser,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Languages_Parser_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  )
{
  Arcadia_EnterConstructor(Arcadia_Languages_Parser);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_Languages_Parser);
}

static void
Arcadia_Languages_Parser_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_ParserDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Languages_Parser_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Languages_Parser_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  )
{/*Intentionally empty.*/}

Arcadia_Value
Arcadia_Languages_Parser_run
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self,
    Arcadia_String* input
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Languages_Parser, run, self, input); }

Arcadia_Languages_StringTable*
Arcadia_Languages_Parser_getStringTable
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Languages_Parser, getStringTable, self); }

Arcadia_Languages_Diagnostics*
Arcadia_Languages_Parser_getDiagnostics
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Parser* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Languages_Parser, getDiagnostics, self); }
