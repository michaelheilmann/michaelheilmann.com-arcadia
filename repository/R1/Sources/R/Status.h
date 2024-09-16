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

#if !defined(R_STATUS_H_INCLUDED)
#define R_STATUS_H_INCLUDED

#include <inttypes.h>

#define R_Status_Success (0)

#define R_Status_AllocationFailed (1)
#define R_Status_ArgumentTypeInvalid (2)
#define R_Status_ArgumentValueInvalid (3)
#define R_Status_EncodingInvalid (4)
#define R_Status_FileSystemOperationFailed (5)
#define R_Status_Initialized (6)
#define R_Status_NumberOfArgumentsInvalid (7)
#define R_Status_OperationInvalid (8)
#define R_Status_TestFailed (9)
#define R_Status_Uninitialized (10)

#define R_Status_TypeExists (11)
#define R_Status_TypeNotExists (12)

#define R_Status_NotExists (13)

typedef uint32_t R_Status;

R_Status
R_getStatus
  (
  );

void
R_setStatus
  (
    R_Status status
  );

#endif // R_STATUS_H_INCLUDED