// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-18

#include "R.h"
#include "R/Mil/Include.h"
#include <stdlib.h>

#include "R/Mil/Tests/SemanticalAnalysis/Enter.h"

static void
_Library_KeyboardKeyMessage_construct
  (
    Arcadia_Process* process,
    R_Value* target,
    Arcadia_SizeValue numberOfArgument,
    R_Value* argumentValues
  )
{ }

static void
_Library_KeyboardKeyMessage_getAction
  (
    Arcadia_Process* process,
    R_Value* target,
    Arcadia_SizeValue numberOfArgument,
    R_Value* argumentValues
  )
{ }

static void
_Library_KeyboardKeyMessage_getKey
  (
    Arcadia_Process* process,
    R_Value* target,
    Arcadia_SizeValue numberOfArgument,
    R_Value* argumentValues
  )
{ }

static void
_Library_print
  (
    Arcadia_Process* process,
    R_Value* target,
    Arcadia_SizeValue numberOfArgument,
    R_Value* argumentValues
  )
{/*Intentionally empty.*/}

static void
_Library_main
  (
    Arcadia_Process* process,
    R_Value* target,
    Arcadia_SizeValue numberOfArgument,
    R_Value* argumentValues
  )
{/*Intentionally empty.*/}

static void
testNativePrintProcedure
  (
    Arcadia_Process* process
  )
{
  R_Map* symbolTable = R_Map_create(process);
  R_Map* foreignProcedures = R_Map_create(process);
#define Define(Name,Function) \
  { \
    R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, Name, sizeof(Name) - 1)) }; \
    R_Value v = { .tag = R_ValueTag_ForeignProcedure, .foreignProcedureValue = &Function }; \
    R_Map_set(process, foreignProcedures, k, v); \
  }
  Define(u8"KeyboardKeyMessage_construct", _Library_KeyboardKeyMessage_construct)
  Define(u8"KeyboardKeyMessage_getAction", _Library_KeyboardKeyMessage_getAction)
  Define(u8"KeyboardKeyMessage_getKey", _Library_KeyboardKeyMessage_getKey)
  Define(u8"print", _Library_print)
  Define(u8"main", _Library_main)
#undef Define

  R_List* paths = R_List_create(process);
  R_List_appendObjectReferenceValue(process, paths, R_FilePath_parseGeneric(process, u8"Assets/MouseButtonMessage.mil", sizeof(u8"Assets/MouseButtonMessage.mil") - 1));
  R_List_appendObjectReferenceValue(process, paths, R_FilePath_parseGeneric(process, u8"Assets/KeyboardKeyMessage.mil", sizeof(u8"Assets/KeyboardKeyMessage.mil") - 1));
  R_List_appendObjectReferenceValue(process, paths, R_FilePath_parseGeneric(process, u8"Assets/print.mil", sizeof(u8"Assets/print.mil") - 1));
  R_List_appendObjectReferenceValue(process, paths, R_FilePath_parseGeneric(process, u8"Assets/main.mil", sizeof(u8"Assets/main.mil") - 1));

  R_Mil_Parser* parser = R_Mil_Parser_create(process);
  R_FileSystem* fileSystem = R_FileSystem_create(process);
  R_Interpreter_ProcessState_startup(process);

  R_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (size_t i = 0, n = R_List_getSize(paths); i < n; ++i) {
      R_FilePath* sourceFilePath = R_List_getObjectReferenceValueAt(process, paths, i);
      R_FilePath* absoluteSourceFilePath = NULL;
      if (R_FilePath_isRelative(sourceFilePath)) {
        absoluteSourceFilePath = R_FileSystem_getWorkingDirectory(process, fileSystem);
        R_FilePath_append(process, absoluteSourceFilePath, sourceFilePath);
      } else {
        absoluteSourceFilePath = sourceFilePath;
      }
      R_ByteBuffer* sourceFileContents = R_FileSystem_getFileContents(process, fileSystem, absoluteSourceFilePath);

      R_Mil_Parser_setInput(process, parser, (R_Utf8Reader*)R_Utf8ByteBufferReader_create(process, sourceFileContents));
      R_Mil_ModuleAst* moduleAst = R_Mil_Parser_run(process, parser);

      R_Interpreter_ProcessState* interpreterProcess = R_Interpreter_ProcessState_get();
      for (Arcadia_SizeValue i = 0, n = R_Mil_ModuleAst_getNumberOfDefinitions(moduleAst); i < n; ++i) {
        R_Mil_DefinitionAst* definitionAst = R_Mil_ModuleAst_getDefinitionAt(process, moduleAst, i);
        if (Arcadia_Type_isSubType(R_Object_getType(definitionAst), _R_Mil_ClassDefinitionAst_getType(process))) {
          onClassDefinition(process, interpreterProcess, symbolTable, foreignProcedures, (R_Mil_ClassDefinitionAst*)definitionAst);
        } else if (Arcadia_Type_isSubType(R_Object_getType(definitionAst), _R_Mil_ProcedureDefinitionAst_getType(process))) {
          onProcedureDefinition(process, interpreterProcess, symbolTable, foreignProcedures, (R_Mil_ProcedureDefinitionAst*)definitionAst);
        } else {
          Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
          Arcadia_Process_jump(process);
        }
      }
    }
    Arcadia_Process_popJumpTarget(process);
  } else {
    Arcadia_Process_popJumpTarget(process);
    R_Interpreter_ProcessState_shutdown(process);
    Arcadia_Process_jump(process);
  }
  R_Interpreter_ProcessState_shutdown(process);
}

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  testNativePrintProcedure(process);
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    R_shutdown();
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  status[0] = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
