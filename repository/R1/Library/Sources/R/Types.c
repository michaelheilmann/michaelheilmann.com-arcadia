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

// Last modified: 2024-10-07

#include "R/Types.internal.h"

#include "R/ArmsIntegration.h"
#include "R/JumpTarget.h"
#include "R/TypeNames.h"
#include "R/cstdlib.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
registerTypeType
  (
  );

static void
registerAtomType
  (
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define TypeNodeName "R.Internal.TypeNode"

typedef struct TypeNode TypeNode;

static void
TypeNode_typeRemovedCallback
  (
    uint8_t const* name,
    size_t nameLength
  );

static void
TypeNode_finalizeCallback
  (
    TypeNode* typeNode
  );

static void
TypeNode_visitCallback
  (
    TypeNode* typeNode
  );

typedef struct TypeNodes TypeNodes;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct TypeNodes {
  TypeNode* typeNodes;
};

static TypeNodes* g_typeNodes = NULL;

static bool g_typeNodeRegistered = false;

static void
TypeNode_typeRemovedCallback
  (
    uint8_t const* name,
    size_t nameLength
  )
{ g_typeNodeRegistered = false; }

static void
TypeNode_finalizeCallback
  (
    TypeNode* typeNode
  )
{
  if (typeNode->parentObjectType) {
    if (R_Arms_unlock(typeNode->parentObjectType)) {
      fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  typeNode->typeName = NULL;
}

static void
TypeNode_visitCallback
  (
    TypeNode* typeNode
  )
{
  R_TypeName_visit(typeNode->typeName);
}

static TypeNodes*
TypeNodes_create
  (
  )
{ 
  TypeNodes* typeNodes = NULL;
  if (!R_allocateUnmanaged_nojump(&typeNodes, sizeof(TypeNodes))) {
    return NULL;
  }
  typeNodes->typeNodes = NULL;
  return typeNodes;
}

static void
TypeNodes_destroy
  (
    TypeNodes* typeNodes
  )
{
  while (typeNodes->typeNodes) {
    // At each iteration, remove the leaves of the type tree.
    TypeNode** previous = &typeNodes->typeNodes;
    TypeNode* current = typeNodes->typeNodes;
    if (!R_Type_hasChildren(current)) {
      TypeNode* node = current;
      *previous = current->next;
      current = current->next;
      node->typeDestructing(NULL);
      R_Arms_unlock(node);
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void
_R_Types_startup
  (
  )
{
  if (!g_typeNodeRegistered) {
    if (!R_Arms_registerType_nojump(TypeNodeName, sizeof(TypeNodeName) - 1, &TypeNode_typeRemovedCallback, &TypeNode_visitCallback, &TypeNode_finalizeCallback)) {
      R_jump();
    }
    g_typeNodeRegistered = R_BooleanValue_True;
  }
  R_TypeNames_startup();
  g_typeNodes = TypeNodes_create();
  if (!g_typeNodes) {
    R_TypeNames_shutdown();
    R_jump();
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    registerTypeType();
    registerAtomType();
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    TypeNodes_destroy(g_typeNodes);
    g_typeNodes = NULL;
    R_Status status = R_Arms_run();
    if (status) {
      /*Intentionally empty.*/
    }
    R_TypeNames_shutdown();
    R_jump();
  }
}

R_SizeValue
R_Type_getValueSize
  (
    R_Type const* self
  )
{ return ((TypeNode const*)self)->valueSize; }

R_Type*
R_Type_getParentObjectType
  (
    R_Type const* self
  )
{ return ((TypeNode const*)self)->parentObjectType; }

R_Type_VisitObjectCallbackFunction*
R_Type_getVisitObjectCallbackFunction
  (
    R_Type const* self
  )
{
  TypeNode const* typeNode = (TypeNode const*)self;
  if (!typeNode->typeOperations->objectTypeOperations) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  return typeNode->typeOperations->objectTypeOperations->visit;
}

R_Type_DestructObjectCallbackFunction*
R_Type_getDestructObjectCallbackFunction
  (
    R_Type const* self
  )
{
  TypeNode const* typeNode = (TypeNode const*)self;
  if (!typeNode->typeOperations->objectTypeOperations) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  return typeNode->typeOperations->objectTypeOperations->destruct;
}

R_BooleanValue
R_Type_hasChildren
  (
    R_Type const* self
  )
{
  if (!R_Type_isObjectKind(self)) {
    return R_BooleanValue_False;
  }
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (R_Type_isObjectKind(typeNode)) {
      if (R_Type_getParentObjectType(typeNode) == (TypeNode const*)self) {
        return R_BooleanValue_True;
      }
    }
  }
  return R_BooleanValue_False;
}

void
_R_Types_shutdown
  (
  )
{
  R_Status status;
  status = R_Arms_run();
  if (status) {
    /* Intentionally empty.*/
  }
  TypeNodes_destroy(g_typeNodes);
  g_typeNodes = NULL;
  
  status = R_Arms_run();
  if (status) {
    /* Intentionally empty.*/
  }
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
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Boolean;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
}

void
R_registerForeignValueType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_ForeignValue;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
}

void
R_registerIntegerType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Integer;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
}

void
R_registerNaturalType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Natural;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
}

void
R_registerObjectType
  (
    char const* name,
    size_t nameLength,
    size_t valueSize,
    R_Type* parentObjectType,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Object;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = parentObjectType;
  if (typeNode->parentObjectType) {
    if (R_Arms_lock(typeNode->parentObjectType)) { /* @todo: Can raise due to allocation failure or lock count overflow. */
      fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  typeNode->valueSize = valueSize;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL != typeNode->typeOperations->objectTypeOperations);
  assert(NULL != typeNode->typeOperations->objectTypeOperations->construct);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode); /* @todo Can raise due to allocation failure. Can we built-in a guarantee that at least one lock is always available? */
}

void
R_registerRealType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Real;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
}

void
R_registerSizeType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Size;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
}

