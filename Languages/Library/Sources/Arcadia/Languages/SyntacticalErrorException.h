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

#if !defined(ARCADIA_LANGUAGES_SYNTACTICALERROREXCEPTION_H_INCLUDED)
#define ARCADIA_LANGUAGES_SYNTACTICALERROREXCEPTION_H_INCLUDED

#if !defined(ARCADIA_LANGUAGES_PRIVATE)
  #error("do not include directly, include `Arcadia/Languages/Include.h` instead")
#endif

#include "Arcadia/Ring2/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Languages.SyntacticalErrorException", Arcadia_Languages_SyntacticalErrorException,
                          u8"Arcadia.Exception");

struct Arcadia_Languages_SyntacticalErrorExceptionDispatch {
  Arcadia_ExceptionDispatch _parent;
};

struct Arcadia_Languages_SyntacticalErrorException {
  Arcadia_Exception _parent;
};

Arcadia_Languages_SyntacticalErrorException*
Arcadia_Languages_SyntacticalErrorException_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_LANGUAGES_SYNTACTICALERROREXCEPTION_H_INCLUDED
