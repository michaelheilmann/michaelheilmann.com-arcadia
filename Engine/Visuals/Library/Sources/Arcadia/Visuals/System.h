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

#if !defined(ARCADIA_VISUALS_SYSTEM_H_INCLUDED)
#define ARCADIA_VISUALS_SYSTEM_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Visuals/Icon.h"
#include "Arcadia/Visuals/Window.h"
typedef struct Arcadia_Engine_Event Arcadia_Engine_Event;

/// @code
/// class Arcadia.Visuals.System extends Arcadia.Engine.System {
///   construct
///     (
///     )
/// 
///   method
///   createIcon
///     (
///       width : Arcadia.Integer32,
///       height : Arcadia.Integer32,
///       red : Arcadia.Natural8,
///       green : Arcadia.Natural8,
///       blue : Arcadia.Natural8,
///       alpha : Arcadia.Natural8
///     )
///     : Arcadia.Visuals.Icon
///   
///   method
///   createWindow
///     (
///     )
///     : Arcadia.Visuals.Window
/// 
///   method
///   getDisplayDevices
///     (
///     )
///     : Arcadia.List
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.System", Arcadia_Visuals_System,
                          u8"Arcadia.Engine.System")

struct Arcadia_Visuals_System {
  Arcadia_Engine_System _parent;

  /// @brief List of windows.
  Arcadia_List* windows;

  Arcadia_Visuals_Icon* (*createIcon)(Arcadia_Thread* thread, Arcadia_Visuals_System* self,
                                      Arcadia_Integer32Value width,
                                      Arcadia_Integer32Value height,
                                      Arcadia_Natural8Value red,
                                      Arcadia_Natural8Value green,
                                      Arcadia_Natural8Value blue,
                                      Arcadia_Natural8Value alpha);
  
  Arcadia_Visuals_Window* (*createWindow)(Arcadia_Thread* thread, Arcadia_Visuals_System* self);
  
  Arcadia_List* (*getDisplayDevices)(Arcadia_Thread* thread, Arcadia_Visuals_System* self);

  void (*update)(Arcadia_Thread* thread, Arcadia_Visuals_System* self);
};

Arcadia_Visuals_Icon*
Arcadia_Visuals_System_createIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_System* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue,
    Arcadia_Natural8Value alpha
  );

Arcadia_Visuals_Window*
Arcadia_Visuals_System_createWindow
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_System* self
  );

/// @brief Enumerate all display devices.
/// @param thread A pointer to this thread.
/// @param self A pointer to this application.
/// @todo Add Linux implementation.
Arcadia_List*
Arcadia_Visuals_System_getDisplayDevices
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_System* self
  );

/// @brief Update this window.
/// @param thread A pointer to this thread.
/// @param self A pointer to this window.
void
Arcadia_Visuals_System_update
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_System* self
  );

#endif // ARCADIA_VISUALS_SYSTEM_H_INCLUDED
