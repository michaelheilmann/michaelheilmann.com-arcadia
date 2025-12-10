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

#include "Arcadia/MIL/Frontend/Tests/SemanticalAnalysis/Pass.h"

#include "Arcadia/Include.h"

static void
Arcadia_MIL_Pass_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Pass* self
  );

static void
Arcadia_MIL_Pass_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_PassDispatch* self
  );

static void
Arcadia_MIL_Pass_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Pass* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MIL_Pass_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MIL_Pass_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.Pass", Arcadia_MIL_Pass,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_MIL_Pass_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Pass* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_Pass_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

static void
Arcadia_MIL_Pass_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_PassDispatch* self
  )
{ }

static void
Arcadia_MIL_Pass_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Pass* self
  )
{/*Initially empty.*/}
