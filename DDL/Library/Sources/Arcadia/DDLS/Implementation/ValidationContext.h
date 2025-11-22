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

#if !defined(ARCADIA_DDLS_IMPLEMENTATION_VALIDATIONCONTEXT_H_INCLUDED)
#define ARCADIA_DDLS_IMPLEMENTATION_VALIDATIONCONTEXT_H_INCLUDED

#include "Arcadia/DDLS/Schema.h"
#include "Arcadia/DDL/Include.h"
#include "Arcadia/DDLS/Implementation/Diagnostics.h"
#include "Arcadia/Languages/Include.h"

// Internal type of a validation context.
Arcadia_declareObjectType(u8"Arcadia.DDLS.ValidationContext", Arcadia_DDLS_ValidationContext,
                          u8"Arcadia.Object");

struct Arcadia_DDLS_ValidationContext {
  Arcadia_Object parent;
  Arcadia_DDLS_Diagnostics* diagnostics;
  Arcadia_StringBuffer* temporary1;
  Arcadia_Languages_StringTable* stringTable;
  void (*run)(Arcadia_Thread* thread, Arcadia_DDLS_ValidationContext*, Arcadia_DDLS_Type* type, Arcadia_DDL_Node*);
};

Arcadia_DDLS_ValidationContext*
Arcadia_DDLS_ValidationContext_create
  (
    Arcadia_Thread* thread
  );

void
Arcadia_DDLS_ValidationContext_run
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_ValidationContext* self,
    Arcadia_DDLS_Type* type,
    Arcadia_DDL_Node* node
  );

#endif // ARCADIA_DDLS_IMPLEMENTATION_VALIDATIONCONTEXT_H_INCLUDED
