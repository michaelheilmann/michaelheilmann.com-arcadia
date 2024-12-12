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
#include <string.h>

#include "R/Mil/Tests/SemanticalAnalysis/Enter.h"

static void
_KeyboardKeyMessage_construct
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{ }

static void
_KeyboardKeyMessage_getAction
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{ }

static void
_KeyboardKeyMessage_getKey
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{ }

static void
R_Library_print
  (
    R_Value* target,
    R_SizeValue numberOfArgument,
    R_Value const* argumentValues
  )
{/*Intentionally empty.*/}

static void
R_Library_main
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
  Define("KeyboardKeyMessage_construct", _KeyboardKeyMessage_construct)
  Define("KeyboardKeyMessage_getAction", _KeyboardKeyMessage_getAction)
  Define("KeyboardKeyMessage_getKey", _KeyboardKeyMessage_getKey)
  Define("print", R_Library_print)
  Define("main", R_Library_main)
#undef Define
  static const char* input =
    u8"procedure native \"print\" Print (a)\n"
    u8"\n"
    u8"procedure entry native \"main\" Main()\n"
    u8"\n"
    u8"class KeyboardKeyMessage {\n"
    u8"  constructor native \"KeyboardKeyMessage_construct\" ()\n"
    u8"  method native \"KeyboardKeyMessage_getAction\" getAction()\n"
    u8"  method native \"KeyboardKeyMessage_getKey\" getKey()\n"
    u8"}\n"
    ;
  R_Mil_Parser* parser = R_Mil_Parser_create();
  R_Mil_Parser_setInput(parser, (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn(R_ImmutableByteArray_create(input, strlen(input)))));
  R_Mil_ModuleAst* moduleAst = R_Mil_Parser_run(parser);
  
  R_Interpreter_ProcessState* process = R_Interpreter_ProcessState_create();
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
