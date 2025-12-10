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

#include "Arcadia/DDLS/Include.h"
#include "Arcadia/DDL/Include.h"
#include "Arcadia/DDLS/Tests/Validation/Default.h"

static Arcadia_DDLS_SchemaNode*
readDDLS
  (
    Arcadia_Thread* thread,
    const char* source
  )
{
  Arcadia_DDLS_DefaultReader* reader = Arcadia_DDLS_DefaultReader_create(thread);
  Arcadia_DDLS_Node* ddlsNode = Arcadia_DDLS_DefaultReader_run(thread, reader, Arcadia_String_createFromCxxString(thread, source));
  return (Arcadia_DDLS_SchemaNode*)ddlsNode;
}

static Arcadia_DDL_Node*
readDDL
  (
    Arcadia_Thread* thread,
    const char* source
  )
{
  Arcadia_DDL_DefaultReader* reader = (Arcadia_DDL_DefaultReader*)Arcadia_DDL_DefaultReader_create(thread);
  Arcadia_DDL_Node* target = Arcadia_DDL_DefaultReader_run(thread, reader, Arcadia_String_createFromCxxString(thread, source));
  return target;
}

// input are strings, the single choice is string => accept
static void
Arcadia_DDLS_Tests_Validation_choiceAccept1
  (
    Arcadia_Thread* thread
  )
{
  static const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"MySchema\",\n"
    "  definition : \n"
    "  {\n"
    "  kind : \"Choice\",\n"
    "  choices : [\n"
    "      {\n"
    "        kind : \"String\",\n"
    "      },\n"
    "    ],\n"
    "  },\n"
    "},\n"
    ;

  const char* DDL[] =
    {
      "\"w\"",
    };
  for (Arcadia_SizeValue i = 0; i < sizeof(DDL) / sizeof(const char*); ++i) {
    Arcadia_DDLS_SchemaNode* ddlsNode = readDDLS(thread, DDLS);
    Arcadia_DDL_Node* node = readDDL(thread, DDL[i]);
    Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
    Arcadia_DDLS_ValidationContext_addSchema(thread, validationContext, ddlsNode);
    Arcadia_DDLS_ValidationContext_run(thread, validationContext, Arcadia_String_createFromCxxString(thread, u8"MySchema"), node);
  }
}

// input is true, false, void, some numbers, the single choice is string => reject
static void
Arcadia_DDLS_Tests_Validation_choiceReject1
  (
    Arcadia_Thread* thread
  )
{
  static const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"MySchema\",\n"
    "  definition : \n"
    "  {\n"
    "  kind : \"Choice\",\n"
    "  choices : [\n"
    "      {\n"
    "        kind : \"String\",\n"
    "      },\n"
    "    ],\n"
    "  },\n"
    "},\n"
    ;

  const char* DDL[] =
    {
    "true",
    "false",
    "void",
    "1",
    "-1",
    "0.1",
    "-0.1",
    };
  for (Arcadia_SizeValue i = 0; i < sizeof(DDL) / sizeof(const char*); ++i) {
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      Arcadia_DDLS_SchemaNode* ddlsNode = readDDLS(thread, DDLS);
      Arcadia_DDL_Node* node = readDDL(thread, DDL[i]);
      Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
      Arcadia_DDLS_ValidationContext_addSchema(thread, validationContext, ddlsNode);
      Arcadia_DDLS_ValidationContext_run(thread, validationContext, Arcadia_String_createFromCxxString(thread, u8"MySchema"), node);
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
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_test1)) {
    return EXIT_FAILURE;
  }

  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_testRejectTypeNotDefined)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_testRejectRedNotDefined)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_testRejectGreenNotDefined)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_testRejectBlueNotDefined)) {
    return EXIT_FAILURE;
  }

  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_testRejectTypeDefinedTwice)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_testRejectRedDefinedTwice)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_testRejectGreenDefinedTwice)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_testRejectBlueDefinedTwice)) {
    return EXIT_FAILURE;
  }

  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_choiceAccept1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Validation_choiceReject1)) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
