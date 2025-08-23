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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_INCLUDE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_VISUALS_PRIVATE")
#undef ARCADIA_VISUALS_PRIVATE
#define ARCADIA_VISUALS_PRIVATE (1)

#include "Arcadia/Visuals/Include.h"

#include "Arcadia/Visuals/Implementation/Diagnostics.h"

#include "Arcadia/Visuals/Implementation/Events/ApplicationQuitRequestedEvent.h"

#include "Arcadia/Imaging/Include.h"

#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  #include "Arcadia/Visuals/Implementation/Windows/Application.h"
  #include "Arcadia/Visuals/Implementation/Windows/TextureFont.h"
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  #include "Arcadia/Visuals/Implementation/Linux/Application.h"
#else
  #error("environment not (yet) supported")
#endif

#undef ARCADIA_VISUALS_PRIVATE
#pragma pop_macro("ARCADIA_VISUALS_PRIVATE")

#endif // ARCADIA_VISUALS_IMPLEMENTATION_INCLUDE_H_INCLUDED
