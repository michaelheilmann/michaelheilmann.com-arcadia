// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Collections/Stack.h"

static void
Arcadia_Stack_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  );

static void
Arcadia_Stack_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_StackDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Stack_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Stack", Arcadia_Stack,
                         u8"Arcadia.Collection", Arcadia_Collection,
                         &_typeOperations);

static void
Arcadia_Stack_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Stack_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_Stack_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_StackDispatch* self
  )
{ }

void
Arcadia_Stack_push
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self,
    Arcadia_Value value
  )
{ Arcadia_VirtualCall(Arcadia_Stack, push, self, value); }

void
Arcadia_Stack_pop
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{ Arcadia_VirtualCall(Arcadia_Stack, pop, self); }

Arcadia_Value
Arcadia_Stack_peek
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Stack, peek, self); }

Arcadia_Value
Arcadia_Stack_peekAt
  (
    Arcadia_Thread* thread,
    Arcadia_Stack* self,
    Arcadia_SizeValue index
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_Stack, peekAt, self, index); }

#define Define(Type, Suffix, Variable) \
  void \
  Arcadia_Stack_push##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_Stack* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    Arcadia_Stack_push(thread, self, value); \
  } \
\
  Arcadia_BooleanValue \
  Arcadia_Stack_is##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_Stack* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    Arcadia_Value v = Arcadia_Stack_peekAt(thread, self, index); \
    return Arcadia_Value_is##Suffix##Value(&v); \
  } \
\
  Type##Value \
  Arcadia_Stack_get##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_Stack* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    Arcadia_Value v = Arcadia_Stack_peekAt(thread, self, index); \
    if (!Arcadia_Value_is##Suffix##Value(&v)) { \
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Thread_jump(thread); \
    } \
    return Arcadia_Value_get##Suffix##Value(&v); \
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
