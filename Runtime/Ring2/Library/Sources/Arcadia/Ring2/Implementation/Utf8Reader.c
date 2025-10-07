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
#include "Arcadia/Ring2/Implementation/Utf8Reader.h"

/// @code
/// constructor()
/// @endcode
static void
Arcadia_Utf8Reader_constructorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_Utf8Reader_constructorImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Utf8Reader", Arcadia_Utf8Reader,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Utf8Reader_constructorImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Utf8Reader_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->getCodePoint = NULL;
  self->hasCodePoint = NULL;
  self->next = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

void
Arcadia_Utf8Reader_next
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  )
{
  self->next(thread, self);
}

Arcadia_Natural32Value
Arcadia_Utf8Reader_getCodePoint
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  )
{
  return self->getCodePoint(thread, self);
}

Arcadia_BooleanValue
Arcadia_Utf8Reader_hasCodePoint
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  )
{
  return self->hasCodePoint(thread, self);
}

Arcadia_SizeValue
Arcadia_Utf8Reader_getByteIndex
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Reader* self
  )
{
  return self->getByteIndex(thread, self);
}
