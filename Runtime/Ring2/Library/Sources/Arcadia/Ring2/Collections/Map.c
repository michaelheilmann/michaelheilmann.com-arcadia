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
#include "Arcadia/Ring2/Collections/Map.h"

#include "Arcadia/Ring2/Include.h"

static void
Arcadia_Map_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_Map_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Map", Arcadia_Map,
                         u8"Arcadia.Collection", Arcadia_Collection,
                         &_typeOperations);

static void
Arcadia_Map_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Map_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->get = NULL;
  self->remove = NULL;
  self->set = NULL;
  self->getKeys = NULL;
  self->getValues = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

Arcadia_Value
Arcadia_Map_get
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key
  )
{ return self->get(thread, self, key); }

void
Arcadia_Map_remove
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  )
{ self->remove(thread, self, key, oldKey, oldValue); }

void
Arcadia_Map_set
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key,
    Arcadia_Value value,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  )
{ self->set(thread,self, key, value, oldKey, oldValue); }

Arcadia_List*
Arcadia_Map_getKeys
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self
  )
{ return self->getKeys(thread, self); }

Arcadia_List*
Arcadia_Map_getValues
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self
  )
{ return self->getValues(thread, self); }
