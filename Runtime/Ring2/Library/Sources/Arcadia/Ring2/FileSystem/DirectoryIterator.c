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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/FileSystem/DirectoryIterator.h"

static void
Arcadia_DirectoryIterator_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIterator* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_DirectoryIterator_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.DirectoryIterator", Arcadia_DirectoryIterator,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_DirectoryIterator_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIterator* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_DirectoryIterator_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->getValue = NULL;
  self->hasValue = NULL;
  self->nextValue = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

Arcadia_BooleanValue
Arcadia_DirectoryIterator_hasValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIterator* self
  )
{ return self->hasValue(thread, self); }

Arcadia_FilePath*
Arcadia_DirectoryIterator_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIterator* self
  )
{ return self->getValue(thread, self); }

void
Arcadia_DirectoryIterator_nextValue
  (
    Arcadia_Thread* thread,
    Arcadia_DirectoryIterator* self
  )
{ self->nextValue(thread, self); }
