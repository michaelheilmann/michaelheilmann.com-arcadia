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

#if !defined(ARCADIA_ADL_DEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_ADL_Definitions Arcadia_ADL_Definitions;

// @brief A definition.
//
// @code
// class Arcadia.ADL.Definition extends Arcadia.Object {
//
//   field definitions : Arcadia.ADL.Definitions
//
//   field name : Arcadia.String
//
//   constructor(definitions: Arcadia.ADL.Definitions, name : Arcadia.String)
//
//   method getDefinitions() : Arcadia.ADL.Definitions
//
//   method getName() : Arcadia.String
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.Definition", Arcadia_ADL_Definition,
                          u8"Arcadia.Object");

struct Arcadia_ADL_Definition {
  Arcadia_Object _parent;
  Arcadia_ADL_Definitions* definitions;
  Arcadia_String* name;
  void (*link)(Arcadia_Thread*, Arcadia_ADL_Definition*);
};

Arcadia_ADL_Definitions*
Arcadia_ADL_Definitions_getDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  );

Arcadia_String*
Arcadia_ADL_Definition_getName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  );

void
Arcadia_ADL_Definition_link
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definition* self
  );

#endif  // ARCADIA_ADL_DEFINITION_H_INCLUDED
