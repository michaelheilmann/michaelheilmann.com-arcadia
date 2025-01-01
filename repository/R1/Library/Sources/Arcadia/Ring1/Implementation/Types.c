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

// Last modified: 2024-10-07

#include "Arcadia/Ring1/Implementation/Types.private.h"

#include "Arcadia/Ring1/Include.h"
#include "R/Value.h"

#include "R/ArmsIntegration.h"
#include "Arcadia/Ring1/Implementation/Atoms.private.h" ///< @todo A better solution is required for this.

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define TypeNodeName "R.Internal.TypeNode"

typedef struct TypeNode TypeNode;

static void
TypeNode_typeRemovedCallback
  (
    Arcadia_Process* context,
    const uint8_t* name,
    size_t nameLength
  );

static void
TypeNode_finalizeCallback
  (
    Arcadia_Process* context,
    TypeNode* typeNode
  );

static void
TypeNode_visitCallback
  (
    Arcadia_Process* context,
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
    Arcadia_Process* context,
    const uint8_t* name,
    size_t nameLength
  )
{ g_typeNodeRegistered = false; }

static void
TypeNode_finalizeCallback
  (
    Arcadia_Process* context,
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
    Arcadia_Process* context,
    TypeNode* typeNode
  )
{
  Arcadia_Atom_visit(typeNode->typeName);
}

static TypeNodes*
TypeNodes_create
  (
    Arcadia_Process* process
  )
{ 
  TypeNodes* typeNodes = NULL;
  if (!R_allocateUnmanaged_nojump(process, &typeNodes, sizeof(TypeNodes))) {
    return NULL;
  }
  typeNodes->typeNodes = NULL;
  return typeNodes;
}

