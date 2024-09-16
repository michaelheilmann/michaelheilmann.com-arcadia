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

#include "R/ArmsIntegration.h"
#include "R/TypeNames.h"
#include "R.h"
#include <string.h>

#define TypeNodeName "R.Internal.TypeNode"

#define ObjectTypeName "R.Object"

typedef struct TypeNode TypeNode;

static void TypeNode_visit(TypeNode* typeNode);

static void TypeNode_finalize(TypeNode* typeNode);

struct TypeNode {
  TypeNode* next;

  R_TypeNameValue typeName;
  R_TypeKind kind;
  TypeNode* parentObjectType;
  R_SizeValue valueSize;
  R_Object_VisitCallbackFunction* visit;
  R_Object_DestructCallbackFunction* destruct;
};

static void
TypeNode_visit
  (
    TypeNode* typeNode
  )
{/*Intentionally empty.*/}

static void
TypeNode_finalize
  (
    TypeNode* typeNode
  )
{
  typeNode->typeName = NULL;
}

typedef struct ObjectTag ObjectTag;

struct ObjectTag {
  TypeNode* type;
};

static TypeNode* g_typeNodes = NULL;

static bool g_registered = false;

static void onVisitObject(void* p);

static void onFinalizeObject(void* p);

void
_R_startupTypes
  (
  )
{
  R_Status status = Arms_registerType(TypeNodeName, sizeof(TypeNodeName) - 1, &TypeNode_visit, &TypeNode_finalize);
  switch (status) {
    case Arms_Status_Success: {
    } break;
    case Arms_Status_AllocationFailed: {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    } break;
    case Arms_Status_ArgumentValueInvalid: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_TypeExists: {
      R_setStatus(Arms_Status_OperationInvalid);
      R_jump();
    } break;
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      R_setStatus(Arms_Status_OperationInvalid);
      R_jump();
    } break;
  };
  R_TypeNames_startup();
  g_typeNodes = NULL;
  g_registered = false;
}

void
_R_shutdownTypes
  (
  )
{
  g_registered = false;
  while (g_typeNodes) {
    // At each iteration, remove the leaves of the type tree.
    TypeNode** previous = &g_typeNodes;
    TypeNode* current = g_typeNodes;
    if (!current->parentObjectType) {
      TypeNode* node = current;
      *previous = current->next;
      current = current->next;
      Arms_unlock(node);
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
  R_Status status = R_Arms_run();
  if (status) {
    R_setStatus(status);
    R_jump();
  }
  // TODO: Make this re-entrant.
  R_TypeNames_shutdown();
}

R_TypeKind
R_Type_getKind
  (
    R_Type const* self
  )
{ return ((TypeNode*)self)->kind; }

void
R_registerBooleanType
  (
    char const* name,
    size_t nameLength
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_Arms_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Boolean;
  typeNode->typeName = typeName;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->visit = NULL;
  typeNode->destruct = NULL;

  typeNode->next = g_typeNodes;
  g_typeNodes = typeNode;

  Arms_lock(typeNode);
}

void
R_registerIntegerType
  (
    char const* name,
    size_t nameLength
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_Arms_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Integer;
  typeNode->typeName = typeName;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->visit = NULL;
  typeNode->destruct = NULL;

  typeNode->next = g_typeNodes;
  g_typeNodes = typeNode;

  Arms_lock(typeNode);
}

void
R_registerNaturalType
  (
    char const* name,
    size_t nameLength
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_Arms_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Natural;
  typeNode->typeName = typeName;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->visit = NULL;
  typeNode->destruct = NULL;

  typeNode->next = g_typeNodes;
  g_typeNodes = typeNode;

  Arms_lock(typeNode);
}

void
R_registerObjectType
  (
    char const* name,
    size_t nameLength,
    size_t valueSize,
    R_Type* parentObjectType,
    R_Object_VisitCallbackFunction* visit,
    R_Object_DestructCallbackFunction* destruct
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_Arms_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Object;
  typeNode->typeName = typeName;
  typeNode->parentObjectType = parentObjectType;
  typeNode->valueSize = valueSize;
  typeNode->visit = visit;
  typeNode->destruct = destruct;

  typeNode->next = g_typeNodes;
  g_typeNodes = typeNode;

  Arms_lock(typeNode);
}

void
R_registerSizeType
  (
    char const* name,
    size_t nameLength
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_Arms_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Size;
  typeNode->typeName = typeName;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->visit = NULL;
  typeNode->destruct = NULL;

  typeNode->next = g_typeNodes;
  g_typeNodes = typeNode;

  Arms_lock(typeNode);
}

void
R_registerVoidType
  (
    char const* name,
    size_t nameLength
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_Arms_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Void;
  typeNode->typeName = typeName;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->visit = NULL;
  typeNode->destruct = NULL;

  typeNode->next = g_typeNodes;
  g_typeNodes = typeNode;

  Arms_lock(typeNode);
}

R_BooleanValue
R_Type_isSubType
  (
    R_Type const* self,
    R_Type const* other
  )
{
  TypeNode* self1 = (TypeNode*)self;
  TypeNode* other1 = (TypeNode*)other;
  if (self1->kind != R_TypeKind_Object || other1->kind != R_TypeKind_Object) {
    return R_BooleanValue_False;
  }
  do {  
    if (self1 == other1) return R_BooleanValue_True;
    self1 = self1->parentObjectType;
  } while (NULL != self1);
  return R_BooleanValue_False;
}

R_Type*
R_getObjectType
  (
    char const* name,
    size_t nameLength
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      return typeNode;
    }
  }
  R_setStatus(R_Status_TypeNotExists);
  R_jump();
}

