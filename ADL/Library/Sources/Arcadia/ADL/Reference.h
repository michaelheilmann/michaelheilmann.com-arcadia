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

#if !defined(ARCADIA_ADL_REFERENCE_H_INCLUDED)
#define ARCADIA_ADL_REFERENCE_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_ADL_Definition Arcadia_ADL_Definition;
typedef struct Arcadia_ADL_Definitions Arcadia_ADL_Definitions;

// @brief A reference.
//
// @code
// class Arcadia.ADL.Reference extends Arcadia.Object {
//
//   field definitions : Arcadia.ADL.Definitions
//
//   field definition : Arcadia.ADL.Definition
//
//   field definitionName : Arcadia.String
//
//   constructor(definitions: Arcadia.ADL.Definitions, definitionName : Arcadia.String)
//
//   method getDefinitionName() : Arcadia.String
//
//   method getDefinitions() : Arcadia.ADL.Definitions
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.Reference", Arcadia_ADL_Reference,
                          u8"Arcadia.Object");

struct Arcadia_ADL_ReferenceDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_ADL_Reference {
  Arcadia_Object _parent;

  Arcadia_ADL_Definition* definition;
  Arcadia_String* definitionName;
  Arcadia_ADL_Definitions* definitions;
};

Arcadia_ADL_Reference*
Arcadia_ADL_Reference_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* definitionName
  );

Arcadia_ADL_Definitions*
Arcadia_ADL_References_getDefinitions
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  );

Arcadia_String*
Arcadia_ADL_Reference_getDefinitionName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  );

void
Arcadia_ADL_Reference_resolve
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reference* self
  );

#endif  // ARCADIA_ADL_REFERENCE_H_INCLUDED
