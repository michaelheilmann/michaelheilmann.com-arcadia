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

#include "Arcadia/MIL/Frontend/Include.h"

#include <string.h>

static void
expectAndNext
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scanner* scanner,
    Arcadia_MIL_TokenKind tokenKind,
    Arcadia_Natural8Value const* tokenText,
    Arcadia_SizeValue tokenTextLength
  )
{
  if (tokenKind != Arcadia_MIL_Scanner_getTokenKind(thread, scanner)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  if (!Arcadia_String_isEqualTo_pn(thread, Arcadia_MIL_Scanner_getTokenText(thread, scanner), tokenText, tokenTextLength)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MIL_Scanner_step(thread, scanner);
}

static void
testScanner4
  (
    Arcadia_Thread* thread
  )
{
  static const char* input =
    u8"$0\n"
    u8"$1\n"
    u8"$512\n"
    u8"$_\n"
    ;
  Arcadia_MIL_Scanner* scanner = Arcadia_MIL_Scanner_create(thread);
  Arcadia_MIL_Scanner_setInput(thread, scanner, (Arcadia_UTF8Reader*)Arcadia_UTF8StringReader_create(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, input, strlen(input)))));

  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);

  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Register, u8"$0", sizeof(u8"$0") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);

  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Register, u8"$1", sizeof(u8"$1") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);

  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Register, u8"$512", sizeof(u8"$512") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);

  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Register, u8"$_", sizeof(u8"$_") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);

  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

static void
testScanner3
  (
    Arcadia_Thread* thread
  )
{
  static const char* input =
    //
    u8"multiply"
    u8"\n"
    u8"divide"
    u8"\n"
    u8"add"
    u8"\n"
    u8"subtract"
    u8"\n"
    //
    u8"negate"
    u8"\n"
    //
    u8"concatenate"
    u8"\n"
    //
    u8"isEqualTo"
    u8"\n"
    u8"isNotEqualTo"
    u8"\n"
    u8"isLowerThan"
    u8"\n"
    u8"isLowerThanOrEqualTo"
    u8"\n"
    u8"isGreaterThan"
    u8"\n"
    u8"isGreaterThanOrEqualTo"
    u8"\n"
    //
    u8"not"
    u8"\n"
    u8"and"
    u8"\n"
    u8"or"
    u8"\n"
    //
    u8"class"
    u8"\n"
    u8"extends"
    u8"\n"
    u8"implements"
    u8"\n"
    u8"native"
    u8"\n"
    u8"procedure"
    u8"\n"
    u8"method"
    u8"\n"
    u8"constructor"
    u8"\n"
    u8"variable"
    u8"\n"
    ;
  Arcadia_MIL_Scanner* scanner = Arcadia_MIL_Scanner_create(thread);
  Arcadia_MIL_Scanner_setInput(thread, scanner, (Arcadia_UTF8Reader*)Arcadia_UTF8StringReader_create(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, input, strlen(input)))));

  //
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  //
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Multiply, u8"multiply", sizeof(u8"multiply") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Divide, u8"divide", sizeof(u8"divide") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Add, u8"add", sizeof(u8"add") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Subtract, u8"subtract", sizeof(u8"subtract") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Negate, u8"negate", sizeof(u8"negate") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Concatenate, u8"concatenate", sizeof(u8"concatenate") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_IsEqualTo, u8"isEqualTo", sizeof(u8"isEqualTo") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_IsNotEqualTo, u8"isNotEqualTo", sizeof(u8"isNotEqualTo") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_IsLowerThan, u8"isLowerThan", sizeof(u8"isLowerThan") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_IsLowerThanOrEqualTo, u8"isLowerThanOrEqualTo", sizeof(u8"isLowerThanOrEqualTo") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_IsGreaterThan, u8"isGreaterThan", sizeof(u8"isGreaterThan") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_IsGreaterThanOrEqualTo, u8"isGreaterThanOrEqualTo", sizeof(u8"isGreaterThanOrEqualTo") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Not, u8"not", sizeof(u8"not") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_And, u8"and", sizeof(u8"and") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Or, u8"or", sizeof(u8"or") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Class, u8"class", sizeof(u8"class") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Extends, u8"extends", sizeof(u8"extends") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Implements, u8"implements", sizeof(u8"implements") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Native, u8"native", sizeof(u8"native") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Procedure, u8"procedure", sizeof(u8"procedure") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Method, u8"method", sizeof(u8"method") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Constructor, u8"constructor", sizeof(u8"constructor") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Variable, u8"variable", sizeof(u8"variable") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

static void
testScanner2
  (
    Arcadia_Thread* thread
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
  Arcadia_MIL_Scanner* scanner = Arcadia_MIL_Scanner_create(thread);
  Arcadia_MIL_Scanner_setInput(thread, scanner, (Arcadia_UTF8Reader*)Arcadia_UTF8StringReader_create(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, input, strlen(input)))));

  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Name, u8"Name", sizeof(u8"Name") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_IntegerLiteral, u8"17", sizeof(u8"17") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_RealLiteral, u8"17.23", sizeof(u8"17.23") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_StringLiteral, u8"Hello, World!\n", sizeof(u8"Hello, World!\n") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_EqualsSign, u8"=", sizeof(u8"=") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_SingleLineComment, u8"", sizeof(u8"") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_MultiLineComment, u8"", sizeof(u8"") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Colon, u8":", sizeof(u8":") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_Comma, u8",", sizeof(u8",") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

static void
testScanner1
  (
    Arcadia_Thread* thread
  )
{
  static const char* input =
    u8""
    ;
  Arcadia_MIL_Scanner* scanner = Arcadia_MIL_Scanner_create(thread);
  Arcadia_MIL_Scanner_setInput(thread, scanner, (Arcadia_UTF8Reader*)Arcadia_UTF8StringReader_create(thread, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, input, strlen(input)))));

  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  expectAndNext(thread, scanner, Arcadia_MIL_TokenKind_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&testScanner1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testScanner2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testScanner3)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testScanner4)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
