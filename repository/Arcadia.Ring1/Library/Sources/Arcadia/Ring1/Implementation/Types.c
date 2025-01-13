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
#include "Arcadia/Ring1/Implementation/Atoms.private.h" ///< @todo A better solution is required for this.
#include <assert.h>
#include <stdio.h>

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
    Arcadia_Process* process,
    TypeNode* typeNode
  )
{
  if (typeNode->parentObjectType) {
    if (Arcadia_Process_unlockObject(process, typeNode->parentObjectType)) {
      fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  typeNode->typeName = NULL;
}

static void
TypeNode_visitCallback
  (
    Arcadia_Process* process,
    TypeNode* typeNode
  )
{
  Arcadia_Atom_visit(process, typeNode->typeName);
}

static TypeNodes*
TypeNodes_create
  (
    Arcadia_Process1* process
  )
{ 
  TypeNodes* typeNode = NULL;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process1_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Process1_allocateUnmanaged(process, &typeNode, sizeof(TypeNodes));
    Arcadia_Process1_popJumpTarget(process);
  } else {
    Arcadia_Process1_popJumpTarget(process);
    return NULL;
  }
  typeNode->typeNodes = NULL;
  return typeNode;
}

static void
TypeNodes_destroy
  (
    Arcadia_Process1* process,
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
      Arcadia_Process1_unlockObject(process, node);
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void
Arcadia_Types_startup
  (
    Arcadia_Process1* process
  )
{
  if (!g_typeNodeRegistered) {
    Arcadia_Process1_registerType(process, TypeNodeName, sizeof(TypeNodeName) - 1, process, &TypeNode_typeRemovedCallback, &TypeNode_visitCallback, &TypeNode_finalizeCallback);
    g_typeNodeRegistered = Arcadia_BooleanValue_True;
  }
  Arcadia_Atoms_startup(process);
  g_typeNodes = TypeNodes_create(process);
  if (!g_typeNodes) {
    Arcadia_Atoms_shutdown(process);
    Arcadia_Process1_jump(process);
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process1_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Process1_popJumpTarget(process);
  } else {
    Arcadia_Process1_popJumpTarget(process);
    TypeNodes_destroy(process, g_typeNodes);
    g_typeNodes = NULL;
    Arcadia_Status status = Arcadia_Process1_runArms(process);
    if (status) {
      /*Intentionally empty.*/
    }
    Arcadia_Atoms_shutdown(process);
    Arcadia_Process1_jump(process);
  }
}

void
Arcadia_Types_shutdown
  (
    Arcadia_Process1* process
  )
{
  Arcadia_Status status;
  status = Arcadia_Process1_runArms(process);
  if (status) {
    /* Intentionally empty.*/
  }
  TypeNodes_destroy(process, g_typeNodes);
  g_typeNodes = NULL;
  
  status = Arcadia_Process1_runArms(process);
  if (status) {
    /* Intentionally empty.*/
  }
  Arcadia_Atoms_shutdown(process);
}

void
Arcadia_Types_onPreMark
  (
    Arcadia_Process1* process,
    Arcadia_BooleanValue purgeCache
  )
{ }

void
Arcadia_Types_onFinalize
  (
    Arcadia_Process1* process
  )
{ }

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

Arcadia_TypeKind
Arcadia_Type_getKind
  (
    Arcadia_TypeValue self
  )
{ return ((TypeNode*)self)->kind; }

Arcadia_TypeValue
Arcadia_registerInternalType
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
  Arcadia_Process_allocate(process, &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  typeNode->kind = Arcadia_TypeKind_Internal;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  //assert(NULL != typeNode->typeOperations);
  //assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  Arcadia_Process_lockObject(process, typeNode);
  
  return typeNode;
}

Arcadia_TypeValue
Arcadia_registerScalarType
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
  Arcadia_Process_allocate(process, &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  typeNode->kind = Arcadia_TypeKind_Scalar;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->typeNodes;
  g_typeNodes->typeNodes = typeNode;

  Arcadia_Process_lockObject(process, typeNode);

  return typeNode;
}

Arcadia_TypeValue
Arcadia_registerObjectType
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
  Arcadia_Process_allocate(process, &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  typeNode->kind = Arcadia_TypeKind_Object;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = parentObjectType;
  if (typeNode->parentObjectType) {
    if (Arcadia_Process_lockObject(process, typeNode->parentObjectType)) { /* @todo: Can raise due to allocation failure or lock count overflow. */
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

  Arcadia_Process_lockObject(process, typeNode); /* @todo Can raise due to allocation failure. Can we built-in a guarantee that at least one lock is always available? */

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
    if (self1->kind == Arcadia_TypeKind_Object) {
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

Arcadia_TypeValue
Arcadia_getType
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

Arcadia_SizeValue
Arcadia_Type_hash
  (
    Arcadia_TypeValue self
  )
{ return Arcadia_Atom_getHash(Arcadia_Type_getName(self)); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static TypeNode* g_memoryType = NULL;

static void
memoryTypeDestructing
  (
    void* context
  )
{ g_memoryType = NULL; }

Arcadia_TypeValue
_Arcadia_Memory_getType
  (
    Arcadia_Process* process
  )
{
  if (!g_memoryType) {
    g_memoryType = Arcadia_registerInternalType(process, u8"Arcadia.Memory", sizeof(u8"Arcadia.Memory") - 1, NULL, &memoryTypeDestructing);
  }
  return g_memoryType;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
    g_typeType = Arcadia_registerInternalType(process, u8"Arcadia.Type", sizeof(u8"Arcadia.Type") - 1, NULL, &typeTypeDestructing);
  }
  return g_typeType;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
    g_atomType = Arcadia_registerInternalType(process, u8"Arcadia.Atom", sizeof(u8"Arcadia.Atom") - 1, NULL, &atomTypeDestructing);
  }
  return g_atomType;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

