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

// EXIT_SUCCESS, EXIT_FAILURE
#include <stdlib.h>
// strlen
#include <string.h>
// true, false, bool
#include <stdbool.h>

#include "Arcadia/ARMS/Include.h"

typedef struct Object {
  char* name;
} Object;

static bool g_notifyDestroyCalled = false;
static bool g_visitCalled = false;
static bool g_finalizeCalled = false;

static void
Object_notifyDestroy
  (
    void* context,
    Object* object
  )
{
  g_notifyDestroyCalled = true;
}

static void
Object_visit
  (
    void* context,
    Object* object
  )
{
  g_visitCalled = true;
}

static void
Object_finalize
  (
    void* context,
    Object* object
  )
{
  g_finalizeCalled = true;
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (Arcadia_ARMS_startup()) {
    return EXIT_FAILURE;
  }
  if (Arcadia_ARMS_addType("Object", strlen("Object"), NULL, NULL, (Arcadia_ARMS_VisitCallbackFunction*)&Object_visit, (Arcadia_ARMS_FinalizeCallbackFunction*)&Object_finalize)) {
    Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
    Arcadia_ARMS_run(&statistics);
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  Object* sender = NULL;
  if (Arcadia_ARMS_allocate(&sender, "Object", strlen("Object"), sizeof(Object))) {
    Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
    Arcadia_ARMS_run(&statistics);
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  if (Arcadia_ARMS_addNotifyDestroy(sender, NULL, NULL, (Arcadia_ARMS_NotifyDestroyCallback*)&Object_notifyDestroy)) {
    Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
    Arcadia_ARMS_run(&statistics);
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
  Arcadia_ARMS_run(&statistics);
  Arcadia_ARMS_shutdown();
  if (g_visitCalled || !g_finalizeCalled || !g_notifyDestroyCalled) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
