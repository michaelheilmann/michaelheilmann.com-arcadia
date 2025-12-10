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

void
Arcadia_DDLS_Tests_Reader_testAccept1
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"Color\",\n"
    "  definition : \n"
    "  {\n"
    "    kind : \"Map\",\n"
    "    entries : [\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"type\",\n"
    "        type : {\n"
    "          kind : \"String\",\n"
    "        },\n"
    "      },\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"red\",\n"
    "        type : {\n"
    "          kind : \"Number\",\n"
    "        },\n"
    "      },\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"green\",\n"
    "        type : {\n"
    "          kind : \"Number\",\n"
    "        },\n"
    "      },\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"blue\",\n"
    "        type : {\n"
    "          kind : \"Number\",\n"
    "        },\n"
    "      },\n"
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

void
Arcadia_DDLS_Tests_Reader_testAccept2
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"Color\",\n"
    "  definition : \n"
    "  {\n"
    "    kind : \"Map\",\n"
    "    entries : [\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"type\",\n"
    "        type : {\n"
    "          kind : \"SchemaReference\",\n"
    "          name : \"Type\",\n"
    "        },\n"
    "      },\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"red\",\n"
    "        type : {\n"
    "          kind : \"SchemaReference\",\n"
    "          name : \"ColorComponent\",\n"
    "        },"
    "      },\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"green\",\n"
    "        type : {\n"
    "          kind : \"SchemaReference\",\n"
    "          name : \"ColorComponent\",\n"
    "        },\n"
    "      },\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"blue\",\n"
    "        type : {\n"
    "          kind : \"SchemaReference\",\n"
    "          name : \"ColorComponent\",\n"
    "        },\n"
    "      },\n"
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

// "$.kind" is missing
void
Arcadia_DDLS_Tests_Reader_testReject1
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"MySchema\",\n"
    "  definition : \n"
    "  {\n"
    "    entries : [\n"
    "    ],\n"
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
          Arcadia_String_createFromCxxString
            (
              thread,
              DDLS
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
void
Arcadia_DDLS_Tests_Reader_testReject2
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"MySchema\",\n"
    "  definition : \n"
    "  {\n"
    "    kind : \"Map\",\n"
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
        Arcadia_String_createFromCxxString
          (
            thread,
            DDLS
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
void
Arcadia_DDLS_Tests_Reader_testReject3
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"MySchema\",\n"
    "  definition : \n"
    "  {\n"
    "    kind : \"Map\",\n"
    "    entries : \"x\",\n"
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
        Arcadia_String_createFromCxxString
          (
            thread,
            DDLS
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
void
Arcadia_DDLS_Tests_Reader_testReject4
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"MySchema\",\n"
    "  definition : \n"
    "  {\n"
    "    kind : \"Map\",\n"
    "    kind : \"Map\",\n"
    "    entries : {\n"
    "    },\n"
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
        Arcadia_String_createFromCxxString
          (
            thread,
            DDLS
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
void
Arcadia_DDLS_Tests_Reader_testReject5
  (
    Arcadia_Thread* thread
  )
{
  const char* DDLS =
    "{\n"
    "  kind : \"Schema\",\n"
    "  name : \"MySchema\",\n"
    "  definition : \n"
    "  {\n"
    "    kind : \"Map\",\n"
    "    entries : [\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"green\",\n"
    "        type : {\n"
    "          kind : \"Number\",\n"
    "        },\n"
    "      },\n"
    "      {\n"
    "        kind : \"MapEntry\",\n"
    "        name : \"green\",\n"
    "        type : {\n"
    "          kind : \"Number\",\n"
    "        },\n"
    "      },\n"
    "    ],\n"
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
        Arcadia_String_createFromCxxString
          (
            thread,
            DDLS
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
