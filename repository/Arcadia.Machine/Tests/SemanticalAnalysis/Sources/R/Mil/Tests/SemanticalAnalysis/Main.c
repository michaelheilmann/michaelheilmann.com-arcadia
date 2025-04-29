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

// Last modified: 2024-10-18

#include "R/Include.h"
#include "R/Mil/Include.h"
#include <stdlib.h>

#include "R/Mil/Tests/SemanticalAnalysis/Pass.h"
#include "R/Mil/Tests/SemanticalAnalysis/EnterPass.h"

static void
_Library_KeyboardKeyMessage_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{ }

static void
_Library_KeyboardKeyMessage_getAction
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{ }

static void
_Library_KeyboardKeyMessage_getKey
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{ }

static void
_Library_print
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArgument,
    Arcadia_Value* argumentValues
  )
{/*Intentionally empty.*/}

static void
_Library_main
  (
    Arcadia_Thread* thread,
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
  Arcadia_Mil_EnterPass_onModule(Arcadia_Process_getThread(process), R_Interpreter_ProcessState_get(), symbolTable, foreignProcedures, moduleAst);
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
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_Mil_Parser* parser = Arcadia_Mil_Parser_create(thread);
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(thread);
  Arcadia_List* moduleAsts = Arcadia_List_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, paths); i < n; ++i) {
    Arcadia_FilePath* sourceFilePath = Arcadia_List_getObjectReferenceValueAt(thread, paths, i);
    Arcadia_FilePath* absoluteSourceFilePath = NULL;
    if (Arcadia_FilePath_isRelative(thread, sourceFilePath)) {
      absoluteSourceFilePath = Arcadia_FileSystem_getWorkingDirectory(thread, fileSystem);
      Arcadia_FilePath_append(thread, absoluteSourceFilePath, sourceFilePath);
    } else {
      absoluteSourceFilePath = sourceFilePath;
    }
    Arcadia_ByteBuffer* sourceFileContents = Arcadia_FileSystem_getFileContents(thread, fileSystem, absoluteSourceFilePath);

    Arcadia_Mil_Parser_setInput(thread, parser, (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, sourceFileContents));
    Arcadia_Mil_ModuleAst* moduleAst = Arcadia_Mil_Parser_run(thread, parser);
    Arcadia_List_appendObjectReferenceValue(thread, moduleAsts, moduleAst);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, moduleAsts); i < n; ++i) {
    Arcadia_Mil_ModuleAst* moduleAst = Arcadia_List_getObjectReferenceValueAt(thread, moduleAsts, i);
    onPhase1(process, symbolTable, foreignProcedures, moduleAst);
  }
}

static void
testNativePrintProcedure
  (
    Arcadia_Process* process
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_Map* symbolTable = Arcadia_Map_create(thread);
  Arcadia_Map* foreignProcedures = Arcadia_Map_create(thread);
#define Define(Name,Function) \
  { \
    Arcadia_Value k = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, Name, sizeof(Name) - 1)) }; \
    Arcadia_Value v = { .tag = Arcadia_ValueTag_ForeignProcedure, .foreignProcedureValue = &Function }; \
    Arcadia_Map_set(thread, foreignProcedures, k, v); \
  }
  Define(u8"KeyboardKeyMessage_construct", _Library_KeyboardKeyMessage_construct)
  Define(u8"KeyboardKeyMessage_getAction", _Library_KeyboardKeyMessage_getAction)
  Define(u8"KeyboardKeyMessage_getKey", _Library_KeyboardKeyMessage_getKey)
  Define(u8"print", _Library_print)
  Define(u8"main", _Library_main)
#undef Define

  Arcadia_List* paths = Arcadia_List_create(thread);
  Arcadia_List_appendObjectReferenceValue(thread, paths, Arcadia_FilePath_parseGeneric(thread, u8"Assets/MouseButtonMessage.mil", sizeof(u8"Assets/MouseButtonMessage.mil") - 1));
  Arcadia_List_appendObjectReferenceValue(thread, paths, Arcadia_FilePath_parseGeneric(thread, u8"Assets/KeyboardKeyMessage.mil", sizeof(u8"Assets/KeyboardKeyMessage.mil") - 1));
  Arcadia_List_appendObjectReferenceValue(thread, paths, Arcadia_FilePath_parseGeneric(thread, u8"Assets/print.mil", sizeof(u8"Assets/print.mil") - 1));
  Arcadia_List_appendObjectReferenceValue(thread, paths, Arcadia_FilePath_parseGeneric(thread, u8"Assets/main.mil", sizeof(u8"Assets/main.mil") - 1));
  Arcadia_List_appendObjectReferenceValue(thread, paths, Arcadia_FilePath_parseGeneric(thread, u8"Assets/fibonacci.mil", sizeof(u8"Assets/fibonacci.mil") - 1));

  R_Interpreter_ProcessState_startup(process);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    compile(process, symbolTable, foreignProcedures, paths);
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    R_Interpreter_ProcessState_shutdown(process);
    Arcadia_Thread_jump(thread);
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
  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  Arcadia_Status status = Arcadia_Thread_getStatus(Arcadia_Process_getThread(process));
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
