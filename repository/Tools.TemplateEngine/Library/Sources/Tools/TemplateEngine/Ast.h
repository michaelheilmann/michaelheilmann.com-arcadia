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

// Last modified: 2024-09-09

#if !defined(TOOLS_TEMPLATEENGINE_AST_H_INCLUDED)
#define TOOLS_TEMPLATEENGINE_AST_H_INCLUDED

#include "R/Include.h"
#include "Tools/TemplateEngine/Context.h"

Arcadia_declareObjectType(u8"Tools.TemplateEngine.Ast", Ast, u8"Arcadia.Object");

/// <name>
#define GETVARIABLE (1)

/// <name>'(' <argument> ')'
#define INVOKE (2)

struct Ast {
  Arcadia_Object _parent;
  int type;
  /// GETVARIABLE: The name of the variable
  /// INVOKE: The name of the procedure
  Arcadia_String* name;
  /// GETVARIABLE: NULL.
  /// INVOKE: The value of the argument.
  Arcadia_String* argument;
};

Ast*
Ast_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value type,
    Arcadia_String* name,
    Arcadia_String* argument
  );

#endif // TOOLS_TEMPLATEENGINE_AST_H_INCLUDED
