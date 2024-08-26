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

#if !defined(R_R1_H_INCLUDED)
#define R_R1_H_INCLUDED

#include "r/boolean.h"

#include "r/bytebuffer.h"

#include "r/clamp.h"

#include "r/integer16.h"
#include "r/integer32.h"
#include "r/integer64.h"
#include "r/integer8.h"

#include "r/jumptarget.h"

#include "r/maximum.h"
#include "r/minimum.h"

#include "r/natural16.h"
#include "r/natural32.h"
#include "r/natural64.h"
#include "r/natural8.h"

#include "r/object.h"

#include "r/size.h"

#include "r/status.h"

#include "r/void.h"

R_Status
R_startup
  (
  );

R_Status
R_shutdown
  (
  );

#endif // R_R1_H_INCLUDED
