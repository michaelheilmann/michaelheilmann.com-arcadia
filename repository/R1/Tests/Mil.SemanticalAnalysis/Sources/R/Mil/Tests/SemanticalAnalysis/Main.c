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

#include "R/Include.h"
#include "R/Mil/Include.h"
#include <stdlib.h>

#include "R/Mil/Tests/SemanticalAnalysis/Pass.h"
#include "R/Mil/Tests/SemanticalAnalysis/EnterPass.h"

static void
_Library_KeyboardKeyMessage_construct
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{ }

static void
_Library_KeyboardKeyMessage_getAction
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{ }

static void
_Library_KeyboardKeyMessage_getKey
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{ }

static void
_Library_print
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{/*Intentionally empty.*/}

static void
_Library_main
  (
    Arcadia_Process* process,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{/*Intentionally empty.*/}

static void
onPhase1
  (
    Arcadia_Process* process,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ModuleAst* moduleAst
  )
{
  Arcadia_Mil_EnterPass_onModule(process, R_Interpreter_ProcessState_get(), symbolTable, foreignProcedures, moduleAst);
}

static void 
compile
  (
    Arcadia_Process* process,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_List* paths
  )
{
  Arcadia_Mil_Parser* parser = Arcadia_Mil_Parser_create(process);
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(process);
  Arcadia_List* moduleAsts = Arcadia_List_create(process);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, paths); i < n; ++i) {
    Arcadia_FilePath* sourceFilePath = Arcadia_List_getObjectReferenceValueAt(process, paths, i);
    Arcadia_FilePath* absoluteSourceFilePath = NULL;
    if (Arcadia_FilePath_isRelative(sourceFilePath)) {
      absoluteSourceFilePath = Arcadia_FileSystem_getWorkingDirectory(process, fileSystem);
      Arcadia_FilePath_append(process, absoluteSourceFilePath, sourceFilePath);
    } else {
      absoluteSourceFilePath = sourceFilePath;
    }
    Arcadia_ByteBuffer* sourceFileContents = Arcadia_FileSystem_getFileContents(process, fileSystem, absoluteSourceFilePath);

    Arcadia_Mil_Parser_setInput(process, parser, (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(process, sourceFileContents));
    Arcadia_Mil_ModuleAst* moduleAst = Arcadia_Mil_Parser_run(process, parser);
    Arcadia_List_appendObjectReferenceValue(process, moduleAsts, moduleAst);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(process, moduleAsts); i < n; ++i) {
    Arcadia_Mil_ModuleAst* moduleAst = Arcadia_List_getObjectReferenceValueAt(process, moduleAsts, i);
    onPhase1(process, symbolTable, foreignProcedures, moduleAst);
  }
}

static void
testNativePrintProcedure
  (
    Arcadia_Process* process
  )
{
  Arcadia_Map* symbolTable = Arcadia_Map_create(process);
  Arcadia_Map* foreignProcedures = Arcadia_Map_create(process);
#define Define(Name,Function) \
  { \
    Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = Arcadia_String_create_pn(process, Arcadia_ImmutableByteArray_create(Arcadia_Process_getProcess1(process), Name, sizeof(Name) - 1)) }; \
    Arcadia_Value v = { .tag = Arcadia_ValueTag_ForeignProcedure, .foreignProcedureValue = &Function }; \
    Arcadia_Map_set(process, foreignProcedures, k, v); \
  }
  Define(u8"KeyboardKeyMessage_construct", _Library_KeyboardKeyMessage_construct)
  Define(u8"KeyboardKeyMessage_getAction", _Library_KeyboardKeyMessage_getAction)
  Define(u8"KeyboardKeyMessage_getKey", _Library_KeyboardKeyMessage_getKey)
  Define(u8"print", _Library_print)
  Define(u8"main", _Library_main)
#undef Define

  Arcadia_List* paths = Arcadia_List_create(process);
  Arcadia_List_appendObjectReferenceValue(process, paths, Arcadia_FilePath_parseGeneric(process, u8"Assets/MouseButtonMessage.mil", sizeof(u8"Assets/MouseButtonMessage.mil") - 1));
  Arcadia_List_appendObjectReferenceValue(process, paths, Arcadia_FilePath_parseGeneric(process, u8"Assets/KeyboardKeyMessage.mil", sizeof(u8"Assets/KeyboardKeyMessage.mil") - 1));
  Arcadia_List_appendObjectReferenceValue(process, paths, Arcadia_FilePath_parseGeneric(process, u8"Assets/print.mil", sizeof(u8"Assets/print.mil") - 1));
  Arcadia_List_appendObjectReferenceValue(process, paths, Arcadia_FilePath_parseGeneric(process, u8"Assets/main.mil", sizeof(u8"Assets/main.mil") - 1));
  Arcadia_List_appendObjectReferenceValue(process, paths, Arcadia_FilePath_parseGeneric(process, u8"Assets/fibonacci.mil", sizeof(u8"Assets/fibonacci.mil") - 1));

  R_Interpreter_ProcessState_startup(process);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    compile(process, symbolTable, foreignProcedures, paths);
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
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Process_popJumpTarget(process);
  Arcadia_Status status = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
