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

#if !defined(ARCADIA_ADL_DEFINITIONS_FILLOPERATIONDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_FILLOPERATIONDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"
typedef struct Arcadia_ADL_ColorDefinition Arcadia_ADL_ColorDefinition;
typedef struct Arcadia_ADL_Reference Arcadia_ADL_Reference;

// A definition of a fill operation on a pixel buffer.
//
// @code
// {
//   type  : "PixelBufferOperations.FillOperation",
//   name  : "MyGame.RedFillOperation",
//   color : "MyGame.Colors.Red",
// }
// @endcode
//
// @code
// class Arcadia.ADL.PixelBufferOperations.FillOperationDefinition extends Arcadia.ADL.Definition {
//
//   field color : Arcadia.ADL.ColorDefinition
//   field colorName : Arcadia.String
//
//   constructor(definitions : Arcadia.ADL.Definitions, qualifiedName : Arcadia.String, colorName : Arcadia.String)
//
//   method getColor() : Arcadia.String
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.PixelBufferOperations.FillOperationDefinition", Arcadia_ADL_PixelBufferOperations_FillOperationDefinition,
                          u8"Arcadia.ADL.Definition");

struct Arcadia_ADL_PixelBufferOperations_FillOperationDefinitionDispatch {
  Arcadia_ADL_DefinitionDispatch _parent;
};

struct Arcadia_ADL_PixelBufferOperations_FillOperationDefinition {
  Arcadia_ADL_Definition _parent;
  Arcadia_ADL_Reference* color;
};

Arcadia_ADL_PixelBufferOperations_FillOperationDefinition*
Arcadia_ADL_PixelBufferOperations_FillOperationDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* qualifiedName,
    Arcadia_String* colorName
  );

#endif  // ARCADIA_ADL_DEFINITIONS_FILLOPERATIONDEFINITION_H_INCLUDED
