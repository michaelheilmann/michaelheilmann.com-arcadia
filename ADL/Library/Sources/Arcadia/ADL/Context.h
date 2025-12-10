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

#if !defined(ARCADIA_ADL_CONTEXT_H_INCLUDED)
#define ARCADIA_ADL_CONTEXT_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/DDL/Include.h"
typedef struct Arcadia_ADL_Definition Arcadia_ADL_Definition;
typedef struct Arcadia_ADL_Definitions Arcadia_ADL_Definitions;

/**
 * The ADL context is a singleton providing access to ADL functionality including but not restricted to
 * a) adding/removing readers and writer
 * b) reading/writing definitions
 */
Arcadia_declareObjectType(u8"Arcadia.ADL.Context", Arcadia_ADL_Context,
                          u8"Arcadia.Object");

struct Arcadia_ADL_ContextDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_ADL_Context {
  Arcadia_Object _parent;
  /** @brief Map of ADL types to readers. */
  Arcadia_Map* readers;
};

/**
 * @brief Get or create the ADL context.
 * @param thread A pointer to this thread.
 * @return A pointer to the ADL context.
 */
Arcadia_ADL_Context*
Arcadia_ADL_Context_getOrCreate
  (
    Arcadia_Thread* thread
  );

/**
 * @brief Read a definition.
 * @param thread A pointer to this thread.
 * @param self A pointer to this ADL context.
 * @param definitions A pointer to the ADL definitions to add the definition to.
 * @param input A pointer to the input DDL node.
 * @return A pointer to the ADL definition.
 */
Arcadia_ADL_Definition*
Arcadia_ADL_Context_readFromNode
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  );

/**
 * @brief Read a definition.
 * @param thread A pointer to this thread.
 * @param self A pointer to this ADL context.
 * @param definitions A pointer to the ADL definitions to add the definition to.
 * @param input A pointer to the input string.
 * @return A pointer to the ADL definition.
 */
Arcadia_ADL_Definition*
Arcadia_ADL_Context_readFromString
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Context* self,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* input
  );

#endif  // ARCADIA_ADL_CONTEXT_H_INCLUDED
