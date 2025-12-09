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

static void
assertText
  (
    Arcadia_Thread* thread,
    Arcadia_String* v,
    const char* p,
    size_t n
  )
{
  if (Arcadia_String_getNumberOfBytes(thread, v) != n) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
      Arcadia_Thread_jump(thread);
  }
  if (Arcadia_Memory_compare(thread, Arcadia_String_getBytes(thread, v), p, n)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    Arcadia_Thread_jump(thread);
  }
}

static Arcadia_DDL_Node*
parse
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Parser* parser,
    const char *p,
    size_t n
  )
{
  Arcadia_String* input = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, p, n)));
  Arcadia_DDL_Parser_setInput(thread, parser, input);
  return Arcadia_DDL_Parser_run(thread, parser);
}

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_DDL_Parser* parser = Arcadia_DDL_Parser_create(thread);
  Arcadia_DDL_Node* node = NULL;



  node = parse(thread, parser, u8"true", sizeof(u8"true") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Boolean);
  assertText(thread, ((Arcadia_DDL_BooleanNode*)node)->value, u8"true", sizeof(u8"true") - 1);

  node = parse(thread, parser, u8"false", sizeof(u8"false") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Boolean);
  assertText(thread, ((Arcadia_DDL_BooleanNode*)node)->value, u8"false", sizeof(u8"false") - 1);



  node = parse(thread, parser, u8"void", sizeof(u8"void") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Void);
  assertText(thread, ((Arcadia_DDL_VoidNode*)node)->value, u8"void", sizeof(u8"void") - 1);



  node = parse(thread, parser, u8"1", sizeof(u8"1") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Number);
  assertText(thread, ((Arcadia_DDL_NumberNode*)node)->value, u8"1", sizeof(u8"1") - 1);

  node = parse(thread, parser, u8"+1", sizeof(u8"+1") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Number);
  assertText(thread, ((Arcadia_DDL_NumberNode*)node)->value, u8"+1", sizeof(u8"+1") - 1);

  node = parse(thread, parser, u8"-1", sizeof(u8"-1") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Number);
  assertText(thread, ((Arcadia_DDL_NumberNode*)node)->value, u8"-1", sizeof(u8"-1") - 1);

  node = parse(thread, parser, u8"+5012", sizeof(u8"+5012") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Number);
  assertText(thread, ((Arcadia_DDL_NumberNode*)node)->value, u8"+5012", sizeof(u8"+5012") - 1);

  node = parse(thread, parser, u8"-5012", sizeof(u8"-5012") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Number);
  assertText(thread, ((Arcadia_DDL_NumberNode*)node)->value, u8"-5012", sizeof(u8"-5012") - 1);



  node = parse(thread, parser, u8"-1.0e-10", sizeof(u8"-1.0e-10") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Number);
  assertText(thread, ((Arcadia_DDL_NumberNode*)node)->value, u8"-1.0e-10", sizeof(u8"-1.0e-10") - 1);


  // https://www.compart.com/en/unicode/U+1D28
  node = parse(thread, parser, u8"\"\\u1d28\"", sizeof(u8"\"\\u1d28\"") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_String);
  assertText(thread, ((Arcadia_DDL_StringNode*)node)->value, u8"\u1d28", sizeof(u8"\u1d28") - 1);

  node = parse(thread, parser, u8"\"Hello, World!\"", sizeof(u8"\"Hello, World!\"") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_String);
  assertText(thread, ((Arcadia_DDL_StringNode*)node)->value, u8"Hello, World!", sizeof(u8"Hello, World!") - 1);

  node = parse(thread, parser, u8"\"\\n\\r\\t\\v\\0\\\\\"", sizeof(u8"\"\\n\\r\\t\\v\\0\\\\\"") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_String);
  assertText(thread, ((Arcadia_DDL_StringNode*)node)->value, u8"\n\r\t\v\0\\", sizeof(u8"\n\r\t\v\0\\") - 1);



  node = parse(thread, parser, u8"[]", sizeof(u8"[]") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_List);

  node = parse(thread, parser, u8"[ 1 ]", sizeof(u8"[ 1 ]") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_List);

  node = parse(thread, parser, u8"[ 1, ]", sizeof(u8"[ 1, ]") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_List);



  node = parse(thread, parser, u8"{}", sizeof(u8"{}") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Map);

  node = parse(thread, parser, u8"{ x : 1 }", sizeof(u8"{ x : 1 }") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Map);

  node = parse(thread, parser, u8"{ x : 1, }", sizeof(u8"{ x : 1, }") - 1);
  Arcadia_Tests_assertTrue(thread, node->type == Arcadia_DDL_NodeType_Map);
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
