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

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"

// A definition of a sample buffer.
//
// @code
// {
//   type  : "SampleBuffer",
//   name  : "MyGame.SampleBuffer.ExplosionSampleBuffer",
//   length : 2000,
//   operations : [ ... ],
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
  /// The duration, in milliseconds, of the sample buffer.
  Arcadia_Natural32Value duration;
  /// The list of operations.
  Arcadia_List* operations;
};

Arcadia_ADL_SampleBufferDefinition*
Arcadia_ADL_SampleBufferDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_Natural32Value duration
  );

#endif  // ARCADIA_ADL_DEFINITIONS_AUDIALS_SAMPLEBUFFERDEFINITION_H_INCLUDED
