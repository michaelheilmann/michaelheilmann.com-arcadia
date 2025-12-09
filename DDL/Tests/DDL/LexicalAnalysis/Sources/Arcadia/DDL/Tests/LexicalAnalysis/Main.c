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

#include "Arcadia/DDL/Include.h"

#include <string.h>

static void
expectAndNext
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Scanner* scanner,
    Arcadia_DDL_WordType tokenType,
    Arcadia_Natural8Value const* wordTextBytes,
    Arcadia_SizeValue wordTextNumberOfBytes
  )
{
  if (tokenType != Arcadia_Languages_Scanner_getWordType(thread, (Arcadia_Languages_Scanner*)scanner)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_String* wordText = Arcadia_Languages_Scanner_getWordText(thread, (Arcadia_Languages_Scanner*)scanner);
  if (Arcadia_String_getNumberOfBytes(thread, wordText) != wordTextNumberOfBytes ||
      Arcadia_Memory_compare(thread, Arcadia_String_getBytes(thread, wordText), wordTextBytes, wordTextNumberOfBytes)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Languages_Scanner_step(thread, (Arcadia_Languages_Scanner*)scanner);
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
  Arcadia_DDL_Scanner* scanner = Arcadia_DDL_Scanner_create(thread);
  Arcadia_Languages_Scanner_setInput(thread, (Arcadia_Languages_Scanner*)scanner, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, input, strlen(input))));

  expectAndNext(thread, scanner, Arcadia_DDL_WordType_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

static void
testScanner2
  (
    Arcadia_Thread* thread
  )
{
  static const char* input =
    u8","
    u8":"
    u8"{"
    u8"}"
    u8"["
    u8"]"
    u8"\r "
    u8"\n "
    u8"\r\n"
    u8"\"Hello, World!\\n\" "
    u8"true "
    u8"false "
    u8"void "
    u8"1 "
    u8"6.2831"
    ;
  Arcadia_DDL_Scanner* scanner = Arcadia_DDL_Scanner_create(thread);
  Arcadia_Languages_Scanner_setInput(thread, (Arcadia_Languages_Scanner*)scanner, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, input, strlen(input))));
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_Comma, u8",", sizeof(u8",") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_Colon, u8":", sizeof(u8":") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_LeftCurlyBracket, u8"{", sizeof(u8"{") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_RightCurlyBracket, u8"}", sizeof(u8"}") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_LeftSquareBracket, u8"[", sizeof(u8"[") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_RightSquareBracket, u8"]", sizeof(u8"]") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_LineTerminator, u8"\r", sizeof(u8"\r") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_WhiteSpace, u8" ", sizeof(u8" ") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_LineTerminator, u8"\n", sizeof(u8"\n") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_WhiteSpace, u8" ", sizeof(u8" ") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_LineTerminator, u8"\r\n", sizeof(u8"\r\n") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_StringLiteral, u8"Hello, World!\n", sizeof(u8"Hello, World!\n") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_WhiteSpace, u8" ", sizeof(u8" ") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_BooleanLiteral, u8"true", sizeof(u8"true") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_WhiteSpace, u8" ", sizeof(u8" ") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_BooleanLiteral, u8"false", sizeof(u8"false") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_WhiteSpace, u8" ", sizeof(u8" ") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_VoidLiteral, u8"void", sizeof(u8"void") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_WhiteSpace, u8" ", sizeof(u8" ") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_IntegerLiteral, u8"1", sizeof(u8"1") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_WhiteSpace, u8" ", sizeof(u8" ") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_RealLiteral, u8"6.2831", sizeof(u8"6.2831") - 1);
  expectAndNext(thread, scanner, Arcadia_DDL_WordType_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
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
  return EXIT_SUCCESS;
}
