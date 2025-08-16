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
#include "Arcadia/Ring1/Implementation/Types.private.h"

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/Names.h"
#include "Arcadia/Ring1/Implementation/Atoms.private.h" ///< @todo A better solution is required for this.
#include <assert.h>
#include <stdio.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define TypeNodeName "Arcadia.Internal.TypeNode"

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


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static uint32_t g_referenceCount = 0;
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
  Arcadia_Atom_visit(Arcadia_Process_getThread(process), typeNode->typeName);
}

static TypeNodes*
TypeNodes_create
  (
    Arcadia_Process* process
  )
{
  TypeNodes* typeNodes = NULL;
  typeNodes = Arcadia_Memory_allocateUnmanaged(Arcadia_Process_getThread(process), sizeof(TypeNodes));

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    typeNodes->buckets = Arcadia_Memory_allocateUnmanaged(Arcadia_Process_getThread(process), sizeof(TypeNode*) * 8);
    for (size_t i = 0, n = 8; i < n; ++i) {
      typeNodes->buckets[i] = NULL;
    }
    typeNodes->size = 0;
    typeNodes->capacity = 8;
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  } else {
    Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
    Arcadia_Memory_deallocateUnmanaged(Arcadia_Process_getThread(process), typeNodes);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  return typeNodes;
}

static void
TypeNodes_destroy
  (
    Arcadia_Process* process,
    TypeNodes* typeNodes
  )
{
  while (typeNodes->size) {
    for (size_t i = 0, n = typeNodes->capacity; i < n; ++i) {
      // At each iteration, remove the leaves of the type tree.
      TypeNode** previous = &typeNodes->buckets[i];
      TypeNode* current = typeNodes->buckets[i];
      while (current) {
        if (!Arcadia_Type_hasChildren(Arcadia_Process_getThread(process), current)) {
          TypeNode* node = current;
          *previous = current->next;
          current = current->next;
          node->typeDestructing(NULL);
          Arcadia_Process_unlockObject(process, node);
          typeNodes->size--;
        } else {
          previous = &current->next;
          current = current->next;
        }
      }
    }
  }
}

Arcadia_SizeValue
Arcadia_Type_getValueSize
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  )
{ return ((TypeNode const*)self)->valueSize; }

Arcadia_TypeValue
Arcadia_Type_getParentObjectType
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  )
{
  if (!Arcadia_Type_isObjectKind(thread, self)) {
    return Arcadia_BooleanValue_False;
  }
  for (size_t i = 0, n = g_typeNodes->capacity; i < n; ++i) {
    TypeNode* typeNode = g_typeNodes->buckets[i];
    while (typeNode) {
      if (Arcadia_Type_isObjectKind(thread, typeNode)) {
        if (Arcadia_Type_getParentObjectType(thread, typeNode) == (TypeNode const*)self) {
          return Arcadia_BooleanValue_True;
        }
      }
      typeNode = typeNode->next;
    }
  }
  return Arcadia_BooleanValue_False;
}

Arcadia_TypeKind
Arcadia_Type_getKind
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  )
{ return ((TypeNode*)self)->kind; }

Arcadia_TypeValue
Arcadia_registerInternalType
  (
    Arcadia_Thread* thread,
    char const* name,
    size_t nameLength,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(thread, Arcadia_AtomKind_Name, name, nameLength);
  size_t hash = Arcadia_Atom_getHash(thread, typeName);
  assert(NULL != g_typeNodes);
  size_t index = hash % g_typeNodes->capacity;
  for (TypeNode* typeNode = g_typeNodes->buckets[index]; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TypeExists);
      Arcadia_Thread_jump(thread);
    }
  }
  TypeNode* typeNode = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  typeNode->kind = Arcadia_TypeKind_Internal;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  //assert(NULL != typeNode->typeOperations);
  //assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->buckets[index];
  g_typeNodes->buckets[index] = typeNode;
  g_typeNodes->size++;

  Arcadia_Process_lockObject(Arcadia_Thread_getProcess(thread), typeNode);

  return typeNode;
}

Arcadia_TypeValue
Arcadia_registerScalarType
  (
    Arcadia_Thread* thread,
    char const* name,
    size_t nameLength,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(thread, Arcadia_AtomKind_Name, name, nameLength);
  size_t hash = Arcadia_Atom_getHash(thread, typeName);
  size_t index = hash % g_typeNodes->capacity;
  for (TypeNode* typeNode = g_typeNodes->buckets[index]; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TypeExists);
      Arcadia_Thread_jump(thread);
    }
  }
  TypeNode* typeNode = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  typeNode->kind = Arcadia_TypeKind_Scalar;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = NULL;
  typeNode->valueSize = 0;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL == typeNode->typeOperations->objectTypeOperations);

  typeNode->next = g_typeNodes->buckets[index];
  g_typeNodes->buckets[index] = typeNode;
  g_typeNodes->size++;

  Arcadia_Process_lockObject(Arcadia_Thread_getProcess(thread), typeNode);

  return typeNode;
}

