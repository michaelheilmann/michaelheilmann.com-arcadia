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
#include "Arcadia/Ring1/Implementation/Object.h"

#include "Arcadia/Ring1/Include.h"
#include <stdio.h>

static void*
Arcadia_allocateObject
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue type
  );

static void
Arcadia_Object_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  );

static void
identical
  (
    Arcadia_Thread* thread
  );

static void
isEqualTo
  (
    Arcadia_Thread* thread
  );

static void
hash
  (
    Arcadia_Thread* thread
  );

static void
isNotEqualTo
  (
    Arcadia_Thread* thread
  );

static const Arcadia_ObjectType_Operations _Arcadia_Object_objectTypeOperations = {
  .construct = &Arcadia_Object_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _Arcadia_Object_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Object_objectTypeOperations,
  .identical = &identical,
  .equalTo = &isEqualTo,
  .hash = &hash,
  .notEqualTo = &isNotEqualTo,
};

#define BINARY_OPERATION() \
  if (Arcadia_ValueStack_getSize(thread) < 3) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  if (2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 2); \
  Arcadia_Value y = Arcadia_ValueStack_getValue(thread, 1); \
  Arcadia_ValueStack_popValues(thread, 3);

#define UNARY_OPERATION() \
  if (Arcadia_ValueStack_getSize(thread) < 2) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  if (1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) { \
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid); \
    Arcadia_Thread_jump(thread); \
  } \
  Arcadia_Value x = Arcadia_ValueStack_getValue(thread, 1); \
  Arcadia_ValueStack_popValues(thread, 2);

void
Arcadia_Object_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Object_getType(thread);
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
identical
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (!Arcadia_Value_isObjectReferenceValue(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getObjectReferenceValue(&x) == Arcadia_Value_getObjectReferenceValue(&y));
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  }
}

static void
isEqualTo
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (!Arcadia_Value_isObjectReferenceValue(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getObjectReferenceValue(&x) == Arcadia_Value_getObjectReferenceValue(&y));
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_False);
  }
}

static void
hash
  (
    Arcadia_Thread* thread
  )
{
  UNARY_OPERATION();
  Arcadia_ValueStack_pushSizeValue(thread, (Arcadia_SizeValue)(uintptr_t)Arcadia_Value_getObjectReferenceValue(&x));
}

static void
isNotEqualTo
  (
    Arcadia_Thread* thread
  )
{
  BINARY_OPERATION();
  if (!Arcadia_Value_isObjectReferenceValue(&y)) {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_Value_getObjectReferenceValue(&x) != Arcadia_Value_getObjectReferenceValue(&y));
  } else {
    Arcadia_ValueStack_pushBooleanValue(thread, Arcadia_BooleanValue_True);
  }
}

#define ObjectTypeName u8"Arcadia.Object"

typedef struct ObjectTag ObjectTag;

struct ObjectTag {
  Arcadia_TypeValue type;
};

static bool g_objectRegistered = false;

static void
_Arcadia_Object_onObjectTypeRemoved
  (
    Arcadia_Process* process,
    uint8_t const* name,
    size_t nameLength
  );

static void
_Arcadia_Object_onFinalizeObject
  (
    Arcadia_Process* process,
    void* object
  );

static void
_Arcadia_Object_onVisitObject
  (
    Arcadia_Process* process,
    void* object
  );

static void
_Arcadia_Object_onObjectTypeRemoved
  (
    Arcadia_Process* process,
    const uint8_t* name,
    size_t nameLength
  )
{
  g_objectRegistered = false;
}

static void
_Arcadia_Object_onFinalizeObject
  (
    Arcadia_Process* process,
    void* object
  )
{
  ObjectTag* objectTag = (ObjectTag*)object;
  Arcadia_TypeValue type = (Arcadia_TypeValue)objectTag->type;
  if (Arcadia_Process_unlockObject(process, type)) {
    fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
  }
  if (type == _Arcadia_Memory_getType(Arcadia_Process_getThread(process))) {
    return;
  }
  while (type) {
    Arcadia_Type_DestructObjectCallbackFunction* destruct = Arcadia_Type_getDestructObjectCallbackFunction(type);
    if (destruct) {
      destruct(Arcadia_Process_getThread(process), ((ObjectTag*)object) + 1);
    }

    type = Arcadia_Type_getParentObjectType(Arcadia_Process_getThread(process), type);
    objectTag->type = type;
  }
}

