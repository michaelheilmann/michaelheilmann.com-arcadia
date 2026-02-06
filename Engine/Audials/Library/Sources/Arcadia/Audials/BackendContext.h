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

#if !defined(ARCADIA_AUDIALS_DEFAULTBACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_AUDIALS_DEFAULTBACKENDCONTEXT_H_INCLUDED

#include "Arcadia/Engine/Include.h"

/// @code
/// class Arcadia.Engine.Audials.BackendContextBase extends Arcadia.Engine.Audials.BackendContext {
///   constructor
///     (
///     )
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Engine.Audials.BackendContextBase", Arcadia_Engine_Audials_BackendContextBase,
                          u8"Arcadia.Engine.Audials.BackendContext")

struct Arcadia_Engine_Audials_BackendContextBaseDispatch {
  Arcadia_Engine_Audials_BackendContextDispatch parent;
};

struct Arcadia_Engine_Audials_BackendContextBase {
  Arcadia_Engine_Audials_BackendContext _parent;
};

#endif // ARCADIA_AUDIALS_DEFAULTBACKENDCONTEXT_H_INCLUDED
