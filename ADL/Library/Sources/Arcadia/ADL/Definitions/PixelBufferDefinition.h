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

#if !defined(ARCADIA_ADL_DEFINITIONS_PIXELBUFFERDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_PIXELBUFFERDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"

// A definition of a pixel buffer.
//
// @code
// {
//   type  : "PixelBuffer",
//   name  : "MyGame.CheckerboardPixelBuffer",
//   width : 320,
//   height : 240,
//   operations [],
// }
// @endcode
//
// @code
// class Arcadia.ADL.PixelBufferDefinition extends Arcadia.ADL.Definition {
//
//   constructor(definitions : Arcadia.ADL.Definitions, qualifiedName : Arcadia.String)
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.PixelBufferDefinition", Arcadia_ADL_PixelBufferDefinition,
                          u8"Arcadia.ADL.Definition");

struct Arcadia_ADL_PixelBufferDefinitionDispatch {
  Arcadia_ADL_DefinitionDispatch _parent;
};

struct Arcadia_ADL_PixelBufferDefinition {
  Arcadia_ADL_Definition _parent;
  /// The width, in pixels, of the pixel buffer.
  Arcadia_Natural32Value width;
  /// The height, in pixels, of the pixel bufer.
  Arcadia_Natural32Value height;
  /// The list of operations.
  Arcadia_List* operations;
};

Arcadia_ADL_PixelBufferDefinition*
Arcadia_ADL_PixelBufferDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* qualifiedName,
    Arcadia_Natural32Value width,
    Arcadia_Natural32Value height
  );

#endif  // ARCADIA_ADL_DEFINITIONS_PIXELBUFFERDEFINITION_H_INCLUDED
