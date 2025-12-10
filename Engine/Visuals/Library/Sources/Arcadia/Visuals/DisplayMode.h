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

#if !defined (ARCADIA_VISUALS_DISPLAYMODE_H_INCLUDED)
#define ARCADIA_VISUALS_DISPLAYMODE_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

// Information on a display mode available on a display device.
// See Arcadia.Visuals.DisplayDevice for more information.
Arcadia_declareObjectType(u8"Arcadia.Visuals.DisplayMode", Arcadia_Visuals_DisplayMode,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_DisplayModeDispatch {
  Arcadia_ObjectDispatch _parent;

  Arcadia_Integer32Value (*getHorizontalResolution)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayMode* self);
  Arcadia_Integer32Value (*getVerticalResolution)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayMode* self);
  Arcadia_Integer32Value (*getColorDepth)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayMode* self);
  Arcadia_Integer32Value (*getFrequency)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayMode* self);
  void (*apply)(Arcadia_Thread* thread, Arcadia_Visuals_DisplayMode* self);
};

struct Arcadia_Visuals_DisplayMode {
  Arcadia_Object _parent;
};

Arcadia_Integer32Value
Arcadia_Visuals_DisplayMode_getHorizontalResolution
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  );

Arcadia_Integer32Value
Arcadia_Visuals_DisplayMode_getVerticalResolution
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  );

Arcadia_Integer32Value
Arcadia_Visuals_DisplayMode_getColorDepth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  );

Arcadia_Integer32Value
Arcadia_Visuals_DisplayMode_getFrequency
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  );

void
Arcadia_Visuals_DisplayMode_apply
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_DisplayMode* self
  );

#endif // ARCADIA_VISUALS_DISPLAYMODE_H_INCLUDED
