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

#if !defined(ARCADIA_DDLS_IMPLEMENTATION_VALIDATIONCONTEXT_H_INCLUDED)
#define ARCADIA_DDLS_IMPLEMENTATION_VALIDATIONCONTEXT_H_INCLUDED

#include "Arcadia/DDLS/Nodes/Include.h"
#include "Arcadia/DDL/Include.h"
#include "Arcadia/DDLS/Implementation/Diagnostics.h"
#include "Arcadia/Languages/Include.h"

// Internal type of a validation context.
Arcadia_declareObjectType(u8"Arcadia.DDLS.ValidationContext", Arcadia_DDLS_ValidationContext,
                          u8"Arcadia.Object");

struct Arcadia_DDLS_ValidationContextDispatch {
  Arcadia_ObjectDispatch parent;
  void (*run)(Arcadia_Thread* thread, Arcadia_DDLS_ValidationContext*, Arcadia_String* name, Arcadia_DDL_Node*);
};

struct Arcadia_DDLS_ValidationContext {
  Arcadia_Object parent;
  /// @brief The schemata used by this validation context.
  Arcadia_Map* schemata;
  Arcadia_DDLS_Diagnostics* diagnostics;
  Arcadia_StringBuffer* temporary1;
  Arcadia_Languages_StringTable* stringTable;
};

Arcadia_DDLS_ValidationContext*
Arcadia_DDLS_ValidationContext_create
  (
    Arcadia_Thread* thread
  );

/// @brief Add a schema node to this validation context.
/// @param thread A pointer to this thread.
/// @param self A pointer to this validation context.
/// @param schemaNode A pointer the schema node.
/// @error A schema of the same name already eixsts in this validation context.
void
Arcadia_DDLS_ValidationContext_addSchema
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_SchemaNode* schemaNode
  );

/// @brief Get a schema node from this validation context.
/// @param thread A pointer to this thread.
/// @param self A pointer to this validation context.
/// @param name The name of the schema node.
/// @return A pointer to the schema node if it was found. The null pointer otherwise.
Arcadia_DDLS_SchemaNode*
Arcadia_DDLS_ValidationContext_getSchema
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_String* name
  );

/// @brief Remove a schema node from this validation context.
/// @param thread A pointer to this thread.
/// @param self A pointer to this validation context.
/// @param name The name of the schema node.
/// @return A pointer to the schema node if it was found. The null pointer otherwise.
Arcadia_DDLS_SchemaNode*
Arcadia_DDLS_ValidationContext_removeSchema
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_String* name
  );

void
Arcadia_DDLS_ValidationContext_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_String* name,
    Arcadia_DDL_Node* node
  );

#endif // ARCADIA_DDLS_IMPLEMENTATION_VALIDATIONCONTEXT_H_INCLUDED