Arcadia_TypeValue
Arcadia_registerObjectType
  (
    Arcadia_Thread* thread,
    char const* name,
    size_t nameLength,
    size_t valueSize,
    Arcadia_TypeValue parentObjectType,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(thread, Arcadia_AtomKind_Name, name, nameLength);
  size_t hash = Arcadia_Atom_getHash(thread, typeName);
  size_t index = hash % g_typeNodes->capacity;
  for (TypeNode* typeNode = g_typeNodes->buckets[index]; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TypeExists);
      Arcadia_Thread_jump(thread);
    }
  }
  TypeNode* typeNode = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  typeNode->kind = Arcadia_TypeKind_Object;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->parentObjectType = parentObjectType;
  if (typeNode->parentObjectType) {
    if (Arcadia_Process_lockObject(Arcadia_Thread_getProcess(thread), typeNode->parentObjectType)) { /* @todo: Can raise due to allocation failure or lock count overflow. */
      fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  typeNode->valueSize = valueSize;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);
  assert(NULL != typeNode->typeOperations->objectTypeOperations);
  assert(NULL != typeNode->typeOperations->objectTypeOperations->construct);

  typeNode->next = g_typeNodes->buckets[index];
  g_typeNodes->buckets[index] = typeNode;
  g_typeNodes->size++;

  Arcadia_Process_lockObject(Arcadia_Thread_getProcess(thread), typeNode); /* @todo Can raise due to allocation failure. Can we built-in a guarantee that at least one lock is always available? */

  return typeNode;
}

Arcadia_TypeValue
Arcadia_registerEnumerationType
  (
    Arcadia_Thread* thread,
    char const* name,
    size_t nameLength,
    size_t valueSize,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(thread, Arcadia_AtomKind_Name, name, nameLength);
  size_t hash = Arcadia_Atom_getHash(thread, typeName);
  size_t index = hash % g_typeNodes->capacity;
  for (TypeNode* typeNode = g_typeNodes->buckets[index]; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TypeExists);
      Arcadia_Thread_jump(thread);
    }
  }
  TypeNode* typeNode = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &typeNode, TypeNodeName, sizeof(TypeNodeName) - 1, sizeof(TypeNode));
  typeNode->kind = Arcadia_TypeKind_Enumeration;
  typeNode->typeName = typeName;
  typeNode->typeOperations = typeOperations;
  typeNode->valueSize = valueSize;
  typeNode->typeDestructing = typeDestructing;

  assert(NULL != typeNode->typeOperations);

  typeNode->next = g_typeNodes->buckets[index];
  g_typeNodes->buckets[index] = typeNode;
  g_typeNodes->size++;

  Arcadia_Process_lockObject(Arcadia_Thread_getProcess(thread), typeNode); /* @todo Can raise due to allocation failure. Can we built-in a guarantee that at least one lock is always available? */

  return typeNode;
}

