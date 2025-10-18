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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Collections/ImmutableList.h"

#include "Arcadia/Ring2/Include.h"

static void
Arcadia_ImmutableList_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  );

static void
Arcadia_ImmutableList_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  );

static void
Arcadia_ImmutableList_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  );

static void
Arcadia_ImmutableList_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  );

static Arcadia_Value
Arcadia_ImmutableList_getAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_SizeValue index
  );

static Arcadia_SizeValue
Arcadia_ImmutableList_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  );

static Arcadia_BooleanValue
Arcadia_ImmutableList_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  );

static void
Arcadia_ImmutableList_insertAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  );

static void
Arcadia_ImmutableList_insertBackImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_Value value
  );

static void
Arcadia_ImmutableList_insertFrontImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_Value value
  );

static void
Arcadia_ImmutableList_removeAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue count
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_ImmutableList_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*) & Arcadia_ImmutableList_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_ImmutableList_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ImmutableList", Arcadia_ImmutableList,
                         u8"Arcadia.List", Arcadia_List,
                         &_typeOperations);

static void
Arcadia_ImmutableList_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ImmutableList_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->size = 0;
  self->elements = NULL;
  Arcadia_List* other = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_List_getType(thread));
  self->size = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)other);
  self->elements = Arcadia_Memory_allocateUnmanaged(thread, sizeof(Arcadia_Value) * self->size);
  for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
    self->elements[i] = Arcadia_List_getAt(thread, other, i);
  }
  ((Arcadia_Collection*)self)->clear = (void (*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_ImmutableList_clearImpl;
  ((Arcadia_Collection*)self)->getSize = (Arcadia_SizeValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_ImmutableList_getSizeImpl;
  ((Arcadia_Collection*)self)->isImmutable = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_ImmutableList_isImmutableImpl;
  ((Arcadia_List*)self)->getAt = (Arcadia_Value(*)(Arcadia_Thread*, Arcadia_List*, Arcadia_SizeValue)) & Arcadia_ImmutableList_getAtImpl;
  ((Arcadia_List*)self)->insertAt = (void (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_SizeValue, Arcadia_Value)) & Arcadia_ImmutableList_insertAtImpl;
  ((Arcadia_List*)self)->insertBack = (void (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_Value)) & Arcadia_ImmutableList_insertBackImpl;
  ((Arcadia_List*)self)->insertFront = (void (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_Value)) & Arcadia_ImmutableList_insertFrontImpl;
  ((Arcadia_List*)self)->removeAt = (void (*)(Arcadia_Thread*, Arcadia_List*, Arcadia_SizeValue, Arcadia_SizeValue)) & Arcadia_ImmutableList_removeAtImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2);
}

static void
Arcadia_ImmutableList_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  )
{
  if (self->elements) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->elements);
    self->elements = NULL;
  }
}

static void
Arcadia_ImmutableList_visit
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
    Arcadia_Value_visit(thread, self->elements + i);
  }
}

static void
Arcadia_ImmutableList_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  )
{
  Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
  Arcadia_Thread_jump(thread);
}

static Arcadia_Value
Arcadia_ImmutableList_getAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_SizeValue index
  )
{
  if (index >= self->size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return *(self->elements + index); 
}

static Arcadia_SizeValue
Arcadia_ImmutableList_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  )
{ return self->size; }

static Arcadia_BooleanValue
Arcadia_ImmutableList_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self
  )
{ return Arcadia_BooleanValue_True; }

static void
Arcadia_ImmutableList_insertAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  )
{
  Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
  Arcadia_Thread_jump(thread);
}

static void
Arcadia_ImmutableList_insertBackImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_Value value
  )
{
  Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
  Arcadia_Thread_jump(thread);
}

static void
Arcadia_ImmutableList_insertFrontImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_Value value
  )
{
  Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
  Arcadia_Thread_jump(thread);
}

static void
Arcadia_ImmutableList_removeAtImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableList* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue count
  )
{
  Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
  Arcadia_Thread_jump(thread);
}

Arcadia_ImmutableList*
Arcadia_ImmutableList_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value argument
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushValue(thread, &argument);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_ImmutableList);
}
