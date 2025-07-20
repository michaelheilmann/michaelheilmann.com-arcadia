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

#if !defined(ARCADIA_VISUALS_INCLUDE_H_INCLUDED)
#define ARCADIA_VISUALS_INCLUDE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

#include "Arcadia/Visuals/Events/CanvasEvent.h"
#include "Arcadia/Visuals/CullMode.h"
#include "Arcadia/Visuals/DisplayDevice.h"
#include "Arcadia/Visuals/DisplayMode.h"
#include "Arcadia/Imaging/Include.h"
#include "Arcadia/Visuals/TextureAddressMode.h"
#include "Arcadia/Visuals/TextureFilter.h"
#include "Arcadia/Visuals/VertexElementSemantics.h"
#include "Arcadia/Visuals/VertexElementSyntax.h"
#include "Arcadia/Visuals/WindingMode.h"

#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  #include "Arcadia/Visuals/Windows/Application.h"
  #include "Arcadia/Visuals/Windows/TextureFont.h"
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  #include "Arcadia/Visuals/Linux/Application.h"
#else
  #error("environment not (yet) supported")
#endif

#endif // ARCADIA_VISUALS_INCLUDE_H_INCLUDED
