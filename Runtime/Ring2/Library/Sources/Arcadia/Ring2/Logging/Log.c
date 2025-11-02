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
#include "Arcadia/Ring2/Logging/Log.h"

#include "Arcadia/Ring2/FileSystem/Include.h"

static void
Arcadia_Log_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self
  );

static void
Arcadia_Log_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Log_constructImpl,
  .destruct = NULL,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Log_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Log", Arcadia_Log,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Log_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Log_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->error = NULL;
  self->info = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_Log_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self
  )
{ }

void
Arcadia_Log_info
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self,
    Arcadia_String* message
  )
{ self->info(thread, self, message); }

void
Arcadia_Log_error
  (
    Arcadia_Thread* thread,
    Arcadia_Log* self,
    Arcadia_String* message
  )
{ self->error(thread, self, message); }
