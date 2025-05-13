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

#include "Arcadia/Mil/Frontend/Keywords.h"

typedef struct Keyword Keyword;

struct Keyword {
  Keyword* next;
  Arcadia_String* string;
  Arcadia_Natural32Value type;
};

struct Arcadia_Mil_Keywords {
  Arcadia_Object _parent;
  Keyword** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

static void
Arcadia_Mil_Keywords_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_Keywords_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Keywords* self
  );

static void
Arcadia_Mil_Keywords_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Keywords* self
  );

static void
Arcadia_Mil_Keywords_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Keywords* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Keyword* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), node);
    }
  }
  Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), self->buckets);
  self->buckets = NULL;
}

static void
Arcadia_Mil_Keywords_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Keywords* self
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

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Mil_Keywords_constructImpl,
  .destruct = &Arcadia_Mil_Keywords_destruct,
  .visit = &Arcadia_Mil_Keywords_visit,
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

Arcadia_defineObjectType(u8"Arcadia.Mil.Keywords", Arcadia_Mil_Keywords, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Mil_Keywords_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_Keywords* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_Keywords_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->size = 0;
  _self->capacity = 8;
  Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), (void**)&_self->buckets, sizeof(Keyword*) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

Arcadia_Mil_Keywords*
Arcadia_Mil_Keywords_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  Arcadia_Mil_Keywords* self = Arcadia_allocateObject(thread, _Arcadia_Mil_Keywords_getType(thread), 0, &argumentValues[0]);
  return self;
}

void
Arcadia_Mil_Keywords_add
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Keywords* self,
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
  Keyword* keyword = NULL;
  Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &keyword, sizeof(Keyword));
  keyword->string = string;
  keyword->type = type;
  keyword->next = self->buckets[index];
  self->buckets[index] = keyword;
  self->size++;
}

Arcadia_BooleanValue
Arcadia_Mil_Keywords_scan
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Keywords* self,
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
