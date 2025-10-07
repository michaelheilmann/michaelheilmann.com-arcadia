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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/WeakReference.h"

#include "Arcadia/Arms/Include.h"
#include "Arcadia/Ring1/Implementation/Thread.h"
#include "Arcadia/Ring1/Implementation/ThreadExtensions.h"
#include "Arcadia/Ring1/Implementation/Object.h"
#include "Arcadia/Ring1/Implementation/Process.h"
#include "Arcadia/Ring1/Implementation/Thread.h"

static void
Arcadia_WeakReference_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_WeakReference* self
  );

static void
Arcadia_WeakReference_visit
  (
    Arcadia_Thread* thread,
    Arcadia_WeakReference* self
  );

static void
Arcadia_WeakReference_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_WeakReference* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_WeakReference_constructImpl,
  .destruct = &Arcadia_WeakReference_destruct,
  .visit = &Arcadia_WeakReference_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.WeakReference", Arcadia_WeakReference,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
callback
  (
    Arcadia_WeakReference* argument1,
    void* argument2
  )
{
  Arcadia_Value_setVoidValue(&argument1->value, Arcadia_VoidValue_Void);
}

static void
Arcadia_WeakReference_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_WeakReference* self
  )
{
  switch (Arcadia_Value_getTag(&self->value)) {
    case Arcadia_ValueTag_Atom: {
      Arms_removeNotifyDestroy(self->value.atomValue, self, NULL, &callback);
    } break;
    case Arcadia_ValueTag_BigInteger: {
    } break;
    case Arcadia_ValueTag_Boolean:
    case Arcadia_ValueTag_ForeignProcedure: {
    } break;
    case Arcadia_ValueTag_ImmutableByteArray: {
      Arms_removeNotifyDestroy(self->value.immutableByteArrayValue, self, NULL, &callback);
    } break;
    case Arcadia_ValueTag_ImmutableUtf8String: {
      Arms_removeNotifyDestroy(self->value.immutableUtf8StringValue, self, NULL, &callback);
    } break;
    case Arcadia_ValueTag_Integer16:
    case Arcadia_ValueTag_Integer32:
    case Arcadia_ValueTag_Integer64:
    case Arcadia_ValueTag_Integer8:
    case Arcadia_ValueTag_Natural16:
    case Arcadia_ValueTag_Natural32:
    case Arcadia_ValueTag_Natural64:
    case Arcadia_ValueTag_Natural8: {
    } break;
    case Arcadia_ValueTag_ObjectReference: {
      Arcadia_Object_removeNotifyDestroyCallback(thread, self->value.objectReferenceValue, self, &callback);
    } break;
    case Arcadia_ValueTag_Real32:
    case Arcadia_ValueTag_Real64:
    case Arcadia_ValueTag_Size:
    case Arcadia_ValueTag_Type:
    case Arcadia_ValueTag_Void: {
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static void
Arcadia_WeakReference_visit
  (
    Arcadia_Thread* thread,
    Arcadia_WeakReference* self
  )
{ }

static void
Arcadia_WeakReference_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_WeakReference* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_WeakReference_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 == numberOfArgumentValues1) {
    self->value = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
  } else if (1 == numberOfArgumentValues1) {
    self->value = Arcadia_ValueStack_getValue(thread, 1);
    switch (Arcadia_Value_getTag(&self->value)) {
      case Arcadia_ValueTag_Atom: {
        Arms_addNotifyDestroy(self->value.atomValue, self, NULL, &callback);
      } break;
      case Arcadia_ValueTag_BigInteger: {
      } break;
      case Arcadia_ValueTag_Boolean:
      case Arcadia_ValueTag_ForeignProcedure: {
      } break;
      case Arcadia_ValueTag_ImmutableByteArray: {
        Arms_addNotifyDestroy(self->value.immutableByteArrayValue, self, NULL, &callback);
      } break;
      case Arcadia_ValueTag_ImmutableUtf8String: {
        Arms_addNotifyDestroy(self->value.immutableUtf8StringValue, self, NULL, &callback);
      } break;
      case Arcadia_ValueTag_Integer16:
      case Arcadia_ValueTag_Integer32:
      case Arcadia_ValueTag_Integer64:
      case Arcadia_ValueTag_Integer8:
      case Arcadia_ValueTag_Natural16:
      case Arcadia_ValueTag_Natural32:
      case Arcadia_ValueTag_Natural64:
      case Arcadia_ValueTag_Natural8: {
      } break;
      case Arcadia_ValueTag_ObjectReference: {
        Arcadia_Object_addNotifyDestroyCallback(thread, self->value.objectReferenceValue, self, &callback);
      } break;
      case Arcadia_ValueTag_Real32:
      case Arcadia_ValueTag_Real64:
      case Arcadia_ValueTag_Size:
      case Arcadia_ValueTag_Type:
      case Arcadia_ValueTag_Void: {
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
}

Arcadia_WeakReference*
Arcadia_WeakReference_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushValue(thread, &value);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_WeakReference);
}

Arcadia_Value
Arcadia_WeakReference_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_WeakReference* self
  )
{ return self->value; }
