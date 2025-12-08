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

#if !defined(ARCADIA_RING2_COLLECTIONS_MAP_H_INCLUDED)
#define ARCADIA_RING2_COLLECTIONS_MAP_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Collections/Collection.h"
typedef struct Arcadia_List Arcadia_List;

Arcadia_declareObjectType(u8"Arcadia.Map", Arcadia_Map,
                          u8"Arcadia.Collection");

struct Arcadia_Map {
  Arcadia_Collection parent;

  Arcadia_Value(*get)(Arcadia_Thread* thread, Arcadia_Map* self, Arcadia_Value key);
  void (*set)(Arcadia_Thread* thread, Arcadia_Map* self, Arcadia_Value key, Arcadia_Value value, Arcadia_Value* oldKey, Arcadia_Value* oldValue);
  void (*remove)(Arcadia_Thread* thread, Arcadia_Map* self, Arcadia_Value key, Arcadia_Value* oldKey, Arcadia_Value* oldValue);
  Arcadia_List* (*getKeys)(Arcadia_Thread* thread, Arcadia_Map* self);
  Arcadia_List* (*getValues)(Arcadia_Thread* thread,Arcadia_Map* self);
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Map_get
Arcadia_Value
Arcadia_Map_get
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Map_set
void
Arcadia_Map_set
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key,
    Arcadia_Value value,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_Map_remove
void
Arcadia_Map_remove
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  );

Arcadia_List*
Arcadia_Map_getKeys
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self
  );

Arcadia_List*
Arcadia_Map_getValues
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self
  );

/*@extension*/
static inline Arcadia_BooleanValue
Arcadia_Map_getBooleanValueChecked
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key
  )
{
  Arcadia_Value value = Arcadia_Map_get(thread, self, key);
  if (!Arcadia_Value_isBooleanValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BooleanValue booleanValue = Arcadia_Value_getBooleanValue(&value);
  return booleanValue;
}

/*@extension*/
static inline Arcadia_Natural64Value
Arcadia_Map_getNatural64ValueChecked
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key
  )
{
  Arcadia_Value value = Arcadia_Map_get(thread, self, key);
  if (!Arcadia_Value_isNatural64Value(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural64Value natural64Value = Arcadia_Value_getNatural64Value(&value);
  return natural64Value;
}

/*@extension*/
static inline Arcadia_Object*
Arcadia_Map_getObjectReferenceValueChecked
  (
    Arcadia_Thread* thread,
    Arcadia_Map* self,
    Arcadia_Value key,
    Arcadia_Type* type
  )
{
  Arcadia_Value value = Arcadia_Map_get(thread, self, key);
  if (!Arcadia_Value_isObjectReferenceValue(&value)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object* objectValue = Arcadia_Value_getObjectReferenceValue(&value);
  if (!Arcadia_Object_isInstanceOf(thread, objectValue, type)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return objectValue;
}

#endif // ARCADIA_RING2_COLLECTIONS_MAP_H_INCLUDED
