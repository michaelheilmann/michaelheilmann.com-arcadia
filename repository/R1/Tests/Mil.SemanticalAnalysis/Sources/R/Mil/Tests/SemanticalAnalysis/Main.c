// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{ }

static void
_Library_KeyboardKeyMessage_getAction
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{ }

static void
_Library_KeyboardKeyMessage_getKey
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{ }

static void
_Library_print
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{/*Intentionally empty.*/}

static void
_Library_main
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{/*Intentionally empty.*/}

static void
testNativePrintProcedure
  (
  )
{
  R_Map* symbolTable = R_Map_create();
  R_Map* foreignProcedures = R_Map_create();
#define Define(Name,Function) \
  { \
    R_Value k = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = R_String_create_pn(R_ImmutableByteArray_create(Name, sizeof(Name) - 1)) }; \
    R_Value v = { .tag = R_ValueTag_ForeignProcedure, .foreignProcedureValue = &Function }; \
    R_Map_set(foreignProcedures, k, v); \
  }
  Define("KeyboardKeyMessage_construct", _Library_KeyboardKeyMessage_construct)
  Define("KeyboardKeyMessage_getAction", _Library_KeyboardKeyMessage_getAction)
  Define("KeyboardKeyMessage_getKey", _Library_KeyboardKeyMessage_getKey)
  Define("print", _Library_print)
  Define("main", _Library_main)
#undef Define

  R_List* paths = R_List_create();
  R_List_appendObjectReferenceValue(paths, R_FilePath_parseGeneric("Assets/KeyboardKeyMessage.mil", sizeof("Assets/KeyboardKeyMessage.mil") - 1));
  R_List_appendObjectReferenceValue(paths, R_FilePath_parseGeneric("Assets/print.mil", sizeof("Assets/print.mil") - 1));
  R_List_appendObjectReferenceValue(paths, R_FilePath_parseGeneric("Assets/main.mil", sizeof("Assets/main.mil") - 1));

  R_Mil_Parser* parser = R_Mil_Parser_create();
  R_FileSystem* fileSystem = R_FileSystem_create();
  R_Interpreter_ProcessState_startup();

  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    for (size_t i = 0; i < 3; ++i) {
      R_FilePath* sourceFilePath = R_List_getObjectReferenceValueAt(paths, i);
      R_FilePath* absoluteSourceFilePath = NULL;
      if (R_FilePath_isRelative(sourceFilePath)) {
        absoluteSourceFilePath = R_FileSystem_getWorkingDirectory(fileSystem);
        R_FilePath_append(absoluteSourceFilePath, sourceFilePath);
      } else {
        absoluteSourceFilePath = sourceFilePath;
      }
      R_ByteBuffer* sourceFileContents = R_FileSystem_getFileContents(fileSystem, absoluteSourceFilePath);

      R_Mil_Parser_setInput(parser, (R_Utf8Reader*)R_Utf8ByteBufferReader_create(sourceFileContents));
      R_Mil_ModuleAst* moduleAst = R_Mil_Parser_run(parser);

      R_Interpreter_ProcessState* process = R_Interpreter_ProcessState_get();
      for (R_SizeValue i = 0, n = R_Mil_ModuleAst_getNumberOfDefinitions(moduleAst); i < n; ++i) {
        R_Mil_DefinitionAst* definitionAst = R_Mil_ModuleAst_getDefinitionAt(moduleAst, i);
        if (R_Type_isSubType(R_Object_getType(definitionAst), _R_Mil_ClassDefinitionAst_getType())) {
          onClassDefinition(process, symbolTable, foreignProcedures, (R_Mil_ClassDefinitionAst*)definitionAst);
        } else if (R_Type_isSubType(R_Object_getType(definitionAst), _R_Mil_ProcedureDefinitionAst_getType())) {
          onProcedureDefinition(process, symbolTable, foreignProcedures, (R_Mil_ProcedureDefinitionAst*)definitionAst);
        } else {
          R_setStatus(R_Status_ArgumentTypeInvalid);
          R_jump();
        }
      }
    }
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_Interpreter_ProcessState_shutdown();
    R_jump();
  }
  R_Interpreter_ProcessState_shutdown();
}

void
main1
  (
    int argc,
    char** argv
  )
{
  testNativePrintProcedure();
}

int
main
  (
    int argc,
    char** argv
  )
{
  R_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    main1(argc, argv);
    R_popJumpTarget();
  }
  status[0] = R_getStatus();
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
