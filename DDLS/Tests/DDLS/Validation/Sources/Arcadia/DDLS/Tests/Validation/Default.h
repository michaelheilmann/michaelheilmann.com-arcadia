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

#if !defined(ARCADIA_DDLS_TESTS_VALIDATION_DEFAULT_H_INCLUDED)
#define ARCADIA_DDLS_TESTS_VALIDATION_DEFAULT_H_INCLUDED

#include "Arcadia/DDLS/Include.h"
#include "Arcadia/DDL/Include.h"

void
Arcadia_DDLS_Tests_Validation_test1
  (
    Arcadia_Thread* thread
  );

// "$.type" not defined
void
Arcadia_DDLS_Tests_Validation_testRejectTypeNotDefined
  (
    Arcadia_Thread* thread
  );

// "$.red" not defined
void
Arcadia_DDLS_Tests_Validation_testRejectRedNotDefined
  (
    Arcadia_Thread* thread
  );

// "$.green" not defined
void
Arcadia_DDLS_Tests_Validation_testRejectGreenNotDefined
  (
    Arcadia_Thread* thread
  );

// "$.blue" not defined
void
Arcadia_DDLS_Tests_Validation_testRejectBlueNotDefined
  (
    Arcadia_Thread* thread
  );

// "$.type" is defined twice
void
Arcadia_DDLS_Tests_Validation_testRejectTypeDefinedTwice
  (
    Arcadia_Thread* thread
  );

// "$.red" is defined twice
void
Arcadia_DDLS_Tests_Validation_testRejectRedDefinedTwice
  (
    Arcadia_Thread* thread
  );

// "$.green" is defined twice
void
Arcadia_DDLS_Tests_Validation_testRejectGreenDefinedTwice
  (
    Arcadia_Thread* thread
  );

// "$.blue" is defined twice
void
Arcadia_DDLS_Tests_Validation_testRejectBlueDefinedTwice
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_DDLS_TESTS_VALIDATION_DEFAULT_H_INCLUDED
