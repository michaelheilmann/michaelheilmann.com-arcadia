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

#include <stdlib.h>
#include <string.h>
#include "Arcadia/Ring2/Include.h"
#include "Arcadia.Tools.TemplateEngine.Library/Context.h"
#include "Arcadia.Tools.TemplateEngine.Library/Environment.h"
#include "Arcadia.Tools.TemplateEngine.Library/FileContext.h"

void
main1
  (
    Arcadia_Thread* thread,
    int argc,
    char** argv
  )
{
  Arcadia_Value sourceValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
                targetValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
                environmentValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
                dependenciesFileValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
                logFileValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);

  Arcadia_List* arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (int argi = 1; argi < argc; ++argi) {
    Arcadia_String* argument = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, argv[argi], strlen(argv[argi])));
    Arcadia_List_insertBackObjectReferenceValue(thread, arguments, (Arcadia_ObjectReferenceValue)argument);
  }

  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)arguments); i < n; ++i) {
    Arcadia_String* argument = (Arcadia_String*)Arcadia_List_getObjectReferenceValueAt(thread, arguments, i);
    Arcadia_Utf8StringReader* r = Arcadia_Utf8StringReader_create(thread, argument);
    Arcadia_String *key = NULL, *value = NULL;
    if (!Arcadia_CommandLine_parseArgument(thread, (Arcadia_Utf8Reader*)r, &key, &value)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (Arcadia_String_isEqualTo_pn(thread, key, u8"source", sizeof(u8"source") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(thread, key);
      }
      Arcadia_Value_setObjectReferenceValue(&sourceValue, value);
    } else if (Arcadia_String_isEqualTo_pn(thread, key, u8"target", sizeof(u8"target") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(thread, key);
      }
      Arcadia_Value_setObjectReferenceValue(&targetValue, value);
    } else if (Arcadia_String_isEqualTo_pn(thread, key, u8"environment", sizeof(u8"environment") - 1)) {
      if (!value) {
        Arcadia_CommandLine_raiseNoValueError(thread, key);
      }
      Arcadia_Value_setObjectReferenceValue(&environmentValue, value);
    } else if (Arcadia_String_isEqualTo_pn(thread, key, u8"dependenciesFile", sizeof(u8"dependenciesFile") - 1)) {
      Arcadia_Value_setObjectReferenceValue(&dependenciesFileValue, value);
    } else if (Arcadia_String_isEqualTo_pn(thread, key, u8"logFile", sizeof(u8"logFile") - 1)) {
      Arcadia_Value_setObjectReferenceValue(&logFileValue, value);
    } else {
      Arcadia_CommandLine_raiseUnknownArgumentError(thread, key, value);
    }
  }

  Context* context = Context_create(thread);

  Arcadia_FilePath* sourceFilePath = Arcadia_FilePath_parseNative(thread, Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &sourceValue, _Arcadia_String_getType(thread)));
  Arcadia_FilePath* targetFilePath = Arcadia_FilePath_parseNative(thread, Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &targetValue, _Arcadia_String_getType(thread)));
  Arcadia_FilePath* environmentFilePath = Arcadia_FilePath_parseNative(thread, Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &environmentValue, _Arcadia_String_getType(thread)));

  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
  Arcadia_String* environmentString = Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(Arcadia_FileSystem_getFileContents(thread, fileSystem, environmentFilePath)));

  context->stack = (Arcadia_Stack*)Arcadia_ArrayStack_create(thread);
  context->targetBuffer = Arcadia_ByteBuffer_create(thread);
  context->target = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, context->targetBuffer);
  context->temporaryBuffer = Arcadia_ByteBuffer_create(thread);
  context->temporary = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, context->temporaryBuffer);

  Environment* environment = Environment_loadString(thread, environmentString);
  environment->enclosing = context->environment;
  context->environment = environment;

  Arcadia_Stack_pushObjectReferenceValue(thread, context->stack, (Arcadia_Object*)sourceFilePath);
  Context_onRun(thread, context);

  Arcadia_FileSystem_setFileContents(thread, fileSystem, targetFilePath, context->targetBuffer);
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(thread, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(thread);
  Arcadia_Status status = Arcadia_Thread_getStatus(thread);
  thread = NULL;
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
