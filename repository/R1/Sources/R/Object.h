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

#include "R/Configure.h"
#include "Arms.h"

typedef void (R_Object_VisitCallbackFunction)(void *);

typedef void (R_Object_DestructCallbackFunction)(void*);

typedef void R_Type;

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void R_registerObjectType(char const* name, size_t nameLength, size_t valueSize, R_Object_VisitCallbackFunction* visit, R_Object_DestructCallbackFunction* destruct);

/* R_Status_ArgumentValueInvalid, R_Status_TypeNotExists */
R_Type* R_getObjectType(char const* name, size_t nameLength);

/* R_Status_AllocationFailed */
void* R_allocateObject(char const* name, size_t nameLength, size_t size);

#endif // R_OBJECT_H_INCLUDED
