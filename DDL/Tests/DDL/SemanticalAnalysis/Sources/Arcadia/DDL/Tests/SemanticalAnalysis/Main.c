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

#include "Arcadia/DDL/Include.h"

#include <string.h>

static Arcadia_DDL_Node*
doSyntacticalAnalysis
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* parser,
    const char *p,
    size_t n
  )
{
  Arcadia_RuntimeByteArray* input = Arcadia_RuntimeByteArray_create(thread, p, n);
  return (Arcadia_DDL_Node*)Arcadia_Value_getObjectReferenceValueChecked(thread, Arcadia_Languages_Parser_run(thread, (Arcadia_Languages_Parser*)parser, input), _Arcadia_DDL_Node_getType(thread));
}

static Arcadia_DDL_Node*
doSemanticalAnalysis
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis,
    Arcadia_DDL_Node* node
  )
{
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis_run(thread, semanticalAnalysis, node);
  return node;
}

static inline void
onTest
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis,
    Arcadia_DDL_Parser* parser,
    const char *text,
    Arcadia_BooleanValue expectedJump,
    Arcadia_Status expectedStatus
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_BooleanValue receivedJump = Arcadia_BooleanValue_False;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDL_Node* node = doSyntacticalAnalysis(thread, parser, text, strlen(text));
    node = doSemanticalAnalysis(thread, semanticalAnalysis, node);
    Arcadia_Thread_popJumpTarget(thread);
    receivedJump = Arcadia_BooleanValue_False;
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    receivedJump = Arcadia_BooleanValue_True;
  }
  Arcadia_Tests_assertTrue(thread, receivedJump == expectedJump);
  Arcadia_Tests_assertTrue(thread, Arcadia_Thread_getStatus(thread) == expectedStatus);
  Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
}

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_DDL_Parser* syntacticalAnalyser = Arcadia_DDL_Parser_create(thread, Arcadia_DDL_Scanner_create(thread, Arcadia_Languages_StringTable_getOrCreate(thread),
                                                                                                                 Arcadia_Languages_Diagnostics_create(thread, (Arcadia_Log*)Arcadia_ConsoleLog_create(thread))));
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis = Arcadia_DataDefinitionLanguage_SemanticalAnalysis_create(thread);
  onTest(thread, semanticalAnalysis, syntacticalAnalyser, u8"{ prename : \"Michael\", surname: \"Heilmann\" }", Arcadia_BooleanValue_False, Arcadia_Status_Success);
  onTest(thread, semanticalAnalysis, syntacticalAnalyser, u8"{ prename : \"Michael\", surname: \"Heilmann\", prename : \"Martin\" }", Arcadia_BooleanValue_True, Arcadia_Status_SemanticalError);
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
  return EXIT_SUCCESS;
}
