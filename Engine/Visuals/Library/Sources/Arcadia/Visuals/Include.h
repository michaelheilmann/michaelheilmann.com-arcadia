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

#pragma push_macro("ARCADIA_VISUALS_PRIVATE")
#undef ARCADIA_VISUALS_PRIVATE
#define ARCADIA_VISUALS_PRIVATE (1)

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Engine/Include.h"

#include "Arcadia/Visuals/Backend.h"
#include "Arcadia/Visuals/BackendContext.h"

#include "Arcadia/Visuals/Configuration.h"
#include "Arcadia/Visuals/Context.h"

#include "Arcadia/Visuals/Diagnostics.h"

#include "Arcadia/Visuals/Events/ApplicationQuitRequestedEvent.h"

#include "Arcadia/Visuals/Events/CanvasActivationStateChangedEvent.h"
#include "Arcadia/Visuals/Events/CanvasDpiChangedEvent.h"
#include "Arcadia/Visuals/Events/CanvasEvent.h"
#include "Arcadia/Visuals/Events/CanvasSizeChangedEvent.h"
#include "Arcadia/Visuals/Events/WindowClosedEvent.h"
#include "Arcadia/Visuals/Events/WindowPositionChangedEvent.h"
#include "Arcadia/Visuals/Events/WindowSizeChangedEvent.h"

#include "Arcadia/Visuals/Events/KeyboardKeyEvent.h"
#include "Arcadia/Visuals/Events/MouseButtonEvent.h"
#include "Arcadia/Visuals/Events/MousePointerEvent.h"

#include "Arcadia/Visuals/CullMode.h"
#include "Arcadia/Visuals/DisplayDevice.h"
#include "Arcadia/Visuals/DisplayMode.h"
#include "Arcadia/Imaging/Include.h"
#include "Arcadia/Visuals/TextureAddressMode.h"
#include "Arcadia/Visuals/TextureFilter.h"
#include "Arcadia/Visuals/VertexElementSemantics.h"
#include "Arcadia/Visuals/VertexElementSyntax.h"
#include "Arcadia/Visuals/WindingMode.h"

#undef ARCADIA_VISUALS_PRIVATE
#pragma pop_macro("ARCADIA_VISUALS_PRIVATE")

#endif // ARCADIA_VISUALS_INCLUDE_H_INCLUDED
