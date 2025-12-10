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

#if !defined(ARCADIA_ENGINE_DEMO_AUDIALS_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_AUDIALS_H_INCLUDED

#include "Arcadia/DDL/Include.h"
#include "Arcadia/Audials/Include.h"
#include "Arcadia/Visuals/Include.h"

void
Arcadia_Engine_Demo_startupAudials
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine,
    Arcadia_DDL_Node* configuration
  );

#endif // ARCADIA_ENGINE_DEMO_AUDIALS_H_INCLUDED
