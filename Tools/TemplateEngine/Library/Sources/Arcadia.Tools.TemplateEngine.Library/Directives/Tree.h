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

/// <name> : <NAME>
#define Directives_TreeKind_GetVariable (1)

/// <string> : <STRING>
#define Directives_TreeKind_String (2)
/// The '@' symbol.
/// <at> : '@' '@'
#define Directives_TreeKind_At (3)

/// <invoke> : <NAME>'(' <arguments> ')'
/// <arguments> : e
///             | <argument>
///             | <argument> <argumentRest>
/// <argumentRest> : ',' <argument> <arguments> 
#define Directives_TreeKind_Invoke (4)

struct Directives_TreeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Directives_Tree {
  Arcadia_Object _parent;

  /// The kind of this tree.
  Arcadia_Natural8Value type;

  struct {
    // Directives_TreeKind_GetVariable: The name of the variable.
    Arcadia_String* name;
  } getVariable;

  // Directives_TreeKind_String: The string.
  Arcadia_String* string;

  struct {
    /// Directives_TreeKind_Invoke: The name of the procedure.
    Arcadia_String* name;
    /// Directives_TreeKind_Invoke: List of arguments.
    Arcadia_List* arguments;
  } invoke;

};

Directives_Tree*
Directives_Tree_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value type,
    Arcadia_String* name
  );

Directives_Tree*
Directives_Tree_createInvoke
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_List* arguments
  );

Directives_Tree*
Directives_Tree_createAt
  (
    Arcadia_Thread* thread
  );

Directives_Tree*
Directives_Tree_createGetVariable
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

#endif // ARCADIA_TEMPLATEENGINE_DIRECTIVES_TREE_H_INCLUDED
