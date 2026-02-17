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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPENODE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPENODE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif
#include "Arcadia/Ring1/Implementation/TypeSystem/TypeKind.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/Names.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Types.h"

#define TypeNodeName u8"Arcadia.DynamicTypeSystem.TypeNode"
typedef struct TypeNode TypeNode;

struct TypeNode {
  /// Pointer to the successor in the bucket list or the null pointer.
  TypeNode* next;
  /// The kind of this type.
  Arcadia_TypeKind kind;
  /// The name of this type.
  Arcadia_Name* name;


  Arcadia_Type_Operations const* typeOperations;
  Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing;

};

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPENODE_H_INCLUDED
