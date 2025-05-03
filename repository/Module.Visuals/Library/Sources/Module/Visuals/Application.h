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

#if !defined(MODULE_VISUALS_APPLICATION_H_INCLUDED)
#define MODULE_VISUALS_APPLICATION_H_INCLUDED
 
#include "Module/Visuals/Icon.h"
#include "Module/Visuals/Window.h"

/// @code
/// class Arcadia.Visuals.Application {
///   construct()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Application", Arcadia_Visuals_Application, u8"Arcadia.Object")

struct Arcadia_Visuals_Application {
  Arcadia_Object _parent;
  Arcadia_Visuals_Icon* (*createIcon)(Arcadia_Thread* thread, Arcadia_Visuals_Application* self,
                                      Arcadia_Integer32Value width,
                                      Arcadia_Integer32Value height,
                                      Arcadia_Natural8Value red,
                                      Arcadia_Natural8Value green,
                                      Arcadia_Natural8Value blue,
                                      Arcadia_Natural8Value alpha);
  Arcadia_Visuals_Window* (*createWindow)(Arcadia_Thread* thread, Arcadia_Visuals_Application* self);
};

Arcadia_Visuals_Icon*
Arcadia_Visuals_Application_createIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  );

Arcadia_Visuals_Window*
Arcadia_Visuals_Application_createWindow
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Application* self
  );

#endif // MODULE_VISUALS_APPLICATION_H_INCLUDED
