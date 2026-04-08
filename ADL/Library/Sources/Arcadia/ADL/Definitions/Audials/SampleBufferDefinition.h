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

#if !defined(ARCADIA_ADL_DEFINITIONS_AUDIALS_SAMPLEBUFFERDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_AUDIALS_SAMPLEBUFFERDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_MODULE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"
#include "Arcadia/ADL/Reference.h"

// A definition of a sample buffer.
//
// @code
// {
//   type  : "SampleBuffer",
//   name  : "MyGame.MyScene.MySampleBuffer",
//   length : 2,
//   dsp : "MyGame.MyScene.MyDSP",
// }
// @endcode
//
// @code
// class Arcadia.ADL.SampleBufferDefinition extends Arcadia.ADL.Definition {
//
//   constructor(definitions : Arcadia.ADL.Definitions, qualifiedName : Arcadia.String)
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.SampleBufferDefinition", Arcadia_ADL_SampleBufferDefinition,
                          u8"Arcadia.ADL.Definition");

struct Arcadia_ADL_SampleBufferDefinitionDispatch {
  Arcadia_ADL_DefinitionDispatch _parent;
};

struct Arcadia_ADL_SampleBufferDefinition {
  Arcadia_ADL_Definition _parent;
  /// The duration, in seconds, of the sample buffer.
  Arcadia_Natural32Value duration;
  /// Reference to the DSP to fill the sample buffer. 
  Arcadia_ADL_Reference* dsp;
};

Arcadia_ADL_SampleBufferDefinition*
Arcadia_ADL_SampleBufferDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_Natural32Value duration,
    Arcadia_ADL_Reference* dsp
  );

#endif  // ARCADIA_ADL_DEFINITIONS_AUDIALS_SAMPLEBUFFERDEFINITION_H_INCLUDED
