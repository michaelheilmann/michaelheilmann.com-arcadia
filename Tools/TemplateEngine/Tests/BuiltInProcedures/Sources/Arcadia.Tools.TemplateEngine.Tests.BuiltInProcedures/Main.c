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
dateTimeProceduresTest
  (
    Arcadia_Thread* thread
  )
{

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Context* context = Context_create(thread);

  context->sourceFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"dateTimeProcedures.t"));
  context->targetFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"dateTimeProcedures.txt"));
  context->dependenciesFilePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_createFromCxxString(thread, u8"dateTimeProcedures.txt.dependencies"));
  context->environmentFilePath = NULL;

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->target = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);
  context->temporaryBuffer = Arcadia_ByteArrayBuilder_create(thread);
  context->temporary = (Arcadia_Unicode_Encoder*)Arcadia_Unicode_UTF8Encoder_create(thread);

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
  if (!Arcadia_Tests_safeExecute(&dateTimeProceduresTest)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
