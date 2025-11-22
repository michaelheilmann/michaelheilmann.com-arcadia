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
#include "Arcadia/Ring2/Include.h"

static Arcadia_DDL_Node*
doRead
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis,
    Arcadia_DDL_Parser* parser,
    const char* p,
    size_t n
  )
{ 
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_ByteBuffer_append_pn(thread, byteBuffer, p, n);
  Arcadia_Utf8Reader* utf8Reader = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, byteBuffer);
  Arcadia_DDL_Parser_setInput(thread, parser, utf8Reader);
  Arcadia_DDL_Node* node = Arcadia_DDL_Parser_run(thread, parser);
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis_run(thread, semanticalAnalysis, node);
  return node;
}

static void
doWrite
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* unparser,
    Arcadia_DDL_Node* node,
    const char* p,
    size_t n
  )
{
  Arcadia_ByteBuffer* byteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_Utf8Writer* utf8Writer = (Arcadia_Utf8Writer*)Arcadia_Utf8ByteBufferWriter_create(thread, byteBuffer);
  Arcadia_DataDefinitionLanguage_Unparser_run(thread, unparser, node, utf8Writer);
  Arcadia_Tests_assertTrue(thread, Arcadia_ByteBuffer_getNumberOfBytes(thread, byteBuffer) == n);
  Arcadia_Tests_assertTrue(thread, !Arcadia_Memory_compare(thread, Arcadia_ByteBuffer_getBytes(thread, byteBuffer), p, n));
}

static inline void
onTest
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis,
    Arcadia_DDL_Parser* parser,
    Arcadia_DataDefinitionLanguage_Unparser* unparser,
    const char *input,
    const char* output
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDL_Node* node = doRead(thread, semanticalAnalysis, parser, input, strlen(input));
    doWrite(thread, unparser, node, output, strlen(output));
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis = Arcadia_DataDefinitionLanguage_SemanticalAnalysis_create(thread);
  Arcadia_DDL_Parser* parser = Arcadia_DDL_Parser_create(thread);
  Arcadia_DataDefinitionLanguage_Unparser* unparser = Arcadia_DataDefinitionLanguage_Unparser_create(thread);
  onTest(thread, semanticalAnalysis, parser, unparser,
                 u8"{ prename : \"Michael\", surname: \"Heilmann\",\n}\n",
                 u8"{\n  prename : \"Michael\",\n  surname : \"Heilmann\",\n}\n");
  onTest(thread, semanticalAnalysis, parser, unparser,
    u8"{\n  value : {\n  },\n}\n",
    u8"{\n  value : {\n  },\n}\n");
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
