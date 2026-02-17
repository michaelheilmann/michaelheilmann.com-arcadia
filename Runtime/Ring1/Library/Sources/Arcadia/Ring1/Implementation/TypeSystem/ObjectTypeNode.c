// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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
#include "Arcadia/Ring1/Implementation/TypeSystem/ObjectTypeNode.h"

#include "Arcadia/Ring1/Implementation/Diagnostics.h"
#include "Arcadia/Ring1/Implementation/Memory.h"
#include "Arcadia/Ring1/Implementation/ThreadExtensions.h"

static bool g_registered = false;

static void
typeRemovedCallback
  (
    Arcadia_Process* context,
    const uint8_t* name,
    size_t nameLength
  );

static void
finalizeCallback
  (
    Arcadia_Process* context,
    ObjectTypeNode* typeNode
  );

static void
visitCallback
  (
    Arcadia_Process* context,
    ObjectTypeNode* typeNode
  );

static void
typeRemovedCallback
  (
    Arcadia_Process* context,
    const uint8_t* name,
    size_t nameLength
  )
{ g_registered = false; }

static void
finalizeCallback
  (
    Arcadia_Process* process,
    ObjectTypeNode* typeNode
  )
{
  if (typeNode->parentObjectType) {
    if (Arcadia_ARMS_unlock(typeNode->parentObjectType)) {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  if (typeNode->dispatch) {
    free(typeNode->dispatch);
    typeNode->dispatch = NULL;
  }
}

static void
visitCallback
  (
    Arcadia_Process* process,
    ObjectTypeNode* typeNode
  )
{
  if (typeNode->parentObjectType) {
    Arcadia_Type_visit(Arcadia_Process_getThread(process), typeNode->parentObjectType);
  }
  Arcadia_Name_visit(Arcadia_Process_getThread(process), ((TypeNode*)typeNode)->name);
}

ObjectTypeNode*
ObjectTypeNode_allocate
  (
    Arcadia_Thread* thread
  )
{
  if (!g_registered) {
    Arcadia_Process_registerType(Arcadia_Thread_getProcess(thread), ObjectTypeNodeName, sizeof(ObjectTypeNodeName) - 1, Arcadia_Thread_getProcess(thread), &typeRemovedCallback, &visitCallback, &finalizeCallback);
    g_registered = Arcadia_BooleanValue_True;
  }
  ObjectTypeNode* node = NULL;
  Arcadia_Process_allocate(Arcadia_Thread_getProcess(thread), &node, ObjectTypeNodeName, sizeof(ObjectTypeNodeName) - 1, sizeof(ObjectTypeNode));
  Arcadia_Memory_fillZero(thread, node, sizeof(ObjectTypeNode));
  return node;
}
