// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(R_TYPES_INTERNAL_H_INCLUDED)
#define R_TYPES_INTERNAL_H_INCLUDED

#if defined(R_EXPORTED_INCLUDE)
  #error("R/Types.internal.h must not be included from public header")
#endif
#include "R/Configure.h"
#include "R/Types.h"

typedef struct TypeNode TypeNode;

struct TypeNode {
  TypeNode* next;

  R_TypeNameValue typeName;
  R_TypeKind kind;
  TypeNode* parentObjectType;
  R_SizeValue valueSize;
  R_Type_Operations const* typeOperations;
  R_Type_TypeDestructingCallbackFunction* typeDestructing;
};

// Startup the type system
// WARNING: Internal function.
void
_R_Types_startup
  (
  );

// Shutdown the type system.
// WARNING: Internal function.
void
_R_Types_shutdown
  (
  );

#endif // R_TYPES_INTERNAL_H_INCLUDED
