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

#if !defined(ARCADIA_VPL_SYMBOLS_PROCEDURE_H_INCLUDED)
#define ARCADIA_VPL_SYMBOLS_PROCEDURE_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Symbols/Symbol.h"
#include "Arcadia/VPL/Tree/Include.h"
typedef struct Arcadia_VPL_Symbols_Stage Arcadia_VPL_Symbols_Stage;
typedef struct Arcadia_VPL_Symbols_BuiltinType Arcadia_VPL_Symbols_BuiltinType;

// @brief Marks a built-in procedure.
#define Arcadia_VPL_Symbols_ProcedureFlags_Builtin (1 << 1)

// The procedure is in vertex stage scope.
// Can be combined with fragment stage scope and pixel stage scope.
// Cannot be specified if Arcadia_VPL_Symbols_ProcedureFlags_Builtin is specified.
#define Arcadia_VPL_Symbols_ProcedureFlags_VertexStage (1 << 2)

// The procedure is in fragment stage scope.
// Can be combined with vertex stage scope and pixel stage scope.
// Cannot be specified if Arcadia_VPL_Symbols_ProcedureFlags_Builtin is specified.
#define Arcadia_VPL_Symbols_ProcedureFlags_FragmentStage (1 << 3)

// The procedure is in pixel stage scope.
// Can be combined with vertex stage scope and fragment stage scope.
// Cannot be specified if Arcadia_VPL_Symbols_ProcedureFlags_Builtin is specified.
#define Arcadia_VPL_Symbols_ProcedureFlags_PixelStage (1 << 4)

// A procedure.
Arcadia_declareObjectType(u8"Arcadia.VPL.Symbols.Procedure", Arcadia_VPL_Symbols_Procedure,
                          u8"Arcadia.VPL.Symbols.Symbol");

struct Arcadia_VPL_Symbols_ProcedureDispatch {
  Arcadia_VPL_Symbols_SymbolDispatch _parent;
};

struct Arcadia_VPL_Symbols_Procedure {
  Arcadia_VPL_Symbols_Symbol _parent;
  /// The flags.
  Arcadia_Natural8Value flags;
  Arcadia_String* name;
  Arcadia_VPL_Symbols_Symbol* enclosing;
  Arcadia_VPL_Tree_Node* node;
  // The scope.
  Arcadia_Languages_Scope* scope;
  // List of Arcadia.Symbols.Variable representing the parameter list.
  Arcadia_List* parameters;
  // Arcadia.Symbols.BuiltinType representing the return value type.
  Arcadia_VPL_Symbols_BuiltinType* returnValueType;
};

/// @param flags The flags of this procedure.
/// @param name The name of this procedure.
/// @param enclosing The enclosing symbol. Must be a program symbol or a stage symbol.
/// @param node The tree node of the definition of this procedure.
Arcadia_VPL_Symbols_Procedure*
Arcadia_VPL_Symbols_Procedure_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags,
    Arcadia_String* name,
    Arcadia_VPL_Symbols_Symbol* enclosing,
    Arcadia_VPL_Tree_Node* node
  );

#endif // ARCADIA_VPL_SYMBOLS_PROCEDURE_H_INCLUDED
