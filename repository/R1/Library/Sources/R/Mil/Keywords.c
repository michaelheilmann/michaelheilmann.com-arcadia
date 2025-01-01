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
  R_String* string;
  Arcadia_Natural32Value type;
};

struct R_Mil_Keywords {
  R_Object _parent;
  Keyword** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

static void
R_Mil_Keywords_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
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
      R_deallocateUnmanaged_nojump(process, node);
    }
  }
  R_deallocateUnmanaged_nojump(process, self->buckets);
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
      R_Object_visit(node->string);
      node = node->next;
    }
  }
}

static const R_ObjectType_Operations _objectTypeOperations = {
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

Rex_defineObjectType(u8"R.Mil.Keywords", R_Mil_Keywords, u8"R.Object", R_Object, &_typeOperations);

static void
R_Mil_Keywords_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Mil_Keywords* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_Keywords_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->size = 0;
  _self->capacity = 8;
  if (!R_allocateUnmanaged_nojump(process, (void**)&_self->buckets, sizeof(Keyword*) * _self->capacity)) {
    Arcadia_Process_jump(process);
  }
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  R_Object_setType((R_Object*)_self, _type);
}

R_Mil_Keywords*
R_Mil_Keywords_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
  R_Mil_Keywords* self = R_allocateObject(process, _R_Mil_Keywords_getType(process), 0, &argumentValues[0]);
  return self;
}

void
R_Mil_Keywords_add
  (
    Arcadia_Process* process,
    R_Mil_Keywords* self,
    R_String* string,
    Arcadia_Natural32Value type
  )
{
  Arcadia_SizeValue hash = R_Object_hash(process, (R_ObjectReferenceValue)string);
  Arcadia_SizeValue index = hash % self->capacity;
  for (Keyword* keyword = self->buckets[index]; NULL != keyword; keyword = keyword->next) {
    R_Value t;
    R_Value_setObjectReferenceValue(&t, (R_ObjectReferenceValue)string);
    if (R_Object_equalTo(process, (R_Object*)keyword->string, &t)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_Exists);
      Arcadia_Process_jump(process);
    }
  }
  Keyword* keyword = NULL;
  if (!R_allocateUnmanaged_nojump(process, &keyword, sizeof(Keyword))) {
    Arcadia_Process_jump(process);
  }
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
    R_String* string,
    Arcadia_Natural32Value* tokenType
  )
{
  R_Value stringValue;
  R_Value_setObjectReferenceValue(&stringValue, string);
  Arcadia_SizeValue hash = R_Object_hash(process, (R_ObjectReferenceValue)string);
  Arcadia_SizeValue index = hash % self->capacity;
  for (Keyword* keyword = self->buckets[index]; NULL != keyword; keyword = keyword->next) {
    if (R_Object_equalTo(process, (R_ObjectReferenceValue)keyword->string, &stringValue)) {
      *tokenType = keyword->type;
      return Arcadia_BooleanValue_True;
    }
  }
  return Arcadia_BooleanValue_False;
}
