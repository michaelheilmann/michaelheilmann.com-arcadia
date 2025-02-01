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

// Last modified: 2024-09-22

#include "R/Mil/Keywords.h"

typedef struct Keyword Keyword;

struct Keyword {
  Keyword* next;
  Arcadia_String* string;
  Arcadia_Natural32Value type;
};

struct R_Mil_Keywords {
  Arcadia_Object _parent;
  Keyword** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

static void
R_Mil_Keywords_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Mil_Keywords_destruct
  (
    Arcadia_Process* process,
    R_Mil_Keywords* self
  );

static void
R_Mil_Keywords_visit
  (
    Arcadia_Process* process,
    R_Mil_Keywords* self
  );

static void
R_Mil_Keywords_destruct
  (
    Arcadia_Process* process,
    R_Mil_Keywords* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Keyword* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Process_deallocateUnmanaged(process, node);
    }
  }
  Arcadia_Process_deallocateUnmanaged(process, self->buckets);
  self->buckets = NULL;
}

static void
R_Mil_Keywords_visit
  (
    Arcadia_Process* process,
    R_Mil_Keywords* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Keyword* node = self->buckets[i];
    while (node) {
      Arcadia_Object_visit(process, node->string);
      node = node->next;
    }
  }
}

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Mil_Keywords_constructImpl,
  .destruct = &R_Mil_Keywords_destruct,
  .visit = &R_Mil_Keywords_visit,
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

Rex_defineObjectType(u8"R.Mil.Keywords", R_Mil_Keywords, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_Mil_Keywords_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Mil_Keywords* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_Keywords_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->size = 0;
  _self->capacity = 8;
  Arcadia_Process_allocateUnmanaged(process, (void**)&_self->buckets, sizeof(Keyword*) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  Arcadia_Object_setType(process, _self, _type);
}

R_Mil_Keywords*
R_Mil_Keywords_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
  R_Mil_Keywords* self = R_allocateObject(process, _R_Mil_Keywords_getType(process), 0, &argumentValues[0]);
  return self;
}

void
R_Mil_Keywords_add
  (
    Arcadia_Process* process,
    R_Mil_Keywords* self,
    Arcadia_String* string,
    Arcadia_Natural32Value type
  )
{
  Arcadia_Value stringValue =  { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = string };
  Arcadia_SizeValue hash = Arcadia_Value_getHash(process, &stringValue);
  Arcadia_SizeValue index = hash % self->capacity;
  for (Keyword* keyword = self->buckets[index]; NULL != keyword; keyword = keyword->next) {
    Arcadia_Value v[] = { { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = keyword->string },
                          stringValue };
    if (Arcadia_Value_isEqualTo(process, &v[0], &v[1])) {
      Arcadia_Process_setStatus(process, Arcadia_Status_Exists);
      Arcadia_Process_jump(process);
    }
  }
  Keyword* keyword = NULL;
  Arcadia_Process_allocateUnmanaged(process, &keyword, sizeof(Keyword));
  keyword->string = string;
  keyword->type = type;
  keyword->next = self->buckets[index];
  self->buckets[index] = keyword;
  self->size++;
}

Arcadia_BooleanValue
R_Mil_Keywords_scan
  (
    Arcadia_Process* process,
    R_Mil_Keywords* self,
    Arcadia_String* string,
    Arcadia_Natural32Value* tokenType
  )
{
  Arcadia_Value stringValue = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = string };
  Arcadia_SizeValue hash = Arcadia_Value_getHash(process, &stringValue);
  Arcadia_SizeValue index = hash % self->capacity;
  for (Keyword* keyword = self->buckets[index]; NULL != keyword; keyword = keyword->next) {
    Arcadia_Value v[2] = { { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = keyword->string }, 
                           stringValue };
    if (Arcadia_Value_isEqualTo(process, &v[0], &v[1])) {
      *tokenType = keyword->type;
      return Arcadia_BooleanValue_True;
    }
  }
  return Arcadia_BooleanValue_False;
}
