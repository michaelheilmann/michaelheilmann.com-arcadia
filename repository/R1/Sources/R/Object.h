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

// Last modified: 2024-08-27

#if !defined(R_OBJECT_H_INCLUDED)
#define R_OBJECT_H_INCLUDED

#include "R/Types.h"

typedef struct R_Object R_Object;
void _R_Object_registerType();

struct R_Object {
  int dummy;
};

void
R_Object_construct
  (
    R_Object* self
  );

/* R_ArgumentValueInvalid, R_Status_AllocationFailed */
void*
R_allocateObject
  (
    R_Type* type
  );

void
R_Object_setType
  (
    void* self,
    R_Type* type
  );

/// @brief Visit an object.
/// @param self A pointer to the object.
void
R_Object_visit
  (
    void* self
  );

/// @brief Get the type of an object.
/// @param self A pointer to the object.
/// @return The type of an object.
R_Type*
R_Object_getType
  (
    void* self
  );

#endif // R_OBJECT_H_INCLUDED
