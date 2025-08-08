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

#if !defined(ARCADIA_TEMPLATEENGINE_AST_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_AST_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Tools/TemplateEngine/Context.h"

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.Ast", Ast,
                          u8"Arcadia.Object");

/// <name>
#define Arcadia_TemplateEngine_AstKind_GetVariable (1)

/// <name>'(' <arguments> ')'
#define Arcadia_TemplateEngine_AstKind_Invoke (2)

struct Ast {
  Arcadia_Object _parent;
  int type;
  /// Arcadia_TemplateEngine_AstKind_GetVariable: The name of the variable
  /// Arcadia_TemplateEngine_AstKind_Invoke: The name of the procedure
  Arcadia_String* name;
  /// Arcadia_TemplateEngine_AstKind_GetVariable: [].
  /// Arcadia_TemplateEngine_AstKind_Invoke: List of arguments.
  Arcadia_List* arguments;
};

Ast*
Ast_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value type,
    Arcadia_String* name
  );

#endif // ARCADIA_TEMPLATEENGINE_AST_H_INCLUDED
