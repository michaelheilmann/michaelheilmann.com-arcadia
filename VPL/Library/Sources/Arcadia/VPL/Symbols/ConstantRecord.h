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

#if !defined(ARCADIA_VPL_SYMBOLS_CONSTANTBLOCK_H_INCLUDED)
#define ARCADIA_VPL_SYMBOLS_CONSTANTBLOCK_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Symbols/Constant.h"
#include "Arcadia/VPL/Tree/Include.h"
typedef struct Arcadia_VPL_Symbols_Program Arcadia_VPL_Symbols_Program;

// A constant record. Contains members.
// The "constant block" maps to an "uniform block" in OpenGL which can both be accessed from any stage (e.g., vertex, fragment, etc.).
// An uniform block cannot be modified by the stages.
// 
// ```
// 'constant' 'record' <name>
// '{'
//   <record body>
// '}' ';'
// <record body> : <record member>*
// <record member> : 'member' <name> ':' <type> ';'
// ```
Arcadia_declareObjectType(u8"Arcadia.VPL.Symbols.ConstantRecord", Arcadia_VPL_Symbols_ConstantRecord,
                          u8"Arcadia.VPL.Symbols.Constant");

struct Arcadia_VPL_Symbols_ConstantRecordDispatch {
  Arcadia_VPL_Symbols_ConstantDispatch _parent;
};

struct Arcadia_VPL_Symbols_ConstantRecord {
  Arcadia_VPL_Symbols_Constant _parent;
  Arcadia_String* name;
  Arcadia_VPL_Symbols_Program* program;
  Arcadia_VPL_Tree_Node* node;

  Arcadia_List* fields;
  /// The mapped name.
  /// This is null initially and computed in later stages.
  Arcadia_String* mappedName;
  /// The scope of this constant record.
  /// This is null initially and computed in later stages.
  Arcadia_Languages_Scope* scope;
};

/// @brief Create a constant block.
/// @param thread A pointer to this thread.
/// @param name The name of the constant block.
/// @param progrma The program owning this constant block.
/// @param node The tree node of the definition of this constant record.
Arcadia_VPL_Symbols_ConstantRecord*
Arcadia_VPL_Symbols_ConstantRecord_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_VPL_Symbols_Program* program,
    Arcadia_VPL_Tree_Node* node
  );

/// @brief Get an immutable list of the fields of this constant block.
/// @param thread A pointer to this thread.
/// @param self A pointer to this constant block.
/// @return A pointer to this list.
Arcadia_List*
Arcadia_VPL_Symbols_ConstantRecord_getFields
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_ConstantRecord* self
  );

#endif // ARCADIA_VPL_SYMBOLS_CONSTANTBLOCK_H_INCLUDED
