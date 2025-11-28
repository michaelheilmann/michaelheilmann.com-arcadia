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

#if !defined(ARCADIA_VISUALS_BACKENDCONTEXT_H_INCLUDED)
#define ARCADIA_VISUALS_BACKENDCONTEXT_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Visuals/Icon.h"
#include "Arcadia/Visuals/Window.h"
typedef struct Arcadia_Engine_Event Arcadia_Engine_Event;

/// @code
/// class Arcadia.Visuals.BackendContext extends Arcadia.Engine.BackendContext {
///
///   constructor
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
///
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.BackendContext", Arcadia_Visuals_BackendContext,
                          u8"Arcadia.Engine.BackendContext")

struct Arcadia_Visuals_BackendContext {
  Arcadia_Engine_BackendContext _parent;

  /// @brief List of windows.
  Arcadia_List* windows;

  Arcadia_Visuals_Icon* (*createIcon)(Arcadia_Thread* thread, Arcadia_Visuals_BackendContext* self, Arcadia_Imaging_PixelBuffer* pixelBuffer);

  Arcadia_Visuals_Window* (*createWindow)(Arcadia_Thread* thread, Arcadia_Visuals_BackendContext* self);

  Arcadia_List* (*getDisplayDevices)(Arcadia_Thread* thread, Arcadia_Visuals_BackendContext* self);

  void (*update)(Arcadia_Thread* thread, Arcadia_Visuals_BackendContext* self);
};

Arcadia_Visuals_Icon*
Arcadia_Visuals_BackendContext_createIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self,
    Arcadia_Imaging_PixelBuffer* pixelBuffer
  );

Arcadia_Visuals_Window*
Arcadia_Visuals_BackendContext_createWindow
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  );

/// @brief Enumerate all display devices.
/// @param thread A pointer to this thread.
/// @param self A pointer to this backend context.
Arcadia_List*
Arcadia_Visuals_BackendContext_getDisplayDevices
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  );

/// @brief Update this backend context.
/// @param thread A pointer to this thread.
/// @param self A pointer to this backend context.
void
Arcadia_Visuals_BackendContext_update
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_BackendContext* self
  );

#endif // ARCADIA_VISUALS_BACKENDCONTEXT_H_INCLUDED
