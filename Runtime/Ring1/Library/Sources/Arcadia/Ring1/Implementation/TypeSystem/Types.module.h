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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPES_MODULE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPES_MODULE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif
#include "Arcadia/Ring1/Implementation/Module.h"
#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/TypeNode.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/EnumerationTypeNode.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/InterfaceTypeNode.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/InternalTypeNode.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/ObjectTypeNode.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/ScalarTypeNode.h"

typedef struct TypeNodes TypeNodes;

struct TypeNodes {
  TypeNode** buckets;
  size_t size;
  size_t capacity;
};

Arcadia_DeclareModule("Arcadia.Types", Arcadia_Types);

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPES_MODULE_H_INCLUDED