Arcadia_BooleanValue
Arcadia_Type_isSubType
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
    char const* name,
    size_t nameLength
  )
{
  Arcadia_AtomValue typeName = Arcadia_Atoms_getOrCreateAtom(thread, Arcadia_AtomKind_Name, name, nameLength);
  size_t hash = Arcadia_Atom_getHash(thread, typeName);
  size_t index = hash % g_typeNodes->capacity;
  for (TypeNode* typeNode = g_typeNodes->buckets[index]; NULL != typeNode; typeNode = typeNode->next) {
    if (typeNode->typeName == typeName) {
      return typeNode;
    }
  }
  fwrite("type `", 1, sizeof("type `") - 1, stderr);
  fwrite(name, 1, nameLength, stderr);
  fwrite("` not found", 1, sizeof("` not found") - 1, stderr);
  fwrite("\n", 1, sizeof("\n") - 1, stderr);
  Arcadia_Thread_setStatus(thread, Arcadia_Status_TypeNotExists);
  Arcadia_Thread_jump(thread);
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
Arcadia_Type_getHash
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  )
{ return Arcadia_Atom_getHash(thread, Arcadia_Type_getName(self)); }

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
    Arcadia_Thread* thread
  )
{
  if (!g_memoryType) {
    g_memoryType = Arcadia_registerInternalType(thread, u8"Arcadia.Memory", sizeof(u8"Arcadia.Memory") - 1, NULL, &memoryTypeDestructing);
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
    Arcadia_Thread* thread
  )
{
  if (!g_typeType) {
    g_typeType = Arcadia_registerInternalType(thread, u8"Arcadia.Type", sizeof(u8"Arcadia.Type") - 1, NULL, &typeTypeDestructing);
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
_Arcadia_AtomValue_getType
  (
    Arcadia_Thread* thread
  )
{
  if (!g_atomType) {
    g_atomType = Arcadia_registerInternalType(thread, u8"Arcadia.Atom", sizeof(u8"Arcadia.Atom") - 1, NULL, &atomTypeDestructing);
  }
  return g_atomType;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_DefineModule("Arcadia.Types", Arcadia_Types);

static void
_Arcadia_Types_onPreMark
  (
    Arcadia_Thread* thread,
    bool purgeCache
  )
{/*Intentionally empty.*/}

static void
_Arcadia_Types_onFinalize
  (
    Arcadia_Thread* thread,
    size_t* destroyed
  )
{
  *destroyed = 0;
}

static void
startupDependencies
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  Arcadia_Names_getModule(process)->onStartUp(thread);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Atoms_getModule(process)->onStartUp(thread);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Names_getModule(process)->onShutDown(thread);
    Arcadia_Thread_jump(thread);
  }
}

static void
shutdownDependencies
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  Arcadia_Atoms_getModule(process)->onShutDown(thread);
  Arcadia_Names_getModule(process)->onShutDown(thread);
}

static void
_Arcadia_Types_onStartUp
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  if (g_referenceCount == UINT32_MAX) {
    Arcadia_logf(Arcadia_LogFlags_Error, "corrupted reference counter\n");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (g_referenceCount == 0) {
    if (!g_typeNodeRegistered) {
      Arcadia_Process_registerType(process, TypeNodeName, sizeof(TypeNodeName) - 1, process, &TypeNode_typeRemovedCallback, &TypeNode_visitCallback, &TypeNode_finalizeCallback);
      g_typeNodeRegistered = Arcadia_BooleanValue_True;
    }
    startupDependencies(thread);
    g_typeNodes = TypeNodes_create(process);
    if (!g_typeNodes) {
      shutdownDependencies(thread);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_Process_addArmsPreMarkCallback(process, &_Arcadia_Types_onPreMark);
      Arcadia_Process_addArmsVisitCallback(process, &_Arcadia_Types_onVisit);
      Arcadia_Process_addArmsFinalizeCallback(process, &_Arcadia_Types_onFinalize);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
      Arcadia_Process_removeArmsFinalizeCallback(process, &_Arcadia_Types_onFinalize);
      Arcadia_Process_removeArmsVisitCallback(process, &_Arcadia_Types_onVisit);
      Arcadia_Process_removeArmsPreMarkCallback(process, &_Arcadia_Types_onPreMark);
      TypeNodes_destroy(process, g_typeNodes);
      g_typeNodes = NULL;
      Arcadia_Status status = Arcadia_Process_runArms(process, true);
      if (status) {
        /*Intentionally empty.*/
      }
      shutdownDependencies(thread);
      Arcadia_Thread_jump(thread);
    }
  }
  g_referenceCount++;
}

static void
_Arcadia_Types_onShutDown
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  if (g_referenceCount == 0) {
    Arcadia_logf(Arcadia_LogFlags_Error, "corrupted reference counter\n");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  g_referenceCount--;
  if (0 == g_referenceCount) {
    Arcadia_Status status;
    status = Arcadia_Process_runArms(process, true);
    if (status) {
      /* Intentionally empty.*/
    }
    TypeNodes_destroy(process, g_typeNodes);
    g_typeNodes = NULL;
    Arcadia_Process_removeArmsFinalizeCallback(process, &_Arcadia_Types_onFinalize);
    Arcadia_Process_removeArmsVisitCallback(process, &_Arcadia_Types_onVisit);
    Arcadia_Process_removeArmsPreMarkCallback(process, &_Arcadia_Types_onPreMark);
    status = Arcadia_Process_runArms(process, true);
    if (status) {
      /* Intentionally empty.*/
    }
    shutdownDependencies(thread);
  }
}

static void
_Arcadia_Types_onVisit
  (
    Arcadia_Thread* thread
  )
{/*Intentionally empty.*/}
