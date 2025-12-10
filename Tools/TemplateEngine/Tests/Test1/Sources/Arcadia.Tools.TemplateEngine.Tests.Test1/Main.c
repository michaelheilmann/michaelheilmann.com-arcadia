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
main1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, u8"HelloWorld.t", strlen(u8"HelloWorld.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, u8"HelloWorld.txt", strlen(u8"HelloWorld.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, u8"HelloWorld.txt.dependencies", strlen(u8"HelloWorld.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteBuffer_create(thread);
  context->target = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context->temporary = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, context->temporaryBuffer);

  Context_onRun(thread, context);

  Arcadia_FileSystem_setFileContents(thread, fileSystem, context->targetFilePath, context->targetBuffer);
}

static void
recursiveInclude1
  (
    Arcadia_Thread* thread
  )
{
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, u8"recursiveInclude1.t", strlen(u8"recursiveInclude1.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, u8"recursiveInclude1.txt", strlen(u8"recursiveInclude1.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, u8"recursiveInclude1.txt.dependencies", strlen(u8"recursiveInclude1.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteBuffer_create(thread);
  context->target = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context->temporary = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, context->temporaryBuffer);

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
recursiveInclude2
  (
    Arcadia_Thread* thread
  )
{
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, u8"recursiveInclude2.t", strlen(u8"recursiveInclude2.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, u8"recursiveInclude2.txt", strlen(u8"recursiveInclude2.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, u8"recursiveInclude2.txt.dependencies", strlen(u8"recursiveInclude2.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteBuffer_create(thread);
  context->target = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context->temporary = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, context->temporaryBuffer);

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
time
  (
    Arcadia_Thread* thread
  )
{

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, u8"time.t", strlen(u8"time.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, u8"time.txt", strlen(u8"time.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, u8"time.txt.dependencies", strlen(u8"time.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteBuffer_create(thread);
  context->target = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context->temporary = (Arcadia_UTF8Writer*)Arcadia_UTF8ByteBufferWriter_create(thread, context->temporaryBuffer);

  Context_onRun(thread, context);

  Arcadia_FileSystem_setFileContents(thread, fileSystem, context->targetFilePath, context->targetBuffer);
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&main1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&recursiveInclude1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&recursiveInclude2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&time)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