static void
onVisitObject
  (
    void* p
  )
{
  ObjectTag* objectTag = (ObjectTag*)p;
  TypeNode* type = (TypeNode*)objectTag->type;
  while (type) {
    if (type->visit) {
      type->visit(((ObjectTag*)p) + 1);
    }
    type = type->parentObjectType;
  }
}

static void
onFinalizeObject
  (
    void* p
  )
{
  ObjectTag* objectTag = (ObjectTag*)p;
  TypeNode* type = (TypeNode*)objectTag->type;
  while (type) {
    if (type->destruct) {
      type->destruct(((ObjectTag*)p) + 1);
    }
    type = type->parentObjectType;
    objectTag->type = type;
  }
}

void*
R_allocateObject
  (
    R_Type *type
  )
{
  if (!g_registered) {
    Arms_Status status;
    status = Arms_registerType(ObjectTypeName, sizeof(ObjectTypeName) - 1, &onVisitObject, &onFinalizeObject);
    switch (status) {
      case Arms_Status_Success: {
        g_registered = true;
      } break;
      case Arms_Status_AllocationFailed: {
        R_setStatus(R_Status_AllocationFailed);
        R_jump();
      } break;
      case Arms_Status_ArgumentValueInvalid: {
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
      case Arms_Status_OperationInvalid:
      case Arms_Status_TypeExists: {
        R_setStatus(Arms_Status_OperationInvalid);
        R_jump();
      } break;
      case Arms_Status_TypeNotExists:
      default: {
        // This should not happen.
        R_setStatus(Arms_Status_OperationInvalid);
        R_jump();
      } break;
    };
  }
  if (!type) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!R_Type_isObjectKind(type)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  TypeNode* typeNode = (TypeNode*)type;
  ObjectTag* tag = NULL;
  if (SIZE_MAX - sizeof(ObjectTag) < typeNode->valueSize) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  if (!R_Arms_allocate_nojump(&tag, ObjectTypeName, sizeof(ObjectTypeName) - 1, sizeof(ObjectTag) + typeNode->valueSize)) {
    R_jump();
  }
  tag->type = type;
  return (void*)(tag + 1);
}

void
R_Object_visit
  (
    void* object
  )
{
  if (object) {
    Arms_visit(object);
  }
}

R_Type*
R_Object_getType
  (
    void* object
  )
{
  ObjectTag* objectTag = ((ObjectTag*)object) - 1;
  return objectTag->type;
}
