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

// Last modified: 2024-09-22

#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "Scanner.h"

void
main1
  (
    int argc,
    char** argv
  )
{
  static const char *input = 
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
    ;
  Cil_Scanner* scanner = Cil_Scanner_create();
  Cil_Scanner_setInput(scanner, (R_Utf8Reader*)R_Utf8StringReader_create(R_String_create_pn(input, strlen(input))));

  if (Cil_TokenType_StartOfInput != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);
  
  if (Cil_TokenType_Name != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);
  if (Cil_TokenType_LineTerminator != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);
  
  if (Cil_TokenType_NumberLiteral != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);
  if (Cil_TokenType_LineTerminator != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);

  if (Cil_TokenType_NumberLiteral != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);
  if (Cil_TokenType_LineTerminator != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);

  if (Cil_TokenType_StringLiteral != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);
  if (Cil_TokenType_LineTerminator != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);

  if (Cil_TokenType_Assign != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);
  if (Cil_TokenType_LineTerminator != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  Cil_Scanner_step(scanner);

  if (Cil_TokenType_EndOfInput != Cil_Scanner_getType(scanner)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
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
    _Cil_Scanner_registerType();
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
