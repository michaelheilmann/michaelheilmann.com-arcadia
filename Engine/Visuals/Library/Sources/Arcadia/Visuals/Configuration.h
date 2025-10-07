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

#if !defined(ARCADIA_VISUALS_CONFIGURATION_H_INCLUDED)
#define ARCADIA_VISUALS_CONFIGURATION_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif

#include "Arcadia/Ring2/Include.h"

/// @code
/// class Arcadia.Visuals.Configuration extends Arcadia.Object {
///   constructor()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Configuration", Arcadia_Visuals_Configuration,
                          u8"Arcadia.Object")

struct Arcadia_Visuals_Configuration {
  Arcadia_Object _parent;
  struct {

    struct {

      /// Must be non-negative integer.
      /// Default: 4.
      Arcadia_String* major;

      /// Must be non-negative integer.
      /// Default: 3.
      Arcadia_String* minor;

    } version;

  } opengl;

  struct {

    /// Must be non-negative integer.
    /// Default: 24.
    Arcadia_String* depthBits;

  } depthBuffer;

  struct {

    /// Must be non-negative.
    /// Default: 8.
    Arcadia_String* redBits;

    /// Must be non-negative.
    /// Default: 8.
    Arcadia_String* greenBits;

    /// Must be non-negative.
    /// Default: 8.
    Arcadia_String* blueBits;

    /// Must be non-negative.
    /// Default: 8.
    Arcadia_String*  alphaBits;

  } colorBuffer;

};

Arcadia_Visuals_Configuration*
Arcadia_Visuals_Configuration_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_CONFIGURATION_H_INCLUDED
