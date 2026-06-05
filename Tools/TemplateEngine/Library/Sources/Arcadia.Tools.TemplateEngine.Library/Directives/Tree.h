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

#if !defined(ARCADIA_TEMPLATEENGINE_DIRECTIVES_TREE_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_DIRECTIVES_TREE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.Directives.Tree", Directives_Tree,
                          u8"Arcadia.Object");

/// <name expr> : <NAME>
#define Directives_TreeKind_NameExpr (1)

/// <string literal expr> : <STRING>
#define Directives_TreeKind_StringLiteralExpr (2)

/// <at literal expr> : '@' '@'
#define Directives_TreeKind_AtLiteralExpr (3)

/// <invoke expr> : <NAME>'(' <arguments> ')'
/// <arguments> : e
///             | <argument>
///             | <argument> <argument rest>
/// <argument rest> : ',' <argument> <arguments>
#define Directives_TreeKind_InvokeExpr (4)

/// <assignment expr> : <NAME> ':=' <expr>
#define Directives_TreeKind_AssignmentExpr (5)

struct Directives_TreeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Directives_Tree {
  Arcadia_Object _parent;

  /// The kind of this tree.
  Arcadia_Natural8Value type;

  struct {
    // Directives_TreeKind_NameExpr: The name of the variable.
    Arcadia_String* name;
  } nameExpr;

  struct {
    // Directives_TreeKind_StringLiteralExpr: The string.
    Arcadia_String* string;
  } stringLiteralExpr;

  struct {
    /// Directives_TreeKind_InvokeExor: The name of the procedure.
    Arcadia_String* target;
    /// Directives_TreeKind_InvokeExpr: List of arguments.
    Arcadia_List* arguments;
  } invokeExpr;

  struct {
    Arcadia_String* target;
    Directives_Tree* source;
  } assignmentExpr;

};

Directives_Tree*
Directives_Tree_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value type,
    Arcadia_String* name
  );

Directives_Tree*
Directives_Tree_createInvokeExpr
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_List* arguments
  );

Directives_Tree*
Directives_Tree_createAtLiteralExpr
  (
    Arcadia_Thread* thread
  );

Directives_Tree*
Directives_Tree_createNameExpr
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

#endif // ARCADIA_TEMPLATEENGINE_DIRECTIVES_TREE_H_INCLUDED
