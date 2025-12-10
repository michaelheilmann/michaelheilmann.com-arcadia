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

#include "Arcadia/ARMS/Include.h"

typedef struct Sender {
  char* name;
} Sender;

static void
Sender_visit
  (
    void* context,
    Sender* object
  )
{ }

static void
Sender_finalize
  (
    void* context,
    Sender* object
  )
{
  if (object->name) {
    free(object->name);
    object->name = NULL;
  }
}

typedef struct Message {
  char* text;
  Sender* sender;
} Message;

static void
Message_visit
  (
    void* context,
    Message* object
  )
{
  if (object->sender) {
    Arcadia_ARMS_visit(object->sender);
  }
}

static void
Message_finalize
  (
    void* context,
    Message* object
  )
{
  if (object->text) {
    free(object->text);
    object->text = NULL;
  }
  object->sender = NULL; // Not required but good style.
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
  if (Arcadia_ARMS_addType("Sender", strlen("Sender"), NULL, NULL, (Arcadia_ARMS_VisitCallbackFunction*)&Sender_visit, (Arcadia_ARMS_FinalizeCallbackFunction*)&Sender_finalize)) {
    Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
    Arcadia_ARMS_run(&statistics);
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  if (Arcadia_ARMS_addType("Message", strlen("Message"), NULL, NULL, (Arcadia_ARMS_VisitCallbackFunction*) & Message_visit, (Arcadia_ARMS_FinalizeCallbackFunction*) & Message_finalize)) {
    Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
    Arcadia_ARMS_run(&statistics);
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  Sender* sender = NULL;
  if (Arcadia_ARMS_allocate(&sender, "Sender", strlen("Sender"), sizeof(Sender))) {
    Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
    Arcadia_ARMS_run(&statistics);
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  sender->name = NULL;
  Message* message = NULL;
  if (Arcadia_ARMS_allocate(&message, "Message", strlen("Message"), sizeof(Message))) {
    Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
    Arcadia_ARMS_run(&statistics);
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  message->text = NULL;
  message->sender = NULL;
  message->text = strdup("Hello, World!\n");
  if (!message->text) {
    Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
    Arcadia_ARMS_run(&statistics);
    Arcadia_ARMS_shutdown();
    return EXIT_FAILURE;
  }
  message->sender = sender;
  Arcadia_ARMS_lock(message);
  Arcadia_ARMS_RunStatistics statistics = Arcadia_ARMS_RunStatistics_StaticInitializer();
  Arcadia_ARMS_run(&statistics);
  Arcadia_ARMS_unlock(message);
  Arcadia_ARMS_run(&statistics);
  Arcadia_ARMS_shutdown();
  return EXIT_SUCCESS;
}
