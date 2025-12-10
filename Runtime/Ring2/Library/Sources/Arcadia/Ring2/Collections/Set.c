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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Collections/Set.h"

static void
Arcadia_Set_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  );

static void
Arcadia_Set_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_SetDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Set_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Set", Arcadia_Set,
                         u8"Arcadia.Collection", Arcadia_Collection,
                         &_typeOperations);

static void
Arcadia_Set_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Set_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_Set_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_SetDispatch* self
  )
{ }

void
Arcadia_Set_add
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value,
    Arcadia_Value* oldValue
  )
{ Arcadia_VirtualCall(Arcadia_Set, add, self, value, oldValue); }

Arcadia_BooleanValue
Arcadia_Set_contains
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Set, contains, self, value); }

Arcadia_Value
Arcadia_Set_get
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Set, get, self, value); }

void
Arcadia_Set_remove
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_Value value,
    Arcadia_Value* oldValue
  )
{ Arcadia_VirtualCall(Arcadia_Set, remove, self, value, oldValue); }

void
Arcadia_Set_getAll
  (
    Arcadia_Thread* thread,
    Arcadia_Set* self,
    Arcadia_List* target
  )
{ Arcadia_VirtualCall(Arcadia_Set, getAll, self, target); }
