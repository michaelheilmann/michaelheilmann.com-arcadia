// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_LANGUAGES_PRIVATE (1)
#include "Arcadia/Languages/Scanner.h"

static void
Arcadia_Languages_Scanner_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

static void
Arcadia_Languages_Scanner_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

static void
Arcadia_Languages_Scanner_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Languages_Scanner_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Languages_Scanner_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Languages_Scanner_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Languages.Scanner", Arcadia_Languages_Scanner,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Languages_Scanner_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Languages_Scanner_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->getInput = NULL;
  self->getStringTable = NULL;
  self->getWordLength = NULL;
  self->getWordStart = NULL;
  self->getWordText = NULL;
  self->getWordType = NULL;
  self->setInput = NULL;
  self->step = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_Languages_Scanner_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Languages_Scanner_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{/*Intentionally empty.*/}

Arcadia_String*
Arcadia_Languages_Scanner_getWordText
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{ return self->getWordText(thread, self); }

Arcadia_Natural32Value
Arcadia_Languages_Scanner_getWordType
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{ return self->getWordType(thread, self); }

Arcadia_Natural32Value
Arcadia_Languages_Scanner_getWordStart
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{ return self->getWordStart(thread, self); }

Arcadia_Natural32Value
Arcadia_Languages_Scanner_getWordLength
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{ return self->getWordLength(thread, self); }

void
Arcadia_Languages_Scanner_step
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{ self->step(thread, self); }

void
Arcadia_Languages_Scanner_setInput
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self,
    Arcadia_String* input
  )
{ self->setInput(thread, self, input); }

Arcadia_String*
Arcadia_Languages_Scanner_getInput
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{ return self->getInput(thread, self); }

Arcadia_Languages_StringTable*
Arcadia_Languages_Scanner_getStringTable
  (
    Arcadia_Thread* thread,
    Arcadia_Languages_Scanner* self
  )
{ return self->getStringTable(thread, self); }
