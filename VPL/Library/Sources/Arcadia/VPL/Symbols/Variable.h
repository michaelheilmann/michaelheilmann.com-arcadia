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

#if !defined(ARCADIA_VPL_SYMBOLS_VARIABLE_H_INCLUDED)
#define ARCADIA_VPL_SYMBOLS_VARIABLE_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Symbols/Symbol.h"
#include "Arcadia/VPL/Tree/Include.h"
typedef struct Arcadia_VPL_Symbols_Program Arcadia_VPL_Symbols_Program;

/// @brief The representation of variables:
/// - local variables in procedures
/// - fields in constant records
/// - parameters of procedures
Arcadia_declareObjectType(u8"Arcadia.VPL.Symbols.Variable", Arcadia_VPL_Symbols_Variable,
                          u8"Arcadia.VPL.Symbols.Symbol");

struct Arcadia_VPL_Symbols_VariableDispatch {
  Arcadia_VPL_Symbols_SymbolDispatch _parent;
};

struct Arcadia_VPL_Symbols_Variable {
  Arcadia_VPL_Symbols_Symbol _parent;
  /// The enclosing symbol.
  Arcadia_VPL_Symbols_Symbol* enclosing;
  /// The name of the variable.
  Arcadia_String* name;
  /// The type of the variable.
  Arcadia_VPL_Symbols_Symbol* type;
  // The tree node.
  Arcadia_VPL_Tree_Node* node;
};

/// @brief Create a variable scalar.
/// @param thread A pointer to this thread.
/// @param name The name of the variable scalar.
/// @param type The type of the variable scalar.
Arcadia_VPL_Symbols_Variable*
Arcadia_VPL_Symbols_Variable_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_VPL_Symbols_Symbol* type,
    Arcadia_VPL_Symbols_Symbol* enclosing,
    Arcadia_VPL_Tree_Node* node
  );

#endif // ARCADIA_VPL_SYMBOLS_VARIABLE_H_INCLUDED
