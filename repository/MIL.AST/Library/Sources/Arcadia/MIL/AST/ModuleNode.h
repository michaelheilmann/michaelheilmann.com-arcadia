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

#if !defined(ARCADIA_MIL_AST_MODULENODE_H_INCLUDED)
#define ARCADIA_MIL_AST_MODULENODE_H_INCLUDED

#include "Arcadia/MIL/AST/Node.h"
typedef struct Arcadia_MIL_AST_CompilationUnitNode Arcadia_MIL_AST_CompilationUnitNode;

/// @code
/// class Arcadia.MIL.AST.ModuleNode extends Arcadia.MIL.AST.Node
/// @endcode
/// @code
/// module : definition*
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.ModuleNode", Arcadia_MIL_AST_ModuleNode,
                          u8"Arcadia.MIL.AST.Node");

struct Arcadia_MIL_AST_ModuleNodeDispatch {
  Arcadia_MIL_AST_NodeDispatch _parent;
};

struct Arcadia_MIL_AST_ModuleNode {
  Arcadia_MIL_AST_Node _parent;
  /// The  path of the module directory or null.
  Arcadia_FilePath* moduleDirectoryPath;
  /// The compilation units (Arcadia.MIL.AST.CompilationUnit) discovered.
  /// These comprise any `.mil` file in the `Source` directory and its subdirectories and the `Module.mil` file.
  Arcadia_List* compilationUnits;
};

Arcadia_MIL_AST_ModuleNode*
Arcadia_MIL_AST_ModuleNode_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_MIL_AST_ModuleNode_appendCompilationUnit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleNode* self,
    Arcadia_MIL_AST_CompilationUnitNode* compilationUnit
  );

Arcadia_SizeValue
Arcadia_MIL_AST_ModuleNode_getNumberOfCompilationUnits
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleNode* self
  );

Arcadia_MIL_AST_CompilationUnitNode*
Arcadia_MIL_AST_ModuleNode_getCompilationUnitAt
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_ModuleNode* self,
    Arcadia_SizeValue index
  );

#endif // ARCADIA_MIL_AST_MODULENODE_H_INCLUDED
