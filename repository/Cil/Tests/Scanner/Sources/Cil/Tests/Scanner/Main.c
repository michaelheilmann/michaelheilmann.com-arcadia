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
#include "Cilc/Keywords.h"
#include "Cilc/StringTable.h"
#include "Cilc/Scanner.h"
#include "Cilc/Parser.h"

static void
expectAndNext
  (
    Cil_Scanner* scanner,
    Cil_TokenType tokenType,
    R_Natural8Value const* tokenText,
    R_SizeValue tokenTextLength
  )
{
  if (tokenType != Cil_Scanner_getTokenType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  if (!R_String_isEqualTo_pn(Cil_Scanner_getTokenText(scanner), tokenText, tokenTextLength)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);
}

static void
testScanner2
  (
  )
{
  static const char* input =
    u8"multiply"
    u8"\n"
    u8"divide"
    u8"\n"
    u8"add"
    u8"\n"
    u8"subtract"
    u8"\n"
    u8"negate"
    u8"\n"
    u8"not"
    u8"\n"
    u8"concatenate"
    u8"\n"
    ;
  Cil_Scanner* scanner = Cil_Scanner_create();
  Cil_Scanner_setInput(scanner, (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn(input, strlen(input))));

  expectAndNext(scanner, Cil_TokenType_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  expectAndNext(scanner, Cil_TokenType_Multiply, u8"multiply", sizeof(u8"multiply") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_Divide, u8"divide", sizeof(u8"divide") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_Add, u8"add", sizeof(u8"add") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_Subtract, u8"subtract", sizeof(u8"subtract") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_Negate, u8"negate", sizeof(u8"negate") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_Not, u8"not", sizeof(u8"not") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_Concatenate, u8"concatenate", sizeof(u8"concatenate") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

static void
testScanner1
  (
  )
{
  static const char* input =
    u8"Name"
    u8"\n"
    u8"17"
    u8"\n"
    u8"17.23"
    u8"\n"
    u8"\"Hello, World!\n\""
    u8"\n"
    u8"="
    u8"\n"
    u8"//\n"
    u8"/**/"
    u8"\n"
    u8":"
    u8"\n"
    u8","
    u8"\n"
    ;
  Cil_Scanner* scanner = Cil_Scanner_create();
  Cil_Scanner_setInput(scanner, (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn(input, strlen(input))));

  expectAndNext(scanner, Cil_TokenType_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  expectAndNext(scanner, Cil_TokenType_Name, u8"Name", sizeof(u8"Name") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_NumberLiteral, u8"17", sizeof(u8"17") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_NumberLiteral, u8"17.23", sizeof(u8"17.23") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_StringLiteral, u8"Hello, World!\n", sizeof(u8"Hello, World!\n") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_EqualsSign, u8"=", sizeof(u8"=") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_SingleLineComment, u8"", sizeof(u8"") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_MultiLineComment, u8"", sizeof(u8"") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_Colon, u8":", sizeof(u8":") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_Comma, u8",", sizeof(u8",") - 1);
  expectAndNext(scanner, Cil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(scanner, Cil_TokenType_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

void
main1
  (
    int argc,
    char** argv
  )
{
  testScanner1();
  testScanner2();
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
    _Cil_Keywords_getType();
    _Cil_Scanner_getType();
    _Cil_StringTable_getType();
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
