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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_COMMANDLINE_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_COMMANDLINE_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Strings/Include.h"

// A command-line argument is of the form
// @code
// <argument> : '--'<name>('='<value>)?
// <name> : a name as defined in the Common Lexical Specification at https://michaelheilmann.com/specifications/common-lexical-specification
// <value> : a string as defined in the Common Lexical Specification at https://michaelheilmann.com/specifications/common-lexical-specification
// @endcode
// @code{<name>} is returned in @code{*key}.
// If a @code{<value>} is specified, it is returned in @code{*value}.
// Otherwise *value is assigned NULL.
Arcadia_BooleanValue
Arcadia_CommandLine_parseArgument
  (
    Arcadia_Thread* thread,
    Arcadia_UTF8Reader* reader,
    Arcadia_String** key,
    Arcadia_String** value
  );

void
Arcadia_CommandLine_raiseRequiredArgumentMissingError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  );

void
Arcadia_CommandLine_raiseUnknownArgumentError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key,
    Arcadia_String* value
  );

void
Arcadia_CommandLine_raiseNoValueError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  );

void
Arcadia_CommandLine_raiseValueInvalidError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key,
    Arcadia_String* value
  );

void
Arcadia_CommandLine_raiseAlreadySpecifiedError
  (
    Arcadia_Thread* thread,
    Arcadia_String* key
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_COMMANDLINE_H_INCLUDED
