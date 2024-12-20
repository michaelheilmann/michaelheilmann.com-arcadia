// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-14

#include "R/Mil/StringTable.h"

#include "R/cstdlib.h"

static void
R_Mil_StringTable_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_StringTable_maybeResize_nojump
  (
    R_Mil_StringTable* self
  );

static R_SizeValue
R_Mil_StringTable_hashBytes
  (
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  );

static void
R_Mil_StringTable_visit
  (
    R_Mil_StringTable* self
  );

static void
R_Mil_StringTable_destruct
  (
    R_Mil_StringTable* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Mil_StringTable_constructImpl,
  .destruct = &R_Mil_StringTable_destruct,
  .visit = &R_Mil_StringTable_visit,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.StringTable", R_Mil_StringTable, "R.Object", R_Object, &_typeOperations);

static void
R_Mil_StringTable_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_StringTable* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_StringTable_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->buckets = NULL;
  _self->size = R_SizeValue_Literal(0);
  _self->capacity = R_SizeValue_Literal(0);
  static R_SizeValue const g_defaultCapacity = 8;
  if (!R_allocateUnmanaged_nojump((void**)&_self->buckets, sizeof(R_Mil_StringTable_Node*) * g_defaultCapacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = g_defaultCapacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  _self->capacity = g_defaultCapacity;
  R_Object_setType((R_Object*)_self, _type);
}
                              
static void
R_Mil_StringTable_maybeResize_nojump
  (
    R_Mil_StringTable* self
  )
{
  if (self->size >= self->capacity) {
    R_SizeValue maximumCapacity = R_SizeValue_Maximum / sizeof(R_Mil_StringTable_Node*);
    R_SizeValue oldCapacity = self->capacity;
    R_SizeValue newCapacity;
    if (oldCapacity > maximumCapacity / 2) {
      if (oldCapacity == maximumCapacity) {
        return; // Cannot grow. Still a success.
      }
      newCapacity = maximumCapacity;
    } else {
      newCapacity = oldCapacity * 2;
    }
    R_Mil_StringTable_Node** oldBuckets = self->buckets;
    R_Mil_StringTable_Node** newBuckets = NULL;
    if (!R_allocateUnmanaged_nojump((void**)&newBuckets, sizeof(R_Mil_StringTable_Node*) * newCapacity)) {
      R_setStatus(R_Status_Success);
      return;
    }
    for (R_SizeValue i = 0, n = newCapacity; i < n; ++i) {
      newBuckets[i] = NULL;
    }
    for (R_SizeValue oldIndex = 0, n = oldCapacity; oldIndex < n; ++oldIndex) {
      while (oldBuckets[oldIndex]) {
        R_Mil_StringTable_Node* node = oldBuckets[oldIndex];
        oldBuckets[oldIndex] = oldBuckets[oldIndex]->next;
        R_SizeValue hash = R_Object_hash((R_ObjectReferenceValue)node->string);
        R_SizeValue newIndex = hash % newCapacity;
        node->next = newBuckets[newIndex];
        newBuckets[newIndex] = node;
      }
    }
    R_deallocateUnmanaged_nojump(oldBuckets);
    self->buckets = newBuckets;
    self->capacity = newCapacity;
  }
}

static R_SizeValue
R_Mil_StringTable_hashBytes
  (
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  )
{
  R_SizeValue hash = numberOfBytes;
  for (R_SizeValue i = 0, n = numberOfBytes; i < n; ++i) {
    hash = hash * 37 + bytes[i];
  }
  return hash;
}

static void
R_Mil_StringTable_visit
  (
    R_Mil_StringTable* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    R_Mil_StringTable_Node* node = self->buckets[i];
    while (node) {
      R_Object_visit(node->string);
      node = node->next;
    }
  }
}

static void
R_Mil_StringTable_destruct
  (
    R_Mil_StringTable* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      R_Mil_StringTable_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      R_deallocateUnmanaged_nojump(node);
    }
  }
}

R_Mil_StringTable*
R_Mil_StringTable_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_Mil_StringTable* self = R_allocateObject(_R_Mil_StringTable_getType(), 0, &argumentValues[0]);
  return self;
}

R_String*
R_Mil_StringTable_getOrCreateString
  (
    R_Mil_StringTable* self,
    R_StringBuffer* stringBuffer
  )
{
  R_SizeValue hash = R_Mil_StringTable_hashBytes(R_StringBuffer_getBytes(stringBuffer), R_StringBuffer_getNumberOfBytes(stringBuffer));
  R_SizeValue index = hash % self->capacity;
  for (R_Mil_StringTable_Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (R_Object_hash((R_ObjectReferenceValue)node->string) == hash && R_String_getNumberOfBytes(node->string)) {
      if (!c_memcmp(R_String_getBytes(node->string), R_StringBuffer_getBytes(stringBuffer), R_String_getNumberOfBytes(node->string))) {
        return node->string;
      }
    }
  }
  R_Value temporary;
  R_Value_setObjectReferenceValue(&temporary, stringBuffer);
  R_String* string = R_String_create(temporary);
  R_Mil_StringTable_Node* node = NULL;
  if (!R_allocateUnmanaged_nojump(&node, sizeof(R_Mil_StringTable_Node))) {
    R_jump();
  }
  node->string = string;
  node->next = self->buckets[index];
  self->buckets[index] = node;
  self->size++;
  
  R_Mil_StringTable_maybeResize_nojump(self);

  return string;
}
