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

#include "Arcadia/MIL/Frontend/Include.h"
#include "Arcadia/MIL/Compiler/HelpSystem.h"
#include "Arcadia/DDLS/Include.h"
#include <stdlib.h>

#include "Arcadia/MIL/Compiler/Include.h"
#include "Arcadia/DDL/Include.h"
#include <string.h>

static const char* SCHEMA = 
  "{\n"
  "  kind : \"Schema\",\n"
  "  name : \"Machine Interface Language Compiler Configuration File\",\n"
  "  definition : {\n"
  "    kind : \"Map\",\n"
  "    entries : [\n"
  "      {\n"
  "        kind : \"MapEntry\",\n"
  "        name : \"modulePaths\",\n"
  "        type : {\n"
  "          kind : \"List\",\n"
  "          entry : {\n"
  "            kind :  \"String\",\n"
  "          },\n"
  "        },\n"
  "      },\n"
  "    ],\n"
  "  },\n"
  "}\n"
  ;

/// @error Arcadia_Status_SemanticalError if no entry of the specified name was found
/// @error Arcadia_Status_SemanticalError if an entry of the specified name was found but its value is not a list
static inline Arcadia_DDL_ListNode*
Arcadia_DDL_MapNode_getListByName
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    Arcadia_DDL_MapEntryNode* mapEntryNode =
      (Arcadia_DDL_MapEntryNode*)
      Arcadia_List_getObjectReferenceValueCheckedAt
        (
          thread,
          (Arcadia_List*)mapNode->entries,
          i,
          _Arcadia_DDL_MapEntryNode_getType(thread)
        );
    Arcadia_DDL_NameNode* keyNode = mapEntryNode->key;
    Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(key);
    if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)keyNode->value, &t)) {
      Arcadia_DDL_Node* valueNode = mapEntryNode->value;
      if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)valueNode, _Arcadia_DDL_ListNode_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_DDL_ListNode* listNode = (Arcadia_DDL_ListNode*)valueNode;
      return listNode;
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
  Arcadia_Thread_jump(thread);
}

static void
_invoke
  (
    Arcadia_Thread* thread,
    Arcadia_Log* log,
    Arcadia_List* arguments
  )
{
  // (1) Create the context.
  Arcadia_MIL_Compiler_Context* context = Arcadia_MIL_Compiler_Context_create(thread, log);
  // @todo The logic from this point on should be part of a method of the compiler context.
  Arcadia_String* configurationFilePathString = NULL;
  Arcadia_Value CONFIGURATION = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"configuration"));
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)arguments); i < n; ++i) {
    Arcadia_CommandLineArgument* argument = (Arcadia_CommandLineArgument*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, arguments, i, _Arcadia_CommandLineArgument_getType(thread));
    if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)argument->name, &CONFIGURATION)) {
      if (configurationFilePathString) {
        // @todo These errors must integrate with the log of the context.
        Arcadia_CommandLine_raiseAlreadySpecifiedError(thread, argument->name, context->log);
      }
      if (!argument->value) {
        // @todo These errors must integrate with the log of the context.
        Arcadia_CommandLine_raiseNoValueError(thread, argument->name, context->log);
      }
      configurationFilePathString = argument->value;
    } else {
      // @todo These errors must integrate with the log of the context.
      Arcadia_CommandLine_invalidCommandLineArgumentError(thread, argument->name, context->log);
    }
  }
  if (!configurationFilePathString) {
    // @todo These errors must integrate with the log of the context.
    Arcadia_CommandLine_raiseRequiredArgumentMissingError(thread, Arcadia_String_createFromCxxString(thread, u8"configuration"), context->log);
  }
  // (2) Create the path for the configuration file and the working directory.
  Arcadia_FilePath* configurationFilePath = Arcadia_FilePath_parseGeneric(thread, configurationFilePathString);
  if (!Arcadia_FileSystem_regularFileExists(thread, Arcadia_FileSystem_getOrCreate(thread), configurationFilePath)) {
    Arcadia_Log_error(thread, context->log, Arcadia_String_createFromCxxString(thread, u8"unable to find configuration file `"));
    Arcadia_Log_error(thread, context->log, Arcadia_FilePath_toNative(thread, configurationFilePath));
    Arcadia_Log_error(thread, context->log, Arcadia_String_createFromCxxString(thread, u8"`"));
  } else {
    Arcadia_Log_info(thread, context->log, Arcadia_String_createFromCxxString(thread, u8"configuration file `"));
    Arcadia_Log_info(thread, context->log, Arcadia_FilePath_toNative(thread, configurationFilePath));
    Arcadia_Log_info(thread, context->log, Arcadia_String_createFromCxxString(thread, u8"`\n"));
  }
  Arcadia_FilePath* workingDirectory = Arcadia_FilePath_getParent(thread, configurationFilePath);
  Arcadia_Log_info(thread, context->log, Arcadia_String_createFromCxxString(thread, u8"working directory `"));
  Arcadia_Log_info(thread, context->log, Arcadia_FilePath_toNative(thread, workingDirectory));
  Arcadia_Log_info(thread, context->log, Arcadia_String_createFromCxxString(thread, u8"`\n"));
  // (3) Read the configuration file.
  /* @todo Add Arcadia.DDL.Reader and derive Arcadia.DDL.DefaultReader from it. */
  Arcadia_DDL_DefaultReader* readerDDL = (Arcadia_DDL_DefaultReader*)Arcadia_DDL_DefaultReader_create(thread);
  Arcadia_ByteBuffer* fileBytes = Arcadia_FileSystem_getFileContents(thread, Arcadia_FileSystem_getOrCreate(thread),
                                                                             configurationFilePath);
  Arcadia_String* fileString = Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(fileBytes));
  Arcadia_DDL_Node* nodeDDL = Arcadia_DDL_DefaultReader_run(thread, readerDDL, fileString);
  /* @todo Add Arcadia.DDLS.Reader and derivce Arcadia.DDLS.DefaultReader from it. */
  Arcadia_DDLS_DefaultReader* readerDDLS = (Arcadia_DDLS_DefaultReader*)Arcadia_DDLS_DefaultReader_create(thread);
  Arcadia_DDLS_Node* nodeDDLS = Arcadia_DDLS_DefaultReader_run(thread, readerDDLS, Arcadia_String_createFromCxxString(thread, SCHEMA));
  Arcadia_DDLS_ValidationContext* validationContext = Arcadia_DDLS_ValidationContext_create(thread);
  if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)nodeDDLS, _Arcadia_DDLS_ValidationContext_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_DDLS_ValidationContext_addSchema(thread, validationContext, (Arcadia_DDLS_SchemaNode*)nodeDDLS);
  Arcadia_DDLS_ValidationContext_run(thread, validationContext, Arcadia_String_createFromCxxString(thread, u8"Machine Interface Language Compiler Configuration File"), nodeDDL);
  // (4) Obtain the list of configuration file paths.
  Arcadia_DDL_ListNode* source = Arcadia_DDL_MapNode_getListByName(thread, (Arcadia_DDL_MapNode*)nodeDDL, Arcadia_String_createFromCxxString(thread, u8"modulePaths"));
  Arcadia_List* moduleDirectoryPaths = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_DDL_ListNode_getNumberOfElements(thread, source); i < n; ++i) {
    Arcadia_DDL_StringNode* x = (Arcadia_DDL_StringNode*)Arcadia_DDL_ListNode_getElementAt(thread, source, i);
    /* @todo If the specified string is not a generic path, then we need to handle the resulting exception and emit an appropriate error message. */
    Arcadia_FilePath* y = Arcadia_FilePath_parseNative(thread, x->value);
    Arcadia_List_insertBackObjectReferenceValue(thread, moduleDirectoryPaths, y);
  }
  // (5) Run the compiler.
  Arcadia_MIL_Compiler_Context_run(thread, context, workingDirectory, moduleDirectoryPaths);
}

