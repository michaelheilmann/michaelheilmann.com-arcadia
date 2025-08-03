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

#if !defined(ARCADIA_VISUALS_DISPLAYDEVICE_H_INCLUDED)
#define ARCADIA_VISUALS_DISPLAYDEVICE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_Visuals_DisplayMode Arcadia_Visuals_DisplayMode;

Arcadia_declareObjectType(u8"Arcadia.Visuals.DisplayDevice", Arcadia_Visuals_DisplayDevice,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_DisplayDevice {
  Arcadia_Object _parent;
  Arcadia_Visuals_DisplayMode* (*getCurrentDisplayMode)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayDevice* self);
  Arcadia_List* (*getAvailableDisplayModes)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayDevice* self);
  void (*getBounds)(Arcadia_Thread*, Arcadia_Visuals_DisplayDevice*, Arcadia_Integer32Value*, Arcadia_Integer32Value*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);
  Arcadia_String* (*getName)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayDevice* self);
  Arcadia_String* (*getId)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayDevice* self);
};

Arcadia_Visuals_DisplayMode*
Arcadia_Visuals_DisplayDevice_getCurrentDisplayMode
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self
  );

Arcadia_List*
Arcadia_Visuals_DisplayDevice_getAvailableDisplayModes
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self
  );

/// @brief Get the bounds of this display.
/// @param thread A pointer to this thread.
/// @param self A pointer to this display device.
/// @param left, top, width, bottom Pointers to Arcadia_Integer32Value variable receiving the left, top, right, bottom coordinates of the display.
void
Arcadia_Visuals_DisplayDevice_getBounds
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self,
    Arcadia_Integer32Value *left,
    Arcadia_Integer32Value *top,
    Arcadia_Integer32Value *right,
    Arcadia_Integer32Value *bottom
  );

// @brief The a human-readable/display name of the device.
// @param thread A pointer to this thread.
// @param self A pointer to this display device.
// @return A pointer to the name.
Arcadia_String*
Arcadia_Visuals_DisplayDevice_getName
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self
  );

// @brief Get the unique identifier of this device.
// @param thread A pointer to this thread.
// @param self A pointer to this display device.
// @return A pointer to the unique identifier.
Arcadia_String*
Arcadia_Visuals_DisplayDevice_getId
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayDevice* self
  );

#endif // ARCADIA_VISUALS_DISPLAYDEVICE_H_INCLUDED
