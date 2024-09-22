// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// at R_startupTypes(), we register R.Internal.TypeNode as an ARMS type.
// when we add such a type node, then it is locked.
// on R_shutdownTypes(), all type nodes are unlocked and ARMS is run.

#include "R/Object.h"

#include <string.h>
#include "R/ArmsIntegration.h"
#include "R/TypeNames.h"
#include "R.h"

#define ObjectTypeName "R.Object"

typedef struct ObjectTag ObjectTag;

struct ObjectTag {
  R_Type* type;
};


static bool g_objectRegistered = false;

static void onObjectTypeRemoved(uint8_t const* name, size_t nameLength);

static void onFinalizeObject(void* p);

static void onVisitObject(void* p);

static void onObjectTypeRemoved(uint8_t const* name, size_t nameLength) {
  g_objectRegistered = false;
}

static void
onVisitObject
  (
    void* p
  )
{
  ObjectTag* objectTag = (ObjectTag*)p;
  R_Type* type = (R_Type*)objectTag->type;
  while (type) {
    R_Object_VisitCallbackFunction* visit = R_Type_getVisitCallbackFunction(type);
    if (visit) {
      visit(((ObjectTag*)p) + 1);
    }
    type = R_Type_getParentObjectType(type);
  }
}

static void
onFinalizeObject
  (
    void* p
  )
{
  ObjectTag* objectTag = (ObjectTag*)p;
  R_Type* type = (R_Type*)objectTag->type;
  while (type) {
    R_Object_DestructCallbackFunction* destruct = R_Type_getDestructCallbackFunction(type);
    if (destruct) {
      destruct(((ObjectTag*)p) + 1);
    }
    type = R_Type_getParentObjectType(type);
    objectTag->type = type;
  }
}

void*
R_allocateObject
  (
    R_Type *type
  )
{
  if (!g_objectRegistered) {
    if (!R_Arms_registerType_nojump(ObjectTypeName, sizeof(ObjectTypeName) - 1, &onObjectTypeRemoved, &onVisitObject, &onFinalizeObject)) {
      R_jump();
    }
    g_objectRegistered = R_BooleanValue_True;
  }
  if (!type) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!R_Type_isObjectKind(type)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  ObjectTag* tag = NULL;
  if (SIZE_MAX - sizeof(ObjectTag) < R_Type_getValueSize(type)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  if (!R_Arms_allocate_nojump(&tag, ObjectTypeName, sizeof(ObjectTypeName) - 1, sizeof(ObjectTag) + R_Type_getValueSize(type))) {
    R_jump();
  }
  tag->type = type;
  return (void*)(tag + 1);
}

void
R_Object_setType
  (
    void* self,
    R_Type* type
  )
{
  ObjectTag* objectTag = ((ObjectTag*)self) - 1;
  objectTag->type = type;
}

void
R_Object_visit
  (
    void* self
  )
{
  R_Arms_visit(self);
}

R_Type*
R_Object_getType
  (
    void* self
  )
{
  ObjectTag* objectTag = ((ObjectTag*)self) - 1;
  return objectTag->type;
}
