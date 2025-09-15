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

#include "Arcadia/Interpreter/Code/Constants.h"

#include "Arcadia/Interpreter/Include.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self
  );

static Arcadia_Natural32Value
getOrCreate
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Value const* constant
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &constructImpl,
  .destruct = &destructImpl,
  .visit = &visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"R.Interpreter.Code.Constants", R_Interpreter_Code_Constants,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Interpreter_Code_Constants* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Code_Constants_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor2(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  _self->p = Arcadia_Memory_allocateUnmanaged(thread, 0);
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self
  )
{
  if (self->p) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->p);
    self->p = NULL;
  }
}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->cp; i < n; ++i) {
    Arcadia_Value_visit(thread, self->p + i);
  }
}

R_Interpreter_Code_Constants*
R_Interpreter_Code_Constants_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(R_Interpreter_Code_Constants);
}

static Arcadia_Natural32Value
getOrCreate
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Value const* constant
  )
{
  for (Arcadia_SizeValue i = 0, n = self->cp; i < n; ++i) {
    if (Arcadia_Value_isEqualTo(thread, self->p + i, constant)) {
      return i;
    }
  }
  Arcadia_Arrays_resizeByFreeCapacity(thread, Arms_getDefaultMemoryManager(), &self->p, sizeof(Arcadia_Value), self->sz, &self->cp, 1, Arcadia_Arrays_ResizeStrategy_Type4);
  self->p[self->sz++] = *constant;
  return self->sz - 1;
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateBoolean
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_BooleanValue booleanValue
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeBooleanValue(booleanValue);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateForeignProcedure
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_ForeignProcedureValue foreignProcedureValue
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeForeignProcedureValue(foreignProcedureValue);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger16
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer16Value integer16Value
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeInteger16Value(integer16Value);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger32
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer32Value integer32Value
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeInteger32Value(integer32Value);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger64
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer64Value integer64Value
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeInteger64Value(integer64Value);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger8
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer8Value integer8Value
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeInteger8Value(integer8Value);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural16
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural16Value natural16Value
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeNatural16Value(natural16Value);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural32
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural32Value natural32Value
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeNatural32Value(natural32Value);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural64
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural64Value natural64Value
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeNatural64Value(natural64Value);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural8
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural8Value natural8Value
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeNatural8Value(natural8Value);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateSize
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_SizeValue sizeValue
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeSizeValue(sizeValue);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateString
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_String* stringValue
  )
{
  Arcadia_Value const constant = Arcadia_Value_makeObjectReferenceValue(stringValue);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateVoid
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_VoidValue voidValue
  )
{
  Arcadia_Value constant = Arcadia_Value_Initializer();
  Arcadia_Value_setVoidValue(&constant, Arcadia_VoidValue_Void);
  return getOrCreate(thread, self, &constant);
}

Arcadia_Value const*
R_Interpreter_Code_Constants_getAt
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants const* self,
    Arcadia_Natural32Value index
  )
{
  if (index >= self->sz) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->p + index;
}
