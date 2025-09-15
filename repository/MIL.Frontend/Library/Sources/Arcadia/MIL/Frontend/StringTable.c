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

#include "Arcadia/MIL/Frontend/StringTable.h"

#include "Arcadia/MIL/Frontend/Include.h"

static void
Arcadia_MIL_StringTable_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_MIL_StringTable_maybeResize_nojump
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_StringTable* self
  );

static Arcadia_SizeValue
Arcadia_MIL_StringTable_hashBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

static void
Arcadia_MIL_StringTable_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_StringTable* self
  );

static void
Arcadia_MIL_StringTable_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_StringTable* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_MIL_StringTable_constructImpl,
  .destruct = &Arcadia_MIL_StringTable_destruct,
  .visit = &Arcadia_MIL_StringTable_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.StringTable", Arcadia_MIL_StringTable,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_MIL_StringTable_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_MIL_StringTable* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_MIL_StringTable_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->buckets = NULL;
  _self->size = Arcadia_SizeValue_Literal(0);
  _self->capacity = Arcadia_SizeValue_Literal(0);
  static Arcadia_SizeValue const g_defaultCapacity = 8;
  _self->buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_MIL_StringTable_Node*) * g_defaultCapacity);
  for (Arcadia_SizeValue i = 0, n = g_defaultCapacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  _self->capacity = g_defaultCapacity;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_MIL_StringTable_maybeResize_nojump
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_StringTable* self
  )
{
  if (self->size >= self->capacity) {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_SizeValue maximumCapacity = Arcadia_SizeValue_Maximum / sizeof(Arcadia_MIL_StringTable_Node*);
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
      Arcadia_MIL_StringTable_Node** oldBuckets = self->buckets;
      Arcadia_MIL_StringTable_Node** newBuckets = NULL;
      newBuckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_MIL_StringTable_Node*) * newCapacity);
      for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
        newBuckets[i] = NULL;
      }
      for (Arcadia_SizeValue oldIndex = 0, n = oldCapacity; oldIndex < n; ++oldIndex) {
        while (oldBuckets[oldIndex]) {
          Arcadia_MIL_StringTable_Node* node = oldBuckets[oldIndex];
          oldBuckets[oldIndex] = oldBuckets[oldIndex]->next;
          Arcadia_Value v = Arcadia_Value_makeObjectReferenceValue(node->string);
          Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &v);
          Arcadia_SizeValue newIndex = hash % newCapacity;
          node->next = newBuckets[newIndex];
          newBuckets[newIndex] = node;
        }
      }
      Arcadia_Memory_deallocateUnmanaged(thread, oldBuckets);
      self->buckets = newBuckets;
      self->capacity = newCapacity;
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      // Fail silently.
    }
  }
}

static Arcadia_SizeValue
Arcadia_MIL_StringTable_hashBytes
  (
    Arcadia_Thread* thread,
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
Arcadia_MIL_StringTable_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_StringTable* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Arcadia_MIL_StringTable_Node* node = self->buckets[i];
    while (node) {
      Arcadia_Object_visit(thread, (Arcadia_Object*)node->string);
      node = node->next;
    }
  }
}

static void
Arcadia_MIL_StringTable_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_StringTable* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Arcadia_MIL_StringTable_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Memory_deallocateUnmanaged(thread, node);
    }
  }
}

Arcadia_MIL_StringTable*
Arcadia_MIL_StringTable_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_StringTable);
}

Arcadia_String*
Arcadia_MIL_StringTable_getOrCreateString
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_StringTable* self,
    Arcadia_StringBuffer* stringBuffer
  )
{
  Arcadia_SizeValue hash = Arcadia_MIL_StringTable_hashBytes(thread, Arcadia_StringBuffer_getBytes(thread, stringBuffer), Arcadia_StringBuffer_getNumberOfBytes(thread, stringBuffer));
  Arcadia_SizeValue index = hash % self->capacity;
  for (Arcadia_MIL_StringTable_Node* node = self->buckets[index]; NULL != node; node = node->next) {
    Arcadia_Value nodeValue = Arcadia_Value_makeObjectReferenceValue(node->string);
    if (Arcadia_Value_getHash(thread, &nodeValue) == hash && Arcadia_String_getNumberOfBytes(thread, node->string)) {
      if (!Arcadia_Memory_compare(thread, Arcadia_String_getBytes(thread, node->string), Arcadia_StringBuffer_getBytes(thread, stringBuffer), Arcadia_String_getNumberOfBytes(thread, node->string))) {
        return node->string;
      }
    }
  }
  Arcadia_Value temporary;
  Arcadia_Value_setObjectReferenceValue(&temporary, stringBuffer);
  Arcadia_String* string = Arcadia_String_create(thread, temporary);
  Arcadia_MIL_StringTable_Node* node = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_MIL_StringTable_Node));
  node->string = string;
  node->next = self->buckets[index];
  self->buckets[index] = node;
  self->size++;

  Arcadia_MIL_StringTable_maybeResize_nojump(thread, self);

  return string;
}
