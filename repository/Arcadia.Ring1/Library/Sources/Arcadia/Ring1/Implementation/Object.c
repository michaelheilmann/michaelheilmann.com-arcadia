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

// Last modified: 2025-01-01

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Object.h"

#include "Arcadia/Ring1/Include.h"
#include <stdio.h>

static void
Arcadia_Object_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
equalTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
hash
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
notEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Object_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &equalTo,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = &hash,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = &notEqualTo,
  .or = NULL,
  .subtract = NULL,
};

void
Arcadia_Object_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Object* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = Arcadia_getType(thread, u8"Arcadia.Object", sizeof(u8"Arcadia.Object") - 1);
  Arcadia_Object_setType(thread, _self, _type);
}

static void
equalTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Value_isObjectReferenceValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getObjectReferenceValue(A1) == Arcadia_Value_getObjectReferenceValue(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
hash
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setSizeValue(target, (Arcadia_SizeValue)(uintptr_t)Arcadia_Value_getObjectReferenceValue(A1));
#undef A1
}

static void
notEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (!Arcadia_Value_isObjectReferenceValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getObjectReferenceValue(A1) != Arcadia_Value_getObjectReferenceValue(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
#undef A2
#undef A1
}

#define ObjectTypeName u8"Arcadia.Object"

typedef struct ObjectTag ObjectTag;

struct ObjectTag {
  Arcadia_TypeValue type;
};

static bool g_objectRegistered = false;

static void
onObjectTypeRemoved
  (
    Arcadia_Process* process,
    uint8_t const* name,
    size_t nameLength
  );

static void
onFinalizeObject
  (
    Arcadia_Process* process,
    void* object
  );

static void
onVisitObject
  (
    Arcadia_Process* process,
    void* object
  );

static void
onObjectTypeRemoved
  (
    Arcadia_Process* process,
    const uint8_t* name,
    size_t nameLength
  )
{
  g_objectRegistered = false;
}

static void
onFinalizeObject
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
onVisitObject
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

void*
Arcadia_allocateObject
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue type,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  if (!type) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_Type_isObjectKind(thread, type)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
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
  Arcadia_Value selfValue = Arcadia_Value_Initializer();
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)(Arcadia_Object*)(tag + 1));
  Arcadia_Type_getOperations(type)->objectTypeOperations->construct(thread, &selfValue, numberOfArgumentValues, &argumentValues[0]);
  return (void*)(tag + 1);
}

static Arcadia_TypeValue g__Arcadia_Object_type = NULL;

static void
typeDestructing
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
                                 &onObjectTypeRemoved, &onVisitObject, &onFinalizeObject);
    g_objectRegistered = Arcadia_BooleanValue_True;
  }
  if (!g__Arcadia_Object_type) {
    g__Arcadia_Object_type = Arcadia_registerObjectType(thread, ObjectTypeName, sizeof(ObjectTypeName) - 1, sizeof(Arcadia_Object), NULL, &_typeOperations, &typeDestructing);
  }
  return g__Arcadia_Object_type;
}

void
Arcadia_Object_setType
  (
    Arcadia_Thread* thread,
    void* self,
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
    void* self
  )
{
  ObjectTag* tag = ((ObjectTag*)self) - 1;
  Arcadia_Process_visitObject(Arcadia_Thread_getProcess(thread), tag->type);
  Arcadia_Process_visitObject(Arcadia_Thread_getProcess(thread), tag);
}

void
Arcadia_Object_lock
  (
    Arcadia_Thread* thread,
    void* self
  )
{
  Arcadia_Status status = Arcadia_Process_lockObject(Arcadia_Thread_getProcess(thread), ((ObjectTag*)self) - 1);
  if (status) {
    Arcadia_Thread_setStatus(thread, status);
    Arcadia_Thread_jump(thread);
  }
}

void
Arcadia_Object_unlock
  (
    Arcadia_Thread* thread,
    void* self
  )
{
  Arcadia_Status status = Arcadia_Process_unlockObject(Arcadia_Thread_getProcess(thread), ((ObjectTag*)self) - 1);
  if (status) {
    Arcadia_Thread_setStatus(thread, status);
    Arcadia_Thread_jump(thread);
  }
}

Arcadia_TypeValue
Arcadia_Object_getType
  (
    void* self
  )
{
  ObjectTag* objectTag = ((ObjectTag*)self) - 1;
  return objectTag->type;
}
