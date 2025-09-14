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
#include "Arcadia/Ring2/Collections/Collection.h"

#include "Arcadia/Ring1/Include.h"

static void
Arcadia_Collection_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static Arcadia_BooleanValue
Arcadia_Collection_isEmptyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Collection_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Collection", Arcadia_Collection,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Collection_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Collection* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Collection_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->clear = NULL;
  _self->getSize = NULL;
  _self->isEmpty = &Arcadia_Collection_isEmptyImpl;
  _self->isImmutable = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static Arcadia_BooleanValue
Arcadia_Collection_isEmptyImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  )
{ return Arcadia_SizeValue_Literal(0) == Arcadia_Collection_getSize(thread, self); }

void
Arcadia_Collection_clear
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  )
{ self->clear(thread, self); }

Arcadia_SizeValue
Arcadia_Collection_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  )
{ return self->getSize(thread, self); }

Arcadia_BooleanValue
Arcadia_Collection_isEmpty
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  )
{ return self->isEmpty(thread, self); }

Arcadia_BooleanValue
Arcadia_Collection_isImmutable
  (
    Arcadia_Thread* thread,
    Arcadia_Collection* self
  )
{ return self->isImmutable(thread, self); }
