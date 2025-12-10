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

#if !defined(ARCADIA_ADL_DEFINITIONS_CHECKERBOARDFILLOPERATIONDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_CHECKERBOARDFILLOPERATIONDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"
#include "Arcadia/ADL/Reference.h"
typedef struct Arcadia_ADL_ColorDefinition Arcadia_ADL_ColorDefinition;

// A definition of a fill operation on a pixel buffer.
//
// @code
// {
//   type  : "PixelBufferOperations.CheckerboardFillOperation",
//   name  : "MyGame.RedCheckerboardFillOperation",
//   firstCheckerColor : "MyGame.Colors.Black",
//   secondCheckerColor : "MyGame.Colors.White",
//   checkerboardWidth : 8,
//   checkerboardHeight: 8,
// }
// @endcode
//
// @code
// class Arcadia.ADL.PixelBufferOperations.CheckerboardFillOperationDefinition extends Arcadia.ADL.Definition {
//
//   field firstCheckerColor : Arcadia.ADL.Reference
//
//   field secondCheckerColor : Arcadia.ADL.Reference
//
//   field checkerWidth : Arcadia.Integer32
//   field checkerHeight : Arcadia.Integer32
//
//   constructor(definitions : Arcadia.ADL.Definitions,
//               qualifiedName : Arcadia.String,
//               checkerWidth, checkerHeight : Arcadia.Integer32,
//               firstCheckerColorName, secondCheckerColorName : Arcadia.String)
//
//   method getColor() : Arcadia.String
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.PixelBufferOperations.CheckerboardFillOperationDefinition", Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition,
                          u8"Arcadia.ADL.Definition");

struct Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinitionDispatch {
  Arcadia_ADL_DefinitionDispatch _parent;
};

struct Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition {
  Arcadia_ADL_Definition _parent;

  Arcadia_Integer32Value checkerWidth;
  Arcadia_Integer32Value checkerHeight;

  Arcadia_ADL_Reference* firstCheckerColor;
  Arcadia_ADL_Reference* secondCheckerColor;
};

Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition*
Arcadia_ADL_PixelBufferOperations_CheckerboardFillOperationDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* qualifiedName,
    Arcadia_Integer32Value checkerWidth,
    Arcadia_Integer32Value checkerHeight,
    Arcadia_String* firstCheckerColorName,
    Arcadia_String* secondCheckerColorName
  );

#endif  // ARCADIA_ADL_DEFINITIONS_CHECKERBOARDFILLOPERATIONDEFINITION_H_INCLUDED
