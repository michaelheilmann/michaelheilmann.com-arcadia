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

#include "Arcadia/DDLS/Include.h"
#include "Arcadia/DDL/Include.h"

static Arcadia_DDLS_Type*
readDDLS
  (
    Arcadia_Thread* thread,
    const char* source
  )
{
  Arcadia_DDLS_DefaultReader* reader = Arcadia_DDLS_DefaultReader_create(thread);
  Arcadia_DDLS_Type* target = Arcadia_DDLS_DefaultReader_run(thread, reader, (Arcadia_Utf8Reader*)Arcadia_Utf8StringReader_create(thread, Arcadia_String_createFromCxxString(thread, source)));
  return target;
}

static Arcadia_DDL_Node*
readDDL
  (
    Arcadia_Thread* thread,
    const char* source
  )
{
  Arcadia_DDL_DefaultReader* reader = (Arcadia_DDL_DefaultReader*)Arcadia_DDL_DefaultReader_create(thread);
  Arcadia_DDL_Node* target = Arcadia_DDL_DefaultReader_run(thread, reader, (Arcadia_Utf8Reader*)Arcadia_Utf8StringReader_create(thread, Arcadia_String_createFromCxxString(thread, source)));
  return target;
}

static const char* DDLS =
  "{\n"
  "  kind : \"Map\",\n"
  "  entries : [\n"
  "    {\n"
  "      kind : \"MapEntry\",\n"
  "      name : \"type\",\n"
  "      type : {\n"
  "        kind : \"String\",\n"
  "      },\n"
  "    },\n"
  "    {\n"
  "      kind : \"MapEntry\",\n"
  "      name : \"red\",\n"
  "      type : {\n"
  "        kind : \"Number\",\n"
  "      },\n"
  "    },\n"
  "    {\n"
  "      kind : \"MapEntry\",\n"
  "      name : \"green\",\n"
  "      type : {\n"
  "        kind : \"Number\",\n"
  "      },\n"
  "    },\n"
  "    {\n"
  "      kind : \"MapEntry\",\n"
  "      name : \"blue\",\n"
  "      type : {\n"
  "        kind : \"Number\",\n"
  "      },\n"
  "    },\n"
  "  ],\n"
  "},\n"
  ;

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  red : 255,\n"
    "  green : 0,\n"
    "  blue : 0,\n"
    "},\n"
    ;
  Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
  Arcadia_DDL_Node* node = readDDL(thread, DDL);
  Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
  Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
}

// "$.type" not defined
static void
testRejectTypeNotDefined
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  red : 255,\n"
    "  green : 0,\n"
    "  blue : 0,\n"
    "},\n"
    ;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.red" not defined
static void
testRejectRedNotDefined
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  green : 0,\n"
    "  blue : 0,\n"
    "},\n"
    ;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.green" not defined
static void
testRejectGreenNotDefined
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  red : 255,\n"
    "  blue : 0,\n"
    "},\n"
    ;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.blue" not defined
static void
testRejectBlueNotDefined
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  red : 255,\n"
    "  green : 0,\n"
    "},\n"
    ;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.type" is defined twice
static void
testRejectTypeDefinedTwice
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  red : 255,\n"
    "  blue : 0,\n"
    "  green : 0,\n"
    "  type : \"Color\",\n"
    "},\n"
    ;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.red" is defined twice
static void
testRejectRedDefinedTwice
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  red : 255,\n"
    "  blue : 0,\n"
    "  green : 0,\n"
    "  red : 255,\n"
    "},\n"
    ;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.green" is defined twice
static void
testRejectGreenDefinedTwice
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  red : 255,\n"
    "  blue : 0,\n"
    "  green : 0,\n"
    "  green : 0,\n"
    "},\n"
    ;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.blue" is defined twice
static void
testRejectBlueDefinedTwice
  (
    Arcadia_Thread* thread
  )
{
  const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  red : 255,\n"
    "  blue : 0,\n"
    "  green : 0,\n"
    "  blue : 0,\n"
    "},\n"
    ;
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_Type* type = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, type, node);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test1)) {
    return EXIT_FAILURE;
  }

  if (!Arcadia_Tests_safeExecute(&testRejectTypeNotDefined)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testRejectRedNotDefined)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testRejectGreenNotDefined)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testRejectBlueNotDefined)) {
    return EXIT_FAILURE;
  }

  if (!Arcadia_Tests_safeExecute(&testRejectTypeDefinedTwice)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testRejectRedDefinedTwice)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testRejectGreenDefinedTwice)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testRejectBlueDefinedTwice)) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
