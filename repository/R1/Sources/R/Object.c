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

#include "Arms.h"
#include "R/TypeNames.h"
#include "R.h"
#include <string.h>

#define TypeNodeName "R.Internal.TypeNode"

#define ObjectTypeName "R.Object"

static R_Status
allocateArms
  (
    void **p,
    char const* name,
    size_t nameLength,
    size_t size
  )
{
  void* q = NULL;
  Arms_Status status = Arms_allocate(&q, name, nameLength, size);
  switch (status) {
    case Arms_Status_Success: {
      *p = q;
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return R_Status_AllocationFailed;
    } break;
    case Arms_Status_TypeNotExists: {
      // @todo Add and use R_Status_TypeNotExists.
      return R_Status_OperationInvalid;
    } break;
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_OperationInvalid:
    case Arms_Status_TypeExists:
    default: {
      // This should not happen.
      return R_Status_OperationInvalid;
    } break;
  };
}

static R_Status
runArms
  (
  )
{
  Arms_Status status = Arms_run();
  switch (status) {
    case Arms_Status_Success: {
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed:
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is R_Status_EnvironmentInvalid.
      return R_Status_OperationInvalid;
    } break;
  };
}

typedef struct TypeNode TypeNode;

static void TypeNode_visit(TypeNode* typeNode);

static void TypeNode_finalize(TypeNode* typeNode);

struct TypeNode {
  TypeNode* next;

  _TypeName* typeName;
  R_TypeKind kind;
  TypeNode* parent;
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
  _TypeNames_destroyTypeName(typeNode->typeName);
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
  _R_TypeNames_startup();
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
    if (!current->parent) {
      TypeNode* node = current;
      *previous = current->next;
      current = current->next;
      Arms_unlock(node);
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
  R_Status status = runArms();
  if (status) {
    R_setStatus(status);
    R_jump();
  }
  // TODO: Make this re-entrant.
  _R_TypeNames_shutdown();
}

void
R_registerBooleanType
  (
    char const* name,
    size_t nameLength
  )
{
  _TypeName* typeName = _TypeNames_createTypeName(name, nameLength);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
      if (TypeNames_areTypeNamesEqual(typeNode->typeName, typeName)) {
        R_popJumpTarget();
        _TypeNames_destroyTypeName(typeName);
        typeName = NULL;
        R_setStatus(R_Status_TypeExists);
        R_jump();
      }
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_jump();
  }
  TypeNode* typeNode = NULL;
  R_Status status = allocateArms(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  if (status) {
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_setStatus(status);
    R_jump();
  }
  typeNode->kind = R_TypeKind_Boolean;
  typeNode->typeName = typeName;
  typeNode->parent = NULL;
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
  _TypeName* typeName = _TypeNames_createTypeName(name, nameLength);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
      if (TypeNames_areTypeNamesEqual(typeNode->typeName, typeName)) {
        R_popJumpTarget();
        _TypeNames_destroyTypeName(typeName);
        typeName = NULL;
        R_setStatus(R_Status_TypeExists);
        R_jump();
      }
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_jump();
  }
  TypeNode* typeNode = NULL;
  R_Status status = allocateArms(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  if (status) {
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_setStatus(status);
    R_jump();
  }
  typeNode->kind = R_TypeKind_Integer;
  typeNode->typeName = typeName;
  typeNode->parent = NULL;
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
  _TypeName* typeName = _TypeNames_createTypeName(name, nameLength);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
      if (TypeNames_areTypeNamesEqual(typeNode->typeName, typeName)) {
        R_popJumpTarget();
        _TypeNames_destroyTypeName(typeName);
        typeName = NULL;
        R_setStatus(R_Status_TypeExists);
        R_jump();
      }
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_jump();
  }
  TypeNode* typeNode = NULL;
  R_Status status = allocateArms(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  if (status) {
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_setStatus(status);
    R_jump();
  }
  typeNode->kind = R_TypeKind_Natural;
  typeNode->typeName = typeName;
  typeNode->parent = NULL;
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
    R_Object_VisitCallbackFunction* visit,
    R_Object_DestructCallbackFunction* destruct
  )
{
  _TypeName* typeName = _TypeNames_createTypeName(name, nameLength);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
      if (TypeNames_areTypeNamesEqual(typeNode->typeName, typeName)) {
        R_popJumpTarget();
        _TypeNames_destroyTypeName(typeName);
        typeName = NULL;
        R_setStatus(R_Status_TypeExists);
        R_jump();
      }
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_jump();
  }
  TypeNode *typeNode = NULL;
  R_Status status = allocateArms(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  if (status) {
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_setStatus(status);
    R_jump();
  }
  typeNode->kind = R_TypeKind_Object;
  typeNode->typeName = typeName;
  typeNode->parent = NULL;
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
  _TypeName* typeName = _TypeNames_createTypeName(name, nameLength);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
      if (TypeNames_areTypeNamesEqual(typeNode->typeName, typeName)) {
        R_popJumpTarget();
        _TypeNames_destroyTypeName(typeName);
        typeName = NULL;
        R_setStatus(R_Status_TypeExists);
        R_jump();
      }
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_jump();
  }
  TypeNode* typeNode = NULL;
  R_Status status = allocateArms(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  if (status) {
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_setStatus(status);
    R_jump();
  }
  typeNode->kind = R_TypeKind_Size;
  typeNode->typeName = typeName;
  typeNode->parent = NULL;
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
  _TypeName* typeName = _TypeNames_createTypeName(name, nameLength);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
      if (TypeNames_areTypeNamesEqual(typeNode->typeName, typeName)) {
        R_popJumpTarget();
        _TypeNames_destroyTypeName(typeName);
        typeName = NULL;
        R_setStatus(R_Status_TypeExists);
        R_jump();
      }
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_jump();
  }
  TypeNode* typeNode = NULL;
  R_Status status = allocateArms(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  if (status) {
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_setStatus(status);
    R_jump();
  }
  typeNode->kind = R_TypeKind_Void;
  typeNode->typeName = typeName;
  typeNode->parent = NULL;
  typeNode->valueSize = 0;
  typeNode->visit = NULL;
  typeNode->destruct = NULL;

  typeNode->next = g_typeNodes;
  g_typeNodes = typeNode;

  Arms_lock(typeNode);
}

R_Type*
R_getObjectType
  (
    char const* name,
    size_t nameLength
  )
{
  _TypeName* typeName = _TypeNames_createTypeName(name, nameLength);
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (TypeNode* typeNode = g_typeNodes; NULL != typeNode; typeNode = typeNode->next) {
      if (TypeNames_areTypeNamesEqual(typeNode->typeName, typeName)) {
        R_popJumpTarget();
        _TypeNames_destroyTypeName(typeName);
        typeName = NULL;
        return typeNode;
      }
    }
    R_popJumpTarget();
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_setStatus(R_Status_TypeNotExists);
    R_jump();
  } else {
    R_popJumpTarget();
    _TypeNames_destroyTypeName(typeName);
    typeName = NULL;
    R_jump();
  }
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
    type = type->parent;
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
    type = type->parent;
    objectTag->type = type;
  }
}

