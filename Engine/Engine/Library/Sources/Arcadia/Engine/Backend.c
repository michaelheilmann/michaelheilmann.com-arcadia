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

#include "Arcadia/Engine/Backend.h"

static void
Arcadia_Engine_Backend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Backend* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Engine_Backend_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Backend", Arcadia_Engine_Backend,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Engine_Backend_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Backend* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Backend_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->close = NULL;
  self->createSystem = NULL;
  self->getName = NULL;
  self->open = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

void
Arcadia_Engine_Backend_open
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Backend* self
  )
{ self->open(thread, self); }

void
Arcadia_Engine_Backend_close
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Backend* self
  )
{ self->close(thread, self); }

Arcadia_String*
Arcadia_Engine_Backend_getName
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Backend* self
  )
{ return self->getName(thread, self); }

Arcadia_Engine_System*
Arcadia_Engine_System_createSystem
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Backend* self
  )
{ return self->createSystem(thread, self); }
