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

#include "Arcadia/DDLS/Include.h"

static void
testAccept1
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Map\",\n"
    "  entries : [\n"
    "    {\n"
    "      kind : \"MapEntry\",\n"
    "      name : \"type\",\n"
    "      type : {\n"
    "        kind : \"String\",\n"
    "      },\n"
    "    },\n"
    "    {\n"
    "      kind : \"MapEntry\",\n"
    "      name : \"red\",\n"
    "      type : {\n"
    "        kind : \"Number\",\n"
    "      },\n"
    "    },\n"
    "    {\n"
    "      kind : \"MapEntry\",\n"
    "      name : \"green\",\n"
    "      type : {\n"
    "        kind : \"Number\",\n"
    "      },\n"
    "    },\n"
    "    {\n"
    "      kind : \"MapEntry\",\n"
    "      name : \"blue\",\n" 
    "      type : {\n"
    "        kind : \"Number\",\n"
    "      },\n"
    "    },\n"
    "  ],\n"
    "},\n"
    ;
  Arcadia_DDLS_DefaultReader* ddlsReader =
    Arcadia_DDLS_DefaultReader_create
    (
      thread
    );
  Arcadia_DDLS_Type* ddls =
    Arcadia_DDLS_DefaultReader_run
    (
      thread,
      ddlsReader,
      (Arcadia_Utf8Reader*)
      Arcadia_Utf8StringReader_create
      (
        thread,
        Arcadia_String_createFromCxxString
        (
          thread,
          DDLS
        )
      )
    );
#if 1
  ddls = NULL;
#else
  Arcadia_Value a, b;
  a = Arcadia_Value_makeObjectReferenceValue(ddls->name);
  b = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"Color"));
  Arcadia_Tests_assertTrue(thread, Arcadia_Value_isEqualTo(thread, &a, &b));
  Arcadia_Tests_assertTrue(thread, Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddls, _Arcadia_DDLS_MapType_getType(thread)));
#endif
}

// "$.kind" is missing
static void
testReject1
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  entries : [\n"
    "  ],\n"
    "},\n"
    ;
  Arcadia_DDLS_DefaultReader* ddlsReader =
    Arcadia_DDLS_DefaultReader_create
      (
        thread
      );
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_DefaultReader_run
      (
        thread,
        ddlsReader,
        (Arcadia_Utf8Reader*)
        Arcadia_Utf8StringReader_create
        (
          thread,
          Arcadia_String_createFromCxxString
            (
              thread,
              DDLS
            )
        )
      );
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.entries" is missing
static void
testReject2
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Map\",\n"
    "},\n"
    ;
  Arcadia_DDLS_DefaultReader* ddlsReader =
    Arcadia_DDLS_DefaultReader_create
    (
      thread
    );
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_DefaultReader_run
    (
      thread,
      ddlsReader,
      (Arcadia_Utf8Reader*)
      Arcadia_Utf8StringReader_create
      (
        thread,
        Arcadia_String_createFromCxxString
        (
          thread,
          DDLS
        )
      )
    );
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.entries" is not a list
static void
testReject3
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  type : \"Map\",\n"
    "  entries : \"x\",\n"
    "},\n"
    ;
  Arcadia_DDLS_DefaultReader* ddlsReader =
    Arcadia_DDLS_DefaultReader_create
    (
      thread
    );
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_DefaultReader_run
    (
      thread,
      ddlsReader,
      (Arcadia_Utf8Reader*)
      Arcadia_Utf8StringReader_create
      (
        thread,
        Arcadia_String_createFromCxxString
        (
          thread,
          DDLS
        )
      )
    );
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.kind" specified twice
static void
testReject4
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Map\",\n"
    "  kind : \"Map\",\n"
    "  entries : {\n"
    "  },\n"
    "},\n"
    ;
  Arcadia_DDLS_DefaultReader* ddlsReader =
    Arcadia_DDLS_DefaultReader_create
      (
        thread
      );
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_DefaultReader_run
    (
      thread,
      ddlsReader,
      (Arcadia_Utf8Reader*)
      Arcadia_Utf8StringReader_create
      (
        thread,
        Arcadia_String_createFromCxxString
        (
          thread,
          DDLS
        )
      )
    );
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

// "$.entries[0].name" and "$.entries[1].name" are equal
static void
testReject5
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Map\",\n"
    "  entries : [\n"
    "    {\n"
    "      kind : \"MapEntry\",\n"
    "      name : \"green\",\n"
    "      type : {\n"
    "        kind : \"Number\",\n"
    "      },\n"
    "    },\n"
    "    {\n"
    "      kind : \"MapEntry\",\n"
    "      name : \"green\",\n"
    "      type : {\n"
    "        kind : \"Number\",\n"
    "      },\n"
    "    },\n"
    "  ],\n"
    "},\n"
    ;
  Arcadia_DDLS_DefaultReader* ddlsReader =
    Arcadia_DDLS_DefaultReader_create
    (
      thread
    );
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DDLS_DefaultReader_run
    (
      thread,
      ddlsReader,
      (Arcadia_Utf8Reader*)
      Arcadia_Utf8StringReader_create
      (
        thread,
        Arcadia_String_createFromCxxString
        (
          thread,
          DDLS
        )
      )
    );
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    if (Arcadia_Thread_getStatus(thread) != Arcadia_Status_SemanticalError) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_TestFailed);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_Success);
    }
  }
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&testAccept1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testReject1)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testReject2)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testReject3)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testReject4)) {
    return EXIT_FAILURE;
  }
  if (!Arcadia_Tests_safeExecute(&testReject5)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
