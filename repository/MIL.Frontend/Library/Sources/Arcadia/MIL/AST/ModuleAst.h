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

#if !defined(ARCADIA_MIL_AST_MODULEAST_H_INCLUDED)
#define ARCADIA_MIL_AST_MODULEAST_H_INCLUDED

#include "Arcadia/MIL/AST/Node.h"
typedef struct Arcadia_MIL_DefinitionAst Arcadia_MIL_DefinitionAst;

/// @code
/// class Arcadia.MIL.ModuleAst extends Arcadia.MIL.Ast
/// @endcode
/// @code
/// module : definition*
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.ModuleAst", Arcadia_MIL_ModuleAst,
                          u8"Arcadia.MIL.AST.Node");

struct Arcadia_MIL_ModuleAst {
  Arcadia_MIL_AST_Node _parent;
  /// The file path of the module or null.
  Arcadia_FilePath* path;
  Arcadia_List* definitions;
};

Arcadia_MIL_ModuleAst*
Arcadia_MIL_ModuleAst_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_MIL_ModuleAst_appendDefinition
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ModuleAst* self,
    Arcadia_MIL_DefinitionAst* definition
  );

Arcadia_SizeValue
Arcadia_MIL_ModuleAst_getNumberOfDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ModuleAst* self
  );

Arcadia_MIL_DefinitionAst*
Arcadia_MIL_ModuleAst_getDefinitionAt
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_ModuleAst* self,
    Arcadia_SizeValue index
  );

#endif // ARCADIA_MIL_AST_MODULEAST_H_INCLUDED