static void
TypeNodes_destroy
  (
    Arcadia_Process* process,
    TypeNodes* typeNodes
  )
{
  while (typeNodes->typeNodes) {
    // At each iteration, remove the leaves of the type tree.
    TypeNode** previous = &typeNodes->typeNodes;
    TypeNode* current = typeNodes->typeNodes;
    if (!Arcadia_Type_hasChildren(current)) {
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
Arcadia_Types_startup
  (
    Arcadia_Process* process
  )
{
  if (!g_typeNodeRegistered) {
    if (!R_Arms_registerType_nojump(process, TypeNodeName, sizeof(TypeNodeName) - 1, process, &TypeNode_typeRemovedCallback, &TypeNode_visitCallback, &TypeNode_finalizeCallback)) {
      Arcadia_Process_jump(process);
    }
    g_typeNodeRegistered = Arcadia_BooleanValue_True;
  }
  Arcadia_Atoms_startup(process);
  g_typeNodes = TypeNodes_create(process);
  if (!g_typeNodes) {
    Arcadia_Atoms_shutdown(process);
    Arcadia_Process_jump(process);
  }
  R_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    Arcadia_Process_popJumpTarget(process);
  } else {
    Arcadia_Process_popJumpTarget(process);
    TypeNodes_destroy(process, g_typeNodes);
    g_typeNodes = NULL;
    Arcadia_Status status = R_Arms_run();
    if (status) {
      /*Intentionally empty.*/
    }
    Arcadia_Atoms_shutdown(process);
    Arcadia_Process_jump(process);
  }
}

void
Arcadia_Types_shutdown
  (
    Arcadia_Process* process
  )
{
  Arcadia_Status status;
  status = R_Arms_run();
  if (status) {
    /* Intentionally empty.*/
  }
  TypeNodes_destroy(process, g_typeNodes);
  g_typeNodes = NULL;
  
  status = R_Arms_run();
  if (status) {
    /* Intentionally empty.*/
  }
  Arcadia_Atoms_shutdown(process);
}

Arcadia_SizeValue
Arcadia_Type_getValueSize
  (
    Arcadia_TypeValue self
  )
{ return ((TypeNode const*)self)->valueSize; }

Arcadia_TypeValue
Arcadia_Type_getParentObjectType
  (
    Arcadia_TypeValue self
  )
{ return ((TypeNode const*)self)->parentObjectType; }

Arcadia_Type_VisitObjectCallbackFunction*
Arcadia_Type_getVisitObjectCallbackFunction
  (
    Arcadia_TypeValue self
  )
{
  TypeNode const* typeNode = (TypeNode const*)self;
  if (!typeNode->typeOperations->objectTypeOperations) {
    return NULL;
  }
  return typeNode->typeOperations->objectTypeOperations->visit;
}

Arcadia_Type_DestructObjectCallbackFunction*
Arcadia_Type_getDestructObjectCallbackFunction
  (
    Arcadia_TypeValue self
  )
{
  TypeNode const* typeNode = (TypeNode const*)self;
  if (!typeNode->typeOperations->objectTypeOperations) {
    return NULL;
  }
  return typeNode->typeOperations->objectTypeOperations->destruct;
}

Arcadia_BooleanValue
Arcadia_Type_hasChildren
  (
    Arcadia_TypeValue self
  )
{
  if (!Arcadia_Type_isObjectKind(self)) {
    return Arcadia_BooleanValue_False;
  }
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (Arcadia_Type_isObjectKind(typeNode)) {
      if (Arcadia_Type_getParentObjectType(typeNode) == (TypeNode const*)self) {
        return Arcadia_BooleanValue_True;
      }
    }
  }
  return Arcadia_BooleanValue_False;
}

R_TypeKind
Arcadia_Type_getKind
  (
    Arcadia_TypeValue self
  )
{ return ((TypeNode*)self)->kind; }

Arcadia_TypeValue
R_registerInternalType
  (
    Arcadia_Process* process,
    char const* name,
    size_t nameLength,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(process, Arcadia_AtomKind_Name, name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (Arcadia_Atom_isEqualTo(typeNode->typeName, typeName)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TypeExists);
      Arcadia_Process_jump(process);
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(process, &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    Arcadia_Process_jump(process);
  }
  typeNode->kind = R_TypeKind_Internal;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  //assert(NULL != typeNode->typeOperations);
  //assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  R_Arms_lock(typeNode);
  
  return typeNode;
}

Arcadia_TypeValue
R_registerScalarType
  (
    Arcadia_Process* process,
    char const* name,
    size_t nameLength,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(process, Arcadia_AtomKind_Name, name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (Arcadia_Atom_isEqualTo(typeNode->typeName, typeName)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TypeExists);
      Arcadia_Process_jump(process);
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(process, &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    Arcadia_Process_jump(process);
  }
  typeNode->kind = R_TypeKind_Scalar;
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

  return typeNode;
}

Arcadia_TypeValue
R_registerObjectType
  (
    Arcadia_Process* process,
    char const* name,
    size_t nameLength,
    size_t valueSize,
    Arcadia_TypeValue parentObjectType,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(process, Arcadia_AtomKind_Name, name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (Arcadia_Atom_isEqualTo(typeNode->typeName, typeName)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_TypeExists);
      Arcadia_Process_jump(process);
    }
  }
  TypeNode* typeNode = NULL;
  if (!R_allocate_nojump(process, &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode))) {
    Arcadia_Process_jump(process);
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

  return typeNode;
}

Arcadia_BooleanValue
Arcadia_Type_isSubType
  (
    Arcadia_TypeValue self,
    Arcadia_TypeValue other
  )
{
  TypeNode* self1 = (TypeNode*)self;
  TypeNode* other1 = (TypeNode*)other;
  if (self1->kind == other1->kind) {
    if (self1->kind == R_TypeKind_Object) {
      do {
        if (self1 == other1) {
          return Arcadia_BooleanValue_True;
        }
        self1 = self1->parentObjectType;
      } while (NULL != self1);
      return Arcadia_BooleanValue_False;
    } else {
      return self1 == other1;
    }
  } else {
    return Arcadia_BooleanValue_False;
  }
}

R_TypeValue
R_getType
  (
    Arcadia_Process* process,
    char const* name,
    size_t nameLength
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(process, Arcadia_AtomKind_Name, name, nameLength);
  for (TypeNode* typeNode = g_typeNodes->typeNodes; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      return typeNode;
    }
  }
  fwrite("type `", 1, sizeof("type `") - 1, stderr);
  fwrite(name, 1, nameLength, stderr);
  fwrite("` not found", 1, sizeof("` not found") - 1, stderr);
  fwrite("\n", 1, sizeof("\n") - 1, stderr);
  Arcadia_Process_setStatus(process, Arcadia_Status_TypeNotExists);
  Arcadia_Process_jump(process);
}

Arcadia_AtomValue
Arcadia_Type_getName
  (
    Arcadia_TypeValue type
  )
{
  TypeNode* typeNode = (TypeNode*)type;
  return typeNode->typeName;
}

Arcadia_Type_Operations const*
Arcadia_Type_getOperations
  (
    Arcadia_TypeValue type
  )
{
  TypeNode* typeNode = (TypeNode*)type;
  return typeNode->typeOperations;
}

static TypeNode* g_typeType = NULL;

static void
typeTypeDestructing
  (
    void* context
  )
{
  g_typeType = NULL;
}

Arcadia_TypeValue
_Arcadia_Type_getType
  (
    Arcadia_Process* process
  )
{
  if (!g_typeType) {
    g_typeType = R_registerInternalType(process, u8"R.Internal.Type", sizeof(u8"R.Internal.Type") - 1, NULL, &typeTypeDestructing);
  }
  return g_typeType;
}

static TypeNode* g_atomType = NULL;

static void
atomTypeDestructing
  (
    void* context
  )
{
  g_atomType = NULL;
}

Arcadia_TypeValue
_R_Atom_getType
  (
    Arcadia_Process* process
  )
{ 
  if (!g_atomType) {
    g_atomType = R_registerInternalType(process, u8"R.Internal.Atom", sizeof(u8"R.Internal.Atom") - 1, NULL, &atomTypeDestructing);
  }
  return g_atomType;
}

Arcadia_SizeValue
Arcadia_Type_hash
  (
    R_TypeValue self
  )
{ return Arcadia_Atom_getHash(Arcadia_Type_getName(self)); }
