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

#if !defined(__ARCADIA_ENGINE_AUDIALS_BACKENDCONTEXT_H_INCLUDED)
#define __ARCADIA_ENGINE_AUDIALS_BACKENDCONTEXT_H_INCLUDED

#if !defined(ARCADIA_ENGINE_PRIVATE) || 1 != ARCADIA_ENGINE_PRIVATE
  #error("do not include directly, include `Arcadia/Engine/Include.h` instead")
#endif

#include "Arcadia/Engine/BackendContext.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Audials.BackendContext", Arcadia_Engine_Audials_BackendContext,
                          u8"Arcadia.Engine.BackendContext");

struct Arcadia_Engine_Audials_BackendContextDispatch {
  Arcadia_Engine_BackendContextDispatch _parent;
};

struct Arcadia_Engine_Audials_BackendContext {
  Arcadia_Engine_BackendContext _parent;
};


#endif // __ARCADIA_ENGINE_AUDIALS_BACKENDCONTEXT_H_INCLUDED
