// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-22

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPES_PRIVATE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPES_PRIVATE_H_INCLUDED

#if defined(R_EXPORTED_INCLUDE)
  #error("R/Types.internal.h must not be included from public header")
#endif
#include "Arcadia/Ring1/Implementation/Configure.h"
#include "Arcadia/Ring1/Include.h"

typedef struct TypeNode TypeNode;

struct TypeNode {
  TypeNode* next;

  Arcadia_AtomValue typeName;
  Arcadia_TypeKind kind;
  TypeNode* parentObjectType;
  Arcadia_SizeValue valueSize;
  Arcadia_Type_Operations const* typeOperations;
  Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing;
};

/// @brief Startup the type system
/// @warning Internal function.
void
Arcadia_Types_startup
  (
    Arcadia_Process1* process
  );

/// @brief Shutdown the type system.
/// @warning Internal function.
void
Arcadia_Types_shutdown
  (
    Arcadia_Process1* process
  );

/// @brief Must be invoked before the pre mark phase.
/// @warning Internal function.
void
Arcadia_Types_onPreMark
  (
    Arcadia_Process1* process,
    Arcadia_BooleanValue purgeCache
  );

/// @brief Must be invoked after the finalize phase.
/// @warning Internal function.
void
Arcadia_Types_onFinalize
  (
    Arcadia_Process1* process
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPES_PRIVATE_H_INCLUDED
