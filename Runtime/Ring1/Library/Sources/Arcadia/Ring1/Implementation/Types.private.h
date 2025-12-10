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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPES_PRIVATE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPES_PRIVATE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif
#include "Arcadia/Ring1/Implementation/Module.h"
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

  /// The pointer to the dispatch or null.
  /// Only relevant for Arcadia_TypeKind_Object.
  Arcadia_Dispatch* dispatch;
  /// The size, in Bytes, of the dispatch.
  /// Only relevant for Arcadia_TypeKind_Object.
  Arcadia_SizeValue dispatchSize;
  /// A pointer to the dispatch initializer or null.
  /// Only relevant for Arcadia_TypeKind_Object.
  void (*initializeDispatch)(Arcadia_Dispatch*);
};


typedef struct TypeNodes TypeNodes;

struct TypeNodes {
  TypeNode** buckets;
  size_t size;
  size_t capacity;
};

Arcadia_DeclareModule("Arcadia.Types", Arcadia_Types);

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPES_PRIVATE_H_INCLUDED
