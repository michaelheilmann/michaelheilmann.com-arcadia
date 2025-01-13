// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Mil_StringTable_maybeResize_nojump
  (
    Arcadia_Process* process,
    R_Mil_StringTable* self
  );

static Arcadia_SizeValue
R_Mil_StringTable_hashBytes
  (
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
R_Mil_StringTable_visit
  (
    Arcadia_Process* process,
    R_Mil_StringTable* self
  );

static void
R_Mil_StringTable_destruct
  (
    Arcadia_Process* process,
    R_Mil_StringTable* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Mil_StringTable_constructImpl,
  .destruct = &R_Mil_StringTable_destruct,
  .visit = &R_Mil_StringTable_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Rex_defineObjectType(u8"R.Mil.StringTable", R_Mil_StringTable, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_Mil_StringTable_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Mil_StringTable* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_StringTable_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->buckets = NULL;
  _self->size = Arcadia_SizeValue_Literal(0);
  _self->capacity = Arcadia_SizeValue_Literal(0);
  static Arcadia_SizeValue const g_defaultCapacity = 8;
  Arcadia_Process_allocateUnmanaged(process, (void**)&_self->buckets, sizeof(R_Mil_StringTable_Node*) * g_defaultCapacity);
  for (Arcadia_SizeValue i = 0, n = g_defaultCapacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  _self->capacity = g_defaultCapacity;
  Arcadia_Object_setType(process, _self, _type);
}
                              
static void
R_Mil_StringTable_maybeResize_nojump
  (
    Arcadia_Process* process,
    R_Mil_StringTable* self
  )
{
  if (self->size >= self->capacity) {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Process_pushJumpTarget(process, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_SizeValue maximumCapacity = Arcadia_SizeValue_Maximum / sizeof(R_Mil_StringTable_Node*);
      Arcadia_SizeValue oldCapacity = self->capacity;
      Arcadia_SizeValue newCapacity;
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
      Arcadia_Process_allocateUnmanaged(process, (void**)&newBuckets, sizeof(R_Mil_StringTable_Node*) * newCapacity);
      for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
        newBuckets[i] = NULL;
      }
      for (Arcadia_SizeValue oldIndex = 0, n = oldCapacity; oldIndex < n; ++oldIndex) {
        while (oldBuckets[oldIndex]) {
          R_Mil_StringTable_Node* node = oldBuckets[oldIndex];
          oldBuckets[oldIndex] = oldBuckets[oldIndex]->next;
          Arcadia_SizeValue hash = Arcadia_Object_hash(process, (Arcadia_ObjectReferenceValue)node->string); // TODO: Strengthen the contract of Arcadia_Object_hash not to jump.
          Arcadia_SizeValue newIndex = hash % newCapacity;
          node->next = newBuckets[newIndex];
          newBuckets[newIndex] = node;
        }
      }
      Arcadia_Process_deallocateUnmanaged(process, oldBuckets);
      self->buckets = newBuckets;
      self->capacity = newCapacity;
      Arcadia_Process_popJumpTarget(process);
    } else {
      Arcadia_Process_popJumpTarget(process);
      // Fail silently.
    }
  }
}

static Arcadia_SizeValue
R_Mil_StringTable_hashBytes
  (
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  Arcadia_SizeValue hash = numberOfBytes;
  for (Arcadia_SizeValue i = 0, n = numberOfBytes; i < n; ++i) {
    hash = hash * 37 + bytes[i];
  }
  return hash;
}

static void
R_Mil_StringTable_visit
  (
    Arcadia_Process* process,
    R_Mil_StringTable* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    R_Mil_StringTable_Node* node = self->buckets[i];
    while (node) {
      Arcadia_Object_visit(process, node->string);
      node = node->next;
    }
  }
}

static void
R_Mil_StringTable_destruct
  (
    Arcadia_Process* process,
    R_Mil_StringTable* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      R_Mil_StringTable_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Process_deallocateUnmanaged(process, node);
    }
  }
}

R_Mil_StringTable*
R_Mil_StringTable_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Mil_StringTable* self = R_allocateObject(process, _R_Mil_StringTable_getType(process), 0, &argumentValues[0]);
  return self;
}

Arcadia_String*
R_Mil_StringTable_getOrCreateString
  (
    Arcadia_Process* process,
    R_Mil_StringTable* self,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_SizeValue hash = R_Mil_StringTable_hashBytes(Arcadia_StringBuffer_getBytes(stringBuffer), Arcadia_StringBuffer_getNumberOfBytes(stringBuffer));
  Arcadia_SizeValue index = hash % self->capacity;
  for (R_Mil_StringTable_Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (Arcadia_Object_hash(process, (Arcadia_ObjectReferenceValue)node->string) == hash && Arcadia_String_getNumberOfBytes(node->string)) {
      if (!c_memcmp(Arcadia_String_getBytes(node->string), Arcadia_StringBuffer_getBytes(stringBuffer), Arcadia_String_getNumberOfBytes(node->string))) {
        return node->string;
      }
    }
  }
  Arcadia_Value temporary;
  Arcadia_Value_setObjectReferenceValue(&temporary, stringBuffer);
  Arcadia_String* string = Arcadia_String_create(process, temporary);
  R_Mil_StringTable_Node* node = NULL;
  Arcadia_Process_allocateUnmanaged(process, &node, sizeof(R_Mil_StringTable_Node));
  node->string = string;
  node->next = self->buckets[index];
  self->buckets[index] = node;
  self->size++;
  
  R_Mil_StringTable_maybeResize_nojump(process, self);

  return string;
}