static void
_Arcadia_Object_onVisitObject
  (
    Arcadia_Process* process,
    void* object
  )
{
  ObjectTag* objectTag = (ObjectTag*)object;
  Arcadia_TypeValue type = (Arcadia_TypeValue)objectTag->type;
  if (type == _Arcadia_Memory_getType(Arcadia_Process_getThread(process))) {
    return;
  }
  while (type) {
    Arcadia_Type_VisitObjectCallbackFunction* visit = Arcadia_Type_getVisitObjectCallbackFunction(type);
    if (visit) {
      visit(Arcadia_Process_getThread(process), ((ObjectTag*)object) + 1);
    }
    type = Arcadia_Type_getParentObjectType(Arcadia_Process_getThread(process), type);
  }
}

static void*
Arcadia_allocateObject
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue type
  )
{
  if (!type) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Type_isObjectKind(thread, type)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_Type* memoryType = _Arcadia_Memory_getType(thread);

  ObjectTag* tag = NULL;
  if (SIZE_MAX - sizeof(ObjectTag) < Arcadia_Type_getValueSize(thread, type)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &tag, ObjectTypeName, sizeof(ObjectTypeName) - 1, sizeof(ObjectTag) + Arcadia_Type_getValueSize(thread, type));
  tag->type = memoryType;
  if (Arcadia_Process_lockObject(Arcadia_Thread_getProcess(thread), memoryType)) {
    fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
  }
  Arcadia_Type_getOperations(type)->objectTypeOperations->construct(thread, (Arcadia_ObjectReferenceValue)(Arcadia_Object*)(tag + 1));
  return (void*)(tag + 1);
}

void*
ARCADIA_CREATEOBJECT0
  (
    Arcadia_Thread* thread,
    Arcadia_Type* type,
    Arcadia_SizeValue oldValueStackSize
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    void* self = Arcadia_allocateObject(thread, type);
    if (!self || oldValueStackSize != Arcadia_ValueStack_getSize(thread)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Thread_popJumpTarget(thread);
    return self;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (oldValueStackSize < Arcadia_ValueStack_getSize(thread)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_ValueStack_popValues(thread, Arcadia_ValueStack_getSize(thread) - oldValueStackSize);
    }
    Arcadia_Thread_jump(thread);
  }
}

static Arcadia_TypeValue g__Arcadia_Object_type = NULL;

static void
_Arcadia_Object_typeDestructing
  (
    void* context
  )
{ g__Arcadia_Object_type = NULL; }

Arcadia_TypeValue
_Arcadia_Object_getType
  (
    Arcadia_Thread* thread
  )
{
  if (!g_objectRegistered) {
    Arcadia_Process_registerType(Arcadia_Thread_getProcess(thread), ObjectTypeName, sizeof(ObjectTypeName) - 1, Arcadia_Thread_getProcess(thread),
                                 &_Arcadia_Object_onObjectTypeRemoved, &_Arcadia_Object_onVisitObject, &_Arcadia_Object_onFinalizeObject);
    g_objectRegistered = Arcadia_BooleanValue_True;
  }
  if (!g__Arcadia_Object_type) {
    g__Arcadia_Object_type = Arcadia_registerObjectType(thread, ObjectTypeName, sizeof(ObjectTypeName) - 1, sizeof(Arcadia_Object), NULL,
                                                        &_Arcadia_Object_typeOperations, &_Arcadia_Object_typeDestructing);
  }
  return g__Arcadia_Object_type;
}

