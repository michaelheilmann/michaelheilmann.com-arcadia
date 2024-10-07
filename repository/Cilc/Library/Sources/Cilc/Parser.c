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

#include "Cilc/Parser.h"

#include "Cilc/Scanner.h"
#include "Cilc/Ast.h"

struct Cil_Parser {
  // The index of the Byte in the input stream at which the current symbol starts.
  Cil_Scanner* scanner;
};

static void
Cil_Parser_destruct
  (
    Cil_Parser* self
  );

static void
Cil_Parser_visit
  (
    Cil_Parser* self
  );

static R_BooleanValue
is
  (
    Cil_Parser* self,
    Cil_TokenType type
  );

static void
next
  (
    Cil_Parser* self
  );

static void
Cil_Parser_destruct
  (
    Cil_Parser* self
  )
{/*Intentionally empty.*/}

static void
Cil_Parser_visit
  (
    Cil_Parser* self
  )
{
  R_Object_visit(self->scanner);
}

static R_BooleanValue
is
  (
    Cil_Parser* self,
    Cil_TokenType type
  )
{ return type == Cil_Scanner_getTokenType(self->scanner); }

static void
next
  (
    Cil_Parser* self
  )
{ Cil_Scanner_step(self->scanner); }

void
_Cil_Parser_registerType
  (
  )
{
  R_registerObjectType("Cil.Parser", sizeof("Cil.Parser") - 1, sizeof(Cil_Parser), NULL, NULL, &Cil_Parser_visit, &Cil_Parser_destruct);
}

Cil_Parser*
Cil_Parser_create
  (
  )
{
  Cil_Parser* self = R_allocateObject(R_getObjectType("Cil.Parser", sizeof("Cil.Parser") - 1));
  self->scanner = Cil_Scanner_create();
  return self;
}

typedef struct Cil_Ast Cil_Ast;

static Cil_StatementAst*
onStatement
  (
    Cil_Parser* self
  );

static Cil_Ast*
onProgram
  (
    Cil_Parser* self
  );

static Cil_StatementAst*
onStatement
  (
    Cil_Parser* self
  )
{ return NULL; }

/// program : definition* 
static Cil_Ast*
onProgram
  (
    Cil_Parser* self
  )
{
  Cil_ProgramAst* program = Cil_ProgramAst_create();
  if (!is(self, Cil_TokenType_StartOfInput)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  while (!is(self, Cil_TokenType_EndOfInput)) {
    Cil_StatementAst* statement = onStatement(self);
    //Cil_ProgramAst_append(program, definition);
  }
  next(self);
  if (!is(self, Cil_TokenType_EndOfInput)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  return (Cil_Ast*)program;
}

void
Cil_Parser_run
  (
    Cil_Parser* self
  )
{ 
  Cil_Ast* program = onProgram(self);
}

void
Cil_Parser_setInput
  (
    Cil_Parser* self,
    R_Utf8Reader* input
  )
{
  Cil_Scanner_setInput(self->scanner, input);
}
