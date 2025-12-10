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

#if !defined(ARCADIA_ADL_DEFINITIONS_COLORDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_COLORDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"

// The definition of a color.
//
// @code
// {
//   type  : "Color",
//   name  : "MyGame.Colors.Red",
//   red   : 255,
//   green : 0,
//   blue  : 0,
// }
// @endcode
//
// @code
// class Arcadia.ADL.ColorDefinition extends Arcadia.ADL.Definition {
//
//   field red, green, blue : Arcadia.Natural8
//
//   constructor(definitions : Arcadia.ADL.Definitions, name : Arcadia.String, red, green, blue : Arcadia.Natural8)
//
//   method getRed() : Arcadia.Natural8
//   method getGreen() : Arcadia.Natural8
//   method getBlue() : Arcadia.Natural8
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.ColorDefinition", Arcadia_ADL_ColorDefinition,
                          u8"Arcadia.Object");

struct Arcadia_ADL_ColorDefinitionDispatch {
  Arcadia_ADL_DefinitionDispatch _parent;
};

struct Arcadia_ADL_ColorDefinition {
  Arcadia_ADL_Definition _parent;
  Arcadia_Natural8Value red;
  Arcadia_Natural8Value green;
  Arcadia_Natural8Value blue;
};

Arcadia_ADL_ColorDefinition*
Arcadia_ADL_ColorDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue
  );

#endif  // ARCADIA_ADL_DEFINITIONS_COLORDEFINITION_H_INCLUDED
