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

#include <stdlib.h>
#include <string.h>

#include "Arcadia/Ring2/Include.h"
#include "Arcadia.Tools.TemplateEngine.Library/Context.h"
#include "Arcadia.Tools.TemplateEngine.Library/DependenciesContext.h"
#include "Arcadia.Tools.TemplateEngine.Library/Environment.h"
#include "Arcadia.Tools.TemplateEngine.Library/FileContext.h"

static void
test_1_1
  (
    Arcadia_Thread* thread
  )
{
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-1/1.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-1/1.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-1/1.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->target = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);
  context->temporaryBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->temporary = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Context_onRun(thread, context);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
  }
}

static void
test_1_2_1
  (
    Arcadia_Thread* thread
  )
{
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-1/1.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-1/1.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-1/1.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->target = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);
  context->temporaryBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->temporary = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Context_onRun(thread, context);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
  }
}

static void
test_1_2_3_1
(
  Arcadia_Thread* thread
) {
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-3-1/1.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-3-1/1.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-3-1/1.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->target = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);
  context->temporaryBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->temporary = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Context_onRun(thread, context);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
  }
}

static void
test_1_2_3_2
  (
    Arcadia_Thread* thread
  )
{
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-3-2/1.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-3-2/1.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"1-2-3-2/1.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->target = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);
  context->temporaryBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->temporary = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Context_onRun(thread, context);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
  }
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test_1_1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test_1_2_1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test_1_2_3_1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&test_1_2_3_2)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
