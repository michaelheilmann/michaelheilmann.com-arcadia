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

#if !defined(ARCADIA_ADL_DEFINITIONS_DSP_SAWTOOTHWAVEDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_DSP_SAWTOOTHWAVEDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_MODULE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"
#include "Arcadia/ADL/Reference.h"

// A DSP generating a sine wave signal of a constant frequency.
//
// @code
// {
//   type  : "DSP.SawtoothWave",
//   name  : "MyGame.MyDSPs.MySawtoothWave",
//   frequency : 220, /* Frequency in Hz. */   
// }
// @endcode
//
// @code
// class Arcadia.ADL.SawtoothWaveDefinition extends Arcadia.ADL.Definition {
//
//   constructor(definitions : Arcadia.ADL.Definitions, name : Arcadia.String, frequency : Arcadia.Natural32)
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.SawtoothWaveDefinition", Arcadia_ADL_SawtoothWaveDefinition,
                          u8"Arcadia.ADL.Definition");

struct Arcadia_ADL_SawtoothWaveDefinitionDispatch {
  Arcadia_ADL_DefinitionDispatch _parent;
};

struct Arcadia_ADL_SawtoothWaveDefinition {
  Arcadia_ADL_Definition _parent;
  Arcadia_Integer32Value frequency;
};

Arcadia_ADL_SawtoothWaveDefinition*
Arcadia_ADL_SawtoothWaveDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_Integer32Value frequency
  );

Arcadia_Integer32Value
Arcadia_ADL_SawtoothWaveDefinition_getFrequency
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_SawtoothWaveDefinition* self
  );

#endif  // ARCADIA_ADL_DEFINITIONS_DSP_SAWTOOTHWAVEDEFINITION_H_INCLUDED
