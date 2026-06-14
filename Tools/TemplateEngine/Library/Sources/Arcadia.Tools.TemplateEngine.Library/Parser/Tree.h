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

#if !defined(ARCADIA_TEMPLATEENGINE_PARSER_TREE_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_PARSER_TREE_H_INCLUDED

#include "Arcadia.Tools.TemplateEngine.Library/Parser/TreeType.h"

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.Tree", Directives_Tree,
                          u8"Arcadia.Object");

struct Directives_TreeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Directives_Tree {
  Arcadia_Object _parent;

  /// The the type of this tree.
  Arcadia_TemplateEngine_TreeType type;

  // Arcadia_TemplateEngine_TreeType_File.
  struct {
    Arcadia_List* children;
  } file;

  // Arcadia_TemplateEngine_TreeType_InvokeExpr.
  struct {
    Arcadia_String* target;
    Arcadia_List* arguments;
  } invokeExpr;

  // Arcadia_TemplateEngine_TreeType_NameExpr.
  struct {
    Arcadia_String* name;
  } nameExpr;

  // Arcadia_TemplateEngine_TreeType_StringLiteralExpr.
  struct {
    Arcadia_String* string;
  } stringLiteralExpr;

  // Arcadia_TemplateEngine_TreeType_Text.
  struct {
    Arcadia_String* text;
  } text;

};

Directives_Tree*
Directives_Tree_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value type,
    Arcadia_String* name
  );

Directives_Tree*
Directives_Tree_createAtLiteralExpr
  (
    Arcadia_Thread* thread
  );

Directives_Tree*
Directives_Tree_createFile
  (
    Arcadia_Thread* thread
  );

Directives_Tree*
Directives_Tree_createInvokeExpr
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_List* arguments
  );

Directives_Tree*
Directives_Tree_createNameExpr
  (
    Arcadia_Thread* thread,
    Arcadia_String* name
  );

Directives_Tree*
Directives_Tree_createStringLiteralExpr
  (
    Arcadia_Thread* thread,
    Arcadia_String* string
  );

Directives_Tree*
Directives_Tree_createText
  (
    Arcadia_Thread* thread,
    Arcadia_String* text
  );

#endif // ARCADIA_TEMPLATEENGINE_PARSER_TREE_H_INCLUDED
