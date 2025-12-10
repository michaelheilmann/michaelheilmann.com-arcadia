// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/DDLS/Tests/Reader/Schema1.h"
#include "Arcadia/DDLS/Include.h"

static void
testAcceptChoice1
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"AnyScalar\",\n"
    "  definition : \n"
    "  {\n"
    "    kind : \"Choice\",\n"
    "    choices : [\n"
    "      { kind : \"Boolean\" },\n"
    "      { kind : \"String\" },\n"
    "      { kind : \"Number\" },\n"
    "      { kind : \"Void\" },\n"
    "    ],\n"
    "  },\n"
    "},\n"
    ;
  Arcadia_DDLS_DefaultReader* ddlsReader =
    Arcadia_DDLS_DefaultReader_create
      (
        thread
      );
  Arcadia_DDLS_Node* ddlsNode =
    Arcadia_DDLS_DefaultReader_run
      (
        thread,
        ddlsReader,
        Arcadia_String_createFromCxxString
          (
            thread,
            DDLS
          )
      );
  ddlsNode = NULL;
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Reader_testAccept1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Reader_testAccept2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Reader_testReject1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Reader_testReject2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Reader_testReject3)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Reader_testReject4)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&Arcadia_DDLS_Tests_Reader_testReject5)) {
    return EXIT_FAILURE;
  }
  //
  if (!Arcadia_Tests_safeExecute(&testAcceptChoice1)) {
    return EXIT_FAILURE;
  }
  //
  return EXIT_SUCCESS;
}
