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

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/DDL/Include.h"
#include "Arcadia/DDLS/Include.h"
#include "Arcadia/ADL/Include.h"
#include "Arcadia/ADL/Definitions.h"

static void
testColorDefinition1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_ADL_Definitions* definitions = Arcadia_ADL_Definitions_create(thread);
  static const char *DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  name : \"Color.Red\",\n"
    "  red : 255,\n"
    "  green : 0,\n"
    "  blue : 0,\n"
    "}\n"
    ;
  Arcadia_ADL_ColorDefinition_parse(thread, definitions, Arcadia_String_createFromCxxString(thread, DDL));
}

static void
testColorDefinition2
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_ADL_Definitions* definitions = Arcadia_ADL_Definitions_create(thread);
  static const char* DDL =
    "{\n"
    "  type : \"Color\",\n"
    "  name : \"Color.Green\",\n"
    "  red : 0,\n"
    "  green : 255,\n"
    "  blue : 0,\n"
    "}\n"
    ;
  Arcadia_ADL_ColorDefinition_parse(thread, definitions, Arcadia_String_createFromCxxString(thread, DDL));
}

static void
testPixelBufferOperationDefinition1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_ADL_Definitions* definitions = Arcadia_ADL_Definitions_create(thread);
  {
    static const char* DDL =
      "{\n"
      "  type : \"Color\",\n"
      "  name : \"Color.Green\",\n"
      "  red : 0,\n"
      "  green : 255,\n"
      "  blue : 0,\n"
      "}\n"
      ;
    Arcadia_ADL_ColorDefinition_parse(thread, definitions, Arcadia_String_createFromCxxString(thread, DDL));
  }
  {
    static const char* DDL =
      "{\n"
      "  type  : \"PixelBufferOperations.FillOperation\",\n"
      "  name  : \"PixelBufferOperations.FillGreenOperation\",\n"
      "  color : \"Color.Green\",\n"
      "}\n"
      ;
    Arcadia_ADL_PixelBufferOperations_FillOperationDefinition_parse(thread, definitions, Arcadia_String_createFromCxxString(thread, DDL));
  }
  Arcadia_ADL_Definitions_link(thread, definitions);
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&testColorDefinition1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testColorDefinition2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testPixelBufferOperationDefinition1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