void
R_registerTypeType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Internal;
  typeNode->typeName = typeName;
  typeNode->typeOperations = NULL;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
}


void
R_registerVoidType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Void;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
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
  if (self1->kind == other1->kind) {
    if (self1->kind == R_TypeKind_Object) {
      do {
        if (self1 == other1) {
          return R_BooleanValue_True;
        }
        self1 = self1->parentObjectType;
      } while (NULL != self1);
      return R_BooleanValue_False;
    } else {
      return self1 == other1;
    }
  } else {
    return R_BooleanValue_False;
  }
}

R_Type*
R_getType
  (
    char const* name,
    size_t nameLength
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName(name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      return typeNode;
    }
  }
  fwrite("type `", 1, sizeof("type `") - 1, stderr);
  fwrite(name, 1, nameLength, stderr);
  fwrite("` not found", 1, sizeof("` not found") - 1, stderr);
  fwrite("\n", 1, sizeof("\n") - 1, stderr);
  R_setStatus(R_Status_TypeNotExists);
  R_jump();
}

R_TypeNameValue
R_Type_getName
  (
    R_Type* type
  )
{
  TypeNode* typeNode = (TypeNode*)type;
  return typeNode->typeName;
}

R_Type_Operations const*
R_Type_getOperations
  (
    R_Type* type
  )
{
  TypeNode* typeNode = (TypeNode*)type;
  return typeNode->typeOperations;
}

static TypeNode* g_typeType = NULL;

static void typeTypeDestructing(void* context) {
  g_typeType = NULL;
}

static void
registerTypeType
  (
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName("R.Internal.Type", sizeof("R.Internal.Type") - 1);
#if _DEBUG
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
#endif
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Internal;
  typeNode->typeName = typeName;
  typeNode->typeOperations = NULL;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = &typeTypeDestructing;

  assert(NULL == typeNode->typeOperations);
  /*assert(NULL == typeNode->typeOperations->objectTypeOperations);*/

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  g_typeType = typeNode;

  R_Arms_lock(typeNode);
}

static TypeNode* g_atomType = NULL;

static void atomTypeDestructing(void* context) {
  g_atomType = NULL;
}


static void
registerAtomType
  (
  )
{
  R_TypeNameValue typeName = R_TypeNames_getOrCreateTypeName("R.Internal.Atom", sizeof("R.Internal.Atom") - 1);
#if _DEBUG
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      R_setStatus(R_Status_TypeExists);
      R_jump();
    }
  }
#endif
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(&typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    R_jump();
  }
  typeNode->kind = R_TypeKind_Internal;
  typeNode->typeName = typeName;
  typeNode->typeOperations = NULL;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = &atomTypeDestructing;

  assert(NULL == typeNode->typeOperations);
  /*assert(NULL == typeNode->typeOperations->objectTypeOperations);*/

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  g_typeType = typeNode;

  R_Arms_lock(typeNode);
}

R_Type*
_R_Type_getType
  (
  )
{ return g_typeType; }

R_Type*
_R_Atom_getType
  (
  )
{ return g_atomType; }

R_SizeValue
R_Type_hash
  (
    R_TypeValue self
  )
{ return R_TypeName_hash(R_Type_getName(self)); }