void*
R_allocateObject
  (
    char const* name,
    size_t nameLength,
    size_t size
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
  R_Type* type = R_getObjectType(name, nameLength);
  ObjectTag* tag = NULL;
  if (SIZE_MAX - sizeof(ObjectTag) < size) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  Arms_Status status = Arms_allocate(&tag, ObjectTypeName, sizeof(ObjectTypeName) - 1, sizeof(ObjectTag) + size);
  switch (status) {
    case Arms_Status_Success: {
      tag->type = type;
      return (void*)(tag + 1);
    } break;
    case Arms_Status_AllocationFailed: {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    } break;
    case Arms_Status_TypeNotExists: {
      // @todo Add and use R_Status_TypeNotExists.
      R_setStatus(Arms_Status_OperationInvalid);
      R_jump();
    } break;
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_OperationInvalid:
    case Arms_Status_TypeExists:
    default: {
      // This should not happen.
      R_setStatus(Arms_Status_OperationInvalid);
      R_jump();
    } break;
  };
}

void
R_Object_visit
  (
    void* p
  )
{
  if (p) {
    Arms_visit(p);
  }
}

R_BooleanValue
R_UnmanagedMemory_allocate_nojump
  (
    void** p,
    R_SizeValue n
  )
{
  Arms_Status status = Arms_allocateUnmanaged(p, n);
  if (status) {
    if (status == Arms_Status_ArgumentValueInvalid) {
      R_setStatus(R_Status_ArgumentValueInvalid);
    } else if (status == Arms_Status_AllocationFailed) {
      R_setStatus(R_Status_AllocationFailed);
    } else {
      R_setStatus(R_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use R_Status_EnvironmentInvalid.*/
    }
    return R_BooleanValue_False;
  }
  return R_BooleanValue_True;
}

R_BooleanValue
R_UnmanagedMemory_deallocate_nojump
  (
    void* p
  )
{
  Arms_Status status = Arms_deallocateUnmanaged(p);
  if (status) {
    if (status == Arms_Status_ArgumentValueInvalid) {
      R_setStatus(R_Status_ArgumentValueInvalid);
    } else {
      R_setStatus(R_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use R_Status_EnvironmentInvalid.*/
    }
    return R_BooleanValue_False;
  }
  return R_BooleanValue_True;
}

R_BooleanValue
R_UnmanagedMemory_reallocate_nojump
  (
    void** p,
    R_SizeValue n
  )
{
  Arms_Status status = Arms_reallocateUnmanaged(p, n);
  if (status) {
    if (status == Arms_Status_ArgumentValueInvalid) {
      R_setStatus(R_Status_ArgumentValueInvalid);
    } else if (status == Arms_Status_AllocationFailed) {
      R_setStatus(R_Status_AllocationFailed);
    } else {
      R_setStatus(R_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use R_Status_EnvironmentInvalid.*/
    }
    return R_BooleanValue_False;
  }
  return R_BooleanValue_True;
}
