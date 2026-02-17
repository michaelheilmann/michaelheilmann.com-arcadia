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

#if !defined(ARCADIA_VISUALS_VPL_CONSTANTBLOCK_H_INCLUDED)
#define ARCADIA_VISUALS_VPL_CONSTANTBLOCK_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

// A constant block. Contains fields.
Arcadia_declareObjectType(u8"Arcadia.Engine.Visuals.VPL.ConstantBlock", Arcadia_Visuals_VPL_ConstantBlock,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_VPL_ConstantBlockDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Visuals_VPL_ConstantBlock {
  Arcadia_Object _parent;
  Arcadia_String* name;
  Arcadia_List* fields;
};

/// @brief Create a constant block.
/// @param thread A pointer to this thread.
/// @param name The name of the constant block.
/// @param fields The fields of the constant block.
/// @error Arcadia_Status_ArgumentTypeInvalid if the list contains a value other than Arcadia_Visuals_VPL_Block*.
Arcadia_Visuals_VPL_ConstantBlock*
Arcadia_Visuals_VPL_ConstantBlock_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_List* fields
  );

/// @brief Get an immutable list of the fields of this constant block.
/// @param thread A pointer to this thread.
/// @param self A pointer to this constant block.
/// @return A pointer to this list.
Arcadia_List*
Arcadia_Visuals_VPL_ConstantBlock_getFields
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_VPL_ConstantBlock* self
  );

#endif // ARCADIA_VISUALS_VPL_CONSTANTBLOCK_H_INCLUDED
