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

#if !defined(ARCADIA_RING1_TESTS_OBJECTTYPETESTS_MYINTERFACEA_H_INCLUDED)
#define ARCADIA_RING1_TESTS_OBJECTTYPETESTS_MYINTERFACEA_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

Arcadia_declareObjectType(u8"Arcadia.MyInterfaceA", Arcadia_MyInterfaceA,
                          u8"Arcadia.Interface");

struct Arcadia_MyInterfaceADispatch {
  Arcadia_InterfaceDispatch parent;
};

#if 0
struct Arcadia_MyObjectA {
  Arcadia_Object parent;
};

Arcadia_MyObjectA*
Arcadia_MyObjectA_create
  (
    Arcadia_Thread* thread
  );
#endif

#endif // ARCADIA_RING1_TESTS_OBJECTTYPETESTS_MYINTERFACEA_H_INCLUDED
