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

#if !defined(ARCADIA_MIL_AST_COMPILATIONUNITNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_COMPILATIONUNITNODE_H_INCLUDED

#include "Arcadia/MIL/AST/Node.h"
typedef struct Arcadia_MIL_AST_DefinitionNode Arcadia_MIL_AST_DefinitionNode;

/// @code
/// class Arcadia.MIL.AST.CompilationUnitNode extends Arcadia.MIL.AST.Node
/// @endcode
/// @brief A compilation unit is a single `.mil` file.
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.CompilationUnitNode", Arcadia_MIL_AST_CompilationUnitNode,
                          u8"Arcadia.MIL.AST.Node");

struct Arcadia_MIL_AST_CompilationUnitNodeDispatch {
  Arcadia_MIL_AST_NodeDispatch _parent;
};

struct Arcadia_MIL_AST_CompilationUnitNode {
  Arcadia_MIL_AST_Node _parent;
  /// The file path of the compilation unit (e.g., `Module.mil` or `Source/MyClass.mil`).
  Arcadia_FilePath* filePath;
  /// The definitions in this compilation unit.
  Arcadia_List* definitions;
};

Arcadia_MIL_AST_CompilationUnitNode*
Arcadia_MIL_AST_CompilationUnitNode_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_MIL_AST_CompilationUnitNode_appendDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_CompilationUnitNode* self,
    Arcadia_MIL_AST_DefinitionNode* definition
  );

Arcadia_SizeValue
Arcadia_MIL_AST_CompilationUnitNode_getNumberOfDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_CompilationUnitNode* self
  );

Arcadia_MIL_AST_DefinitionNode*
Arcadia_MIL_AST_CompilationUnitNode_getDefinitionAt
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_CompilationUnitNode* self,
    Arcadia_SizeValue index
  );

#endif // ARCADIA_MIL_AST_COMPILATIONUNITNODE_H_INCLUDED
