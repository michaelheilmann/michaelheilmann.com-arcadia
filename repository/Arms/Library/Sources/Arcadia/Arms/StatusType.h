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

#if !defined(ARCADIA_ARMS_STATUSTYPE_H_INCLUDED)
#define ARCADIA_ARMS_STATUSTYPE_H_INCLUDED

#include "Arcadia/Arms/Configure.h"

/// An enumeration of status codes.
typedef enum Arms_Status {
  Arms_Status_Success = 0,
  Arms_Status_ArgumentValueInvalid = 1,
  Arms_Status_AllocationFailed = 2,
  Arms_Status_TypeExists = 3,
  Arms_Status_TypeNotExists = 4,
  Arms_Status_OperationInvalid = 5,
  Arms_Status_EnvironmentFailed = 6,
} Arms_Status;

#endif // ARCADIA_ARMS_STATUSTYPE_H_INCLUDED
