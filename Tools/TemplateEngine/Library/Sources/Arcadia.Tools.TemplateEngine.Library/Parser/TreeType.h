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

#if !defined(ARCADIA_TEMPLATEENGINE_PARSER_TREETYPE_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_PARSER_TREETYPE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType(u8"Arcadia.TemplateEngine.TreeType", Arcadia_TemplateEngine_TreeType);

// <file> : (<text> | <directive>)* 
// <directive> : <expr>           
// <expr> : <name expr>
//        | <string literal expr>
//        | <at literal expr>
//        | <invoke expr>
//
// <name expr> : <NAME>
// <string literal expr> : <STRING>
// 
// <invoke expr> : <NAME> <arguments>
// <arguments> : <argument> <arguments>
//             | e
enum Arcadia_TemplateEngine_TreeType {

  // See <name expr>.
  // Action: The value of the variable denoted by <NAME> is written to the output.
  Arcadia_TemplateEngine_TreeType_NameExpr,
    
  // See <string literal expr>.
  // Action: <STRING> is written to the output.
  Arcadia_TemplateEngine_TreeType_StringLiteralExpr,

  // See <at literal expr>.
  // Action: '@' is written to the output.
  Arcadia_TemplateEngine_TreeType_AtLiteralExpr,
  
  // See <invoke expr>.
  // Action: The procedure denoted by <NAME> is invoked with the arguments <arguments> and its result value is written to the output.
  Arcadia_TemplateEngine_TreeType_InvokeExpr,

  // See <text>.
  // Action: The text is written to the output.
  Arcadia_TemplateEngine_TreeType_Text,

  // See <file>.
  // Action: The children are iterated over from left to right and the action for the respective node is executed.
  Arcadia_TemplateEngine_TreeType_File,

};

#endif // ARCADIA_TEMPLATEENGINE_PARSER_TREETYPE_H_INCLUDED
