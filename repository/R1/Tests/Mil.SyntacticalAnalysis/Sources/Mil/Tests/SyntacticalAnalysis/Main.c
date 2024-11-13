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

#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "R/Mil/Parser.h"
#include "R/Mil/Ast.h"

static void
testProcedureDefinitions
  (
  )
{
  static const char* input =
    u8"procedure MyProcedure {\n"
    u8"}\n"
    u8"procedure MyProcedure (a, b) {\n"
    u8"}\n"
    u8"procedure native \"print\" print (a)\n"
    ;
  R_Mil_Parser* parser = R_Mil_Parser_create();
  R_Mil_Parser_setInput(parser, (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn(input, strlen(input))));
  R_Mil_Parser_run(parser);
}

static void
testClassDefinitions
(
) {
  static const char* input =
    u8"class MyClassB extends MyClassA {\n"
    u8"  constructor {\n"
    u8"  }\n"
    u8"  constructor(a,b) {\n"
    u8"  }\n"
    u8"  method MyMethodA {\n"
    u8"  }\n"
    u8"  method MyMethodB(a, b) {\n"
    u8"  }\n"
    u8"}\n"
    ;
  R_Mil_Parser* parser = R_Mil_Parser_create();
  R_Mil_Parser_setInput(parser, (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn(input, strlen(input))));
  R_Mil_Parser_run(parser);
}

static void
testStatements
  (
  )
{
  static const char* input =
    u8"procedure hello {\n"
    u8"a = \"Hello, \"\n"
    u8"b = \"World!\n\"\n"
    u8"c = concatenate a, b\n"
    u8"c = concatenate \"Hello \", b\n"
    u8"c = concatenate a, \"World!\n\"\n"
    u8"\n"
    u8"a = 7\n"
    u8"b = 5\n"
    u8"c = add a, b\n"
    u8"c = add 7, b\n"
    u8"c = add a, 7\n"
    u8"\n"
    u8"a = 7\n"
    u8"b = 5\n"
    u8"c = subtract a, b\n"
    u8"c = subtract 7, b\n"
    u8"c = subtract a, 7\n"
    u8"\n"
    u8"a = 7\n"
    u8"b = 5\n"
    u8"c = multiply a, b\n"
    u8"c = multiply 7, b\n"
    u8"c = multiply a, 7\n"
    u8"\n"
    u8"a = 7\n"
    u8"b = 5\n"
    u8"c = divide a, b\n"
    u8"c = divide 7, b\n"
    u8"c = divide a, 7\n"
    u8"\n"
    u8"a = 7\n"
    u8"c = negate a\n"
    u8"c = negate 7\n"
    u8"c = negate 5\n"
    u8"\n"
    u8"a = true\n"
    u8"b = false\n"
    u8"c = and a, b\n"
    u8"c = and true, b\n"
    u8"c = and b, false\n"
    u8"\n"
    u8"a = true\n"
    u8"b = false\n"
    u8"c = or a, b\n"
    u8"c = or true, b\n"
    u8"c = or b, false\n"
    u8"\n"
    u8"a = true\n"
    u8"c = not a\n"
    u8"c = not true\n"
    u8"c = not false\n"
    u8"\n"
    u8"return c\n"
    u8"}\n"
    ;
  R_Mil_Parser* parser = R_Mil_Parser_create();
  R_Mil_Parser_setInput(parser, (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn(input, strlen(input))));
  R_Mil_Parser_run(parser);
}

void
main1
  (
    int argc,
    char** argv
  )
{
  testProcedureDefinitions();
  testClassDefinitions();
  testStatements();
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
