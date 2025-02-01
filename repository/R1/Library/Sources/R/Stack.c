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

#include "R/Stack.h"

#include "R.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

static void
R_Stack_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_Stack* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
R_Stack_ensureInitialized
  (
    Arcadia_Process* process
  );

static void
R_Stack_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Stack_destruct
  (
    Arcadia_Process* process,
    R_Stack* self
  );

static void
R_Stack_visit
  (
    Arcadia_Process* process,
    R_Stack* self
  );

static void
R_Stack_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Stack_constructImpl,
  .destruct = &R_Stack_destruct,
  .visit = &R_Stack_visit,
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

Rex_defineObjectType(u8"Arcadia.Library.Stack", R_Stack, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_Stack_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_Stack* self,
    Arcadia_SizeValue requiredFreeCapacity
  )
{
  Arcadia_SizeValue newAvailableFreeCapacity = self->capacity - self->size;
  Arcadia_SizeValue oldCapacity = self->capacity;
  Arcadia_SizeValue newCapacity = oldCapacity;
  while (requiredFreeCapacity > newAvailableFreeCapacity) {
    oldCapacity = self->capacity;
    newCapacity = oldCapacity;
    if (oldCapacity > g_maximumCapacity / 2) {
      // If oldCapacity > maximumCapacity / 2 holds then oldCapacity * 2 > maximumCapacity holds.
      // Consequently, we cannot double the capacity. Try to saturate the capacity.
      if (oldCapacity == g_maximumCapacity) {
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
      } else {
        newCapacity = g_maximumCapacity;
      }
    } else {
      newCapacity = oldCapacity * 2;
    }
    newAvailableFreeCapacity = newCapacity - self->size;
  }
  Arcadia_Process_reallocateUnmanaged(process, &self->elements, sizeof(Arcadia_Value) * newCapacity);
  self->capacity = newCapacity;
}

static void
R_Stack_ensureInitialized
  (
    Arcadia_Process* process
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(Arcadia_Value);
    if (g_maximumCapacity > Arcadia_Integer32Value_Maximum) {
      g_maximumCapacity = Arcadia_Integer32Value_Maximum;
    }
    if (g_minimumCapacity > g_maximumCapacity) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    g_initialized = Arcadia_BooleanValue_True;
  }
}

static void
R_Stack_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Stack* _self = Arcadia_Value_getObjectReferenceValue(self);
  R_Stack_ensureInitialized(process);
  Arcadia_TypeValue _type = _R_Stack_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->elements = NULL;
  _self->capacity = 0;
  _self->size = 0;
  _self->capacity = g_minimumCapacity;
  Arcadia_Process_allocateUnmanaged(process, &_self->elements, sizeof(Arcadia_Value) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    Arcadia_Value_setVoidValue(_self->elements + i, Arcadia_VoidValue_Void);
  }
  Arcadia_Object_setType(process, _self, _type);
}

static void
R_Stack_destruct
  (
    Arcadia_Process* process,
    R_Stack* self
  )
{
  if (self->elements) {
    Arcadia_Process_deallocateUnmanaged(process, self->elements);
    self->elements = NULL;
  }
}

static void
R_Stack_visit
  (
    Arcadia_Process* process,
    R_Stack* self
  )
{
  if (self->elements) {
    for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
      Arcadia_Value_visit(process, self->elements + i);
    }
  }
}

R_Stack*
R_Stack_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Stack* self = R_allocateObject(process, _R_Stack_getType(process), 0, &argumentValues[0]);
  return self;
}

void
R_Stack_clear
  (
    R_Stack* self
  )
{ self->size = 0; }

Arcadia_SizeValue
R_Stack_getSize
  (
    R_Stack* self
  )
{ return self->size; }

void
R_Stack_push
  (
    Arcadia_Process* process,
    R_Stack* self,
    Arcadia_Value value
  )
{
  if (self->capacity == self->size) {
    R_Stack_ensureFreeCapacity(process, self, Arcadia_SizeValue_Literal(1));
  }
  self->elements[self->size++] = value;
}

void
R_Stack_pop
  ( 
    Arcadia_Process* process,
    R_Stack* self
  )
{
  if (0 == self->size) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  --self->size;
}

Arcadia_Value
R_Stack_peek
  (
    Arcadia_Process* process,
    R_Stack* self
  )
{
  if (0 == self->size) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  return self->elements[self->size - 1];
}

#define Define(Type, Suffix, Variable) \
  void \
  R_Stack_push##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      R_Stack* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    R_Stack_push(process, self, value); \
  } \
\
  Arcadia_BooleanValue \
  R_Stack_is##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      R_Stack* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Process_jump(process); \
    } \
    return Arcadia_Value_is##Suffix##Value(self->elements + self->size - index - 1); \
  } \
\
  Type##Value \
  R_Stack_get##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      R_Stack* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Process_jump(process); \
    } \
    Arcadia_Value* element = self->elements + self->size - index - 1; \
    if (!Arcadia_Value_is##Suffix##Value(element)) { \
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Process_jump(process); \
    } \
    return Arcadia_Value_get##Suffix##Value(element); \
  }

Define(Arcadia_Boolean, Boolean, boolean)
Define(Arcadia_ForeignProcedure, ForeignProcedure, foreignProcedure)
Define(Arcadia_Integer8, Integer8, integer8)
Define(Arcadia_Integer16, Integer16, integer16)
Define(Arcadia_Integer32, Integer32, integer32)
Define(Arcadia_Integer64, Integer64, integer64)
Define(Arcadia_Natural8, Natural8, natural8)
Define(Arcadia_Natural16, Natural16, natural16)
Define(Arcadia_Natural32, Natural32, natural32)
Define(Arcadia_Natural64, Natural64, natural64)
Define(Arcadia_ObjectReference, ObjectReference, objectReference)
Define(Arcadia_Size, Size, size)
Define(Arcadia_Void, Void, void)

#undef Define