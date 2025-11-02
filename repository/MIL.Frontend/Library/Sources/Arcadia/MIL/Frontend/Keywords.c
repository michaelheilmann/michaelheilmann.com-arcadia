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

#include "Arcadia/MIL/Frontend/Keywords.h"

typedef struct Keyword Keyword;

struct Keyword {
  Keyword* next;
  Arcadia_String* string;
  Arcadia_Natural32Value type;
};

struct Arcadia_MIL_Keywords {
  Arcadia_Object _parent;
  Keyword** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

static void
Arcadia_MIL_Keywords_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Keywords* self
  );

static void
Arcadia_MIL_Keywords_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Keywords* self
  );

static void
Arcadia_MIL_Keywords_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Keywords* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_Keywords_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_MIL_Keywords_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_Keywords_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Keywords", Arcadia_MIL_Keywords,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_MIL_Keywords_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Keywords* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_Keywords_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->size = 0;
  self->capacity = 8;
  self->buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Keyword*) * self->capacity);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    self->buckets[i] = NULL;
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_MIL_Keywords_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Keywords* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Keyword* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Memory_deallocateUnmanaged(thread, node);
    }
  }
  Arcadia_Memory_deallocateUnmanaged(thread, self->buckets);
  self->buckets = NULL;
}

static void
Arcadia_MIL_Keywords_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Keywords* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Keyword* node = self->buckets[i];
    while (node) {
      Arcadia_Object_visit(thread, (Arcadia_Object*)node->string);
      node = node->next;
    }
  }
}

Arcadia_MIL_Keywords*
Arcadia_MIL_Keywords_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_MIL_Keywords);
}

void
Arcadia_MIL_Keywords_add
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Keywords* self,
    Arcadia_String* string,
    Arcadia_Natural32Value type
  )
{
  Arcadia_Value stringValue = Arcadia_Value_makeObjectReferenceValue(string);
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &stringValue);
  Arcadia_SizeValue index = hash % self->capacity;
  for (Keyword* keyword = self->buckets[index]; NULL != keyword; keyword = keyword->next) {
    Arcadia_Value v[] = {
      Arcadia_Value_makeObjectReferenceValue(keyword->string),
      stringValue
    };
    if (Arcadia_Value_isEqualTo(thread, &v[0], &v[1])) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Exists);
      Arcadia_Thread_jump(thread);
    }
  }
  Keyword* keyword = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Keyword));
  keyword->string = string;
  keyword->type = type;
  keyword->next = self->buckets[index];
  self->buckets[index] = keyword;
  self->size++;
}

Arcadia_BooleanValue
Arcadia_MIL_Keywords_scan
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Keywords* self,
    Arcadia_String* string,
    Arcadia_Natural32Value* tokenType
  )
{
  Arcadia_Value stringValue = Arcadia_Value_makeObjectReferenceValue(string);
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &stringValue);
  Arcadia_SizeValue index = hash % self->capacity;
  for (Keyword* keyword = self->buckets[index]; NULL != keyword; keyword = keyword->next) {
    Arcadia_Value v[2] = {
      Arcadia_Value_makeObjectReferenceValue(keyword->string),
      stringValue
    };
    if (Arcadia_Value_isEqualTo(thread, &v[0], &v[1])) {
      *tokenType = keyword->type;
      return Arcadia_BooleanValue_True;
    }
  }
  return Arcadia_BooleanValue_False;
}