void
Arcadia_Object_setType
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    Arcadia_TypeValue type
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  ObjectTag* objectTag = ((ObjectTag*)self) - 1;
  if (type) {
    if (Arcadia_Process_lockObject(process, type)) {
      fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  if (objectTag->type) {
    if (Arcadia_Process_unlockObject(process, objectTag->type)) {
      fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  objectTag->type = type;
}

void
Arcadia_Object_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  )
{
  ObjectTag* tag = ((ObjectTag*)self) - 1;
  Arcadia_Process_visitObject(Arcadia_Thread_getProcess(thread), tag->type);
  Arcadia_Process_visitObject(Arcadia_Thread_getProcess(thread), tag);
}

void
Arcadia_Object_addNotifyDestroyCallback
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    void* observer,
    void (*callback)(void* observer, Arcadia_Object*)
  )
{
  ObjectTag* tag = ((ObjectTag*)self) - 1;
  Arcadia_Status status = Arcadia_Arms_addNotifyDestroy(tag, observer, self, (void (*)(void*,void*))callback);
  if (status) {
    Arcadia_Thread_setStatus(thread, status);
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Object_removeNotifyDestroyCallback
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    void* observer,
    void (*callback)(void* observer, Arcadia_Object*)
  )
{
  ObjectTag* tag = ((ObjectTag*)self) - 1;
  Arcadia_Status status = Arcadia_Arms_removeNotifyDestroy(tag, observer, self, (void (*)(void*, void*))callback);
  if (status) {
    Arcadia_Thread_setStatus(thread, status);
    Arcadia_Thread_jump(thread);
  }
}

#if Arcadia_Configuration_withBarriers

void
Arcadia_Object_forwardBarrier
  (
    Arcadia_Thread* thread,
    Arcadia_Object* source,
    Arcadia_Object* target
  )
{
  if (source && target) {
    ObjectTag* sourceTag = ((ObjectTag*)source) - 1;
    ObjectTag* targetTag = ((ObjectTag*)target) - 1;
    Arcadia_Arms_forwardBarrier(sourceTag, targetTag);
  }
}

void
Arcadia_Object_backwardBarrier
  (
    Arcadia_Thread* thread,
    Arcadia_Object* source,
    Arcadia_Object* target
  )
{
  if (source && target) {
    ObjectTag* sourceTag = ((ObjectTag*)source) - 1;
    ObjectTag* targetTag = ((ObjectTag*)target) - 1;
    Arcadia_Arms_backwardBarrier(sourceTag, targetTag);
  }
}

#endif // Arcadia_Configuration_withBarriers

void
Arcadia_Object_lock
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  )
{
  ObjectTag* tag = ((ObjectTag*)self) - 1;
  Arcadia_Status status = Arcadia_Process_lockObject(Arcadia_Thread_getProcess(thread), tag);
  if (status) {
    Arcadia_Thread_setStatus(thread, status);
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Object_unlock
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  )
{
  ObjectTag* tag = ((ObjectTag*)self) - 1;
  Arcadia_Status status = Arcadia_Process_unlockObject(Arcadia_Thread_getProcess(thread), tag);
  if (status) {
    Arcadia_Thread_setStatus(thread, status);
    Arcadia_Thread_jump(thread);
  }
}

Arcadia_TypeValue
Arcadia_Object_getType
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  )
{
  ObjectTag* objectTag = ((ObjectTag*)self) - 1;
  return objectTag->type;
}

Arcadia_BooleanValue
Arcadia_Object_isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    Arcadia_Value const* other
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(thread, self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  Arcadia_Value temporary = Arcadia_Value_makeObjectReferenceValue(self);

  Arcadia_Natural8Value n = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushValue(thread, &temporary);
  Arcadia_ValueStack_pushValue(thread, other);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  operations->equalTo(thread);
  if (n + 1 != Arcadia_ValueStack_getSize(thread)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BooleanValue returnValue = Arcadia_ValueStack_getBooleanValue(thread, 0);
  Arcadia_ValueStack_popValues(thread, 1);
  return returnValue;
  
}

Arcadia_BooleanValue
Arcadia_Object_isNotEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    Arcadia_Value const* other
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(thread, self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  Arcadia_Value temporary = Arcadia_Value_makeObjectReferenceValue(self);

  Arcadia_Natural8Value n = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushValue(thread, &temporary);
  Arcadia_ValueStack_pushValue(thread, other);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  operations->notEqualTo(thread);
  if (n + 1 != Arcadia_ValueStack_getSize(thread)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BooleanValue returnValue = Arcadia_ValueStack_getBooleanValue(thread, 0);
  Arcadia_ValueStack_popValues(thread, 1);
  return returnValue;
}

Arcadia_SizeValue
Arcadia_Object_getHash
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(thread, self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  Arcadia_Value temporary = Arcadia_Value_makeObjectReferenceValue(self);

  Arcadia_Natural8Value n = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushValue(thread, &temporary);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  operations->hash(thread);
  if (n + 1 != Arcadia_ValueStack_getSize(thread)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue returnValue = Arcadia_ValueStack_getSizeValue(thread, 0);
  Arcadia_ValueStack_popValues(thread, 1);
  return returnValue;
}

Arcadia_BooleanValue
Arcadia_Object_isIdenticalTo
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    Arcadia_Value const* other
  )
{
  Arcadia_TypeValue type = Arcadia_Object_getType(thread, self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  Arcadia_Value temporary = Arcadia_Value_makeObjectReferenceValue(self);

  Arcadia_Natural8Value n = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushValue(thread, &temporary);
  Arcadia_ValueStack_pushValue(thread, other);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  operations->identical(thread);
  if (n + 1 != Arcadia_ValueStack_getSize(thread)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_StackCorruption);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BooleanValue returnValue = Arcadia_ValueStack_getBooleanValue(thread, 0);
  Arcadia_ValueStack_popValues(thread, 1);
  return returnValue;
}