static void
MIL2C_invoke
  (
    Arcadia_Thread* thread,
    Arcadia_Log* log,
    Arcadia_List* arguments
  )
{
  _invoke(thread, log, arguments);
}

static void
MIL2MIL_invoke
  (
    Arcadia_Thread* thread,
    Arcadia_Log* log,
    Arcadia_List* arguments
  )
{
  _invoke(thread, log, arguments);
}

static void
main1
  (
    Arcadia_Thread* thread,
    int argc,
    char** argv
  )
{
  Arcadia_Log* log = (Arcadia_Log*)Arcadia_ConsoleLog_create(thread);
  // TODO: Add Arcadia.DDL.Reader and derive Arcadia.DDL.DefaultReader from Arcadia.DDL.Reader. 

  // (1) Create the native argument to a list of a list of strings.
  Arcadia_List* arguments = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (int argi = 1; argi < argc; ++argi) {
    Arcadia_String* argumentString = Arcadia_String_createFromCxxString(thread, argv[argi]);
    Arcadia_UTF8Reader* argumentReader = (Arcadia_UTF8Reader*)Arcadia_UTF8StringReader_create(thread, argumentString);
    Arcadia_CommandLineArgument* commandLineArgument = Arcadia_CommandLine_parseArgument(thread, argumentReader);
    if (commandLineArgument->syntacticalError) {
      Arcadia_CommandLine_invalidCommandLineArgumentError(thread, commandLineArgument->name, log);
    }

    Arcadia_List_insertBackObjectReferenceValue(thread, arguments, commandLineArgument);
  }

  // (2) There must be at least one argument `--<tool name>`.
  if (!Arcadia_Collection_getSize(thread, (Arcadia_Collection*)arguments)) {
    /* Invoke help without any arguments. */
    Help_invoke(thread, (Arcadia_List*)Arcadia_ArrayList_create(thread), log);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* toolName  = NULL;
  {
    Arcadia_CommandLineArgument* commandLineArgument = (Arcadia_CommandLineArgument*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, arguments, 0, _Arcadia_CommandLineArgument_getType(thread));
    if (commandLineArgument->syntacticalError) {
      Arcadia_CommandLine_invalidCommandLineArgumentError(thread, commandLineArgument->name, log);
    }
    if (commandLineArgument->value) {
      Arcadia_CommandLine_raiseValueInvalidError(thread, commandLineArgument->name, commandLineArgument->value, log);
    }
    toolName = commandLineArgument->name;
    Arcadia_List_removeFront(thread, arguments, 1);
  }
  if (Arcadia_String_isEqualTo_pn(thread, toolName, u8"mil2c", sizeof(u8"mil2c") - 1)) {
    MIL2C_invoke(thread, log, arguments);
  } else if (Arcadia_String_isEqualTo_pn(thread, toolName, u8"mil2mil", sizeof(u8"mil2mil") - 1)) {
    MIL2MIL_invoke(thread, log, arguments);
  } else if (Arcadia_String_isEqualTo_pn(thread, toolName, u8"help", sizeof(u8"help") - 1)) {
    Help_invoke(thread, arguments, log);
  } else {
    /* Invoke help without any arguments. */
    Help_invoke(thread, (Arcadia_List*)Arcadia_ArrayList_create(thread), log);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Status status;
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
  status = Arcadia_Thread_getStatus(thread);
  thread = NULL;
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
