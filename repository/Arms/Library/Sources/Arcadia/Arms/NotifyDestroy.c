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

#include "Arcadia/Arms/NotifyDestroy.h"

#if defined(Arcadia_Arms_Configuration_WithNotifyDestroy) && 1 == Arcadia_Arms_Configuration_WithNotifyDestroy

#include "Arcadia/Arms/Internal/Common.h"

/* singly-linked list node */
typedef struct NotifyDestroyListNode NotifyDestroyListNode;

struct NotifyDestroyListNode {
  NotifyDestroyListNode* next;
  Arms_NotifyDestroyContext* context;
  Arms_NotifyDestroyCallback* callback;
};

/* hash map node */
typedef struct NotifyDestroyMapNode NotifyDestroyMapNode;

struct NotifyDestroyMapNode {
  NotifyDestroyMapNode* next;
  void* object;
  NotifyDestroyListNode* list;
};

typedef struct NotifyDestroyMap NotifyDestroyMap;

struct NotifyDestroyMap {
  NotifyDestroyMapNode** buckets;
  Arcadia_Arms_Size size;
  Arcadia_Arms_Size capacity;
};

static NotifyDestroyMap* g_notifyDestroyMap = NULL;

Arcadia_Arms_Status
Arms_NotifyDestroyModule_startup
  (
  )
{
  g_notifyDestroyMap = malloc(sizeof(NotifyDestroyMap));
  if (!g_notifyDestroyMap) {
    return Arcadia_Arms_Status_AllocationFailed;
  }
  g_notifyDestroyMap->size = 0;
  g_notifyDestroyMap->capacity = 8;
  g_notifyDestroyMap->buckets = malloc(sizeof(NotifyDestroyMapNode) * g_notifyDestroyMap->capacity);
  if (!g_notifyDestroyMap->buckets) {
    free(g_notifyDestroyMap);
    g_notifyDestroyMap = NULL;
    return Arcadia_Arms_Status_AllocationFailed;
  }
  for (size_t i = 0, n = g_notifyDestroyMap->capacity; i < n; ++i) {
    g_notifyDestroyMap->buckets[i] = NULL;
  }
  return Arcadia_Arms_Status_Success;
}

Arcadia_Arms_Status
Arms_NotifyDestroyModule_shutdown
  (
  )
{
  if (g_notifyDestroyMap) {
    free(g_notifyDestroyMap);
    g_notifyDestroyMap = NULL;
  }
  return Arcadia_Arms_Status_Success;
}

void
Arms_NotifyDestroyModule_notifyDestroy
  (
    void* object
  )
{
  size_t hashValue = (size_t)(uintptr_t)object;
  size_t hashIndex = hashValue % g_notifyDestroyMap->capacity;
  NotifyDestroyMapNode** previous = &g_notifyDestroyMap->buckets[hashIndex];
  NotifyDestroyMapNode* current = g_notifyDestroyMap->buckets[hashIndex];
  while (current) {
    if (current->object == object) {
      NotifyDestroyMapNode* node = current;
      *previous = current->next;
      current = current->next;
      while (node->list) {
        NotifyDestroyListNode* listNode = node->list;
        node->list = node->list->next;
        listNode->callback(listNode->context, object);
        free(listNode);
      }
      free(node);
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

Arcadia_Arms_Status
Arms_addNotifyDestroy
  (
    void* object,
    Arms_NotifyDestroyContext* context,
    Arms_NotifyDestroyCallback* callback
  )
{
  size_t hashValue = (size_t)(uintptr_t)object;
  size_t hashIndex = hashValue % g_notifyDestroyMap->capacity;
  NotifyDestroyMapNode *node = NULL;
  for (node = g_notifyDestroyMap->buckets[hashIndex]; NULL != node; node = node->next) {
    if (node->object == object) {
      break;
    }
  }
  if (!node) {
    node = malloc(sizeof(NotifyDestroyMapNode));
    if (!node) {
      return Arcadia_Arms_Status_AllocationFailed;
    }
    node->object = object;
    node->list = NULL;
    node->next = g_notifyDestroyMap->buckets[hashIndex];
    g_notifyDestroyMap->buckets[hashIndex] = node;
    g_notifyDestroyMap->size++;
  }
  NotifyDestroyListNode* listNode = malloc(sizeof(NotifyDestroyListNode));
  if (!listNode) {
    return Arcadia_Arms_Status_AllocationFailed;
  }
  listNode->next = node->list;
  node->list = listNode;
  listNode->callback = callback;
  listNode->context = context;
  return Arcadia_Arms_Status_Success;
}

Arcadia_Arms_Status
Arms_removeNotifyDestroy
  (
    void* object,
    Arms_NotifyDestroyContext* notifyDestroyContext,
    Arms_NotifyDestroyCallback* callback
  )
{
  size_t hashValue = (size_t)(uintptr_t)object;
  size_t hashIndex = hashValue % g_notifyDestroyMap->capacity;
  NotifyDestroyMapNode** previous = &g_notifyDestroyMap->buckets[hashIndex];
  NotifyDestroyMapNode* current = g_notifyDestroyMap->buckets[hashIndex];
  while (current) {
    if (current->object == object) {
      NotifyDestroyMapNode* node = current;
      *previous = current->next;
      current = current->next;
      while (node->list) {
        NotifyDestroyListNode* listNode = node->list;
        node->list = node->list->next;
        free(listNode);
      }
      free(node);
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
  return Arcadia_Arms_Status_Success;
}

#endif // Arms_Configuration_WithNotifyDestroy
