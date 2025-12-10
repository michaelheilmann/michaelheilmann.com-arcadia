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

#define ARCADIA_ADL_PRIVATE (1)
#include "Arcadia/ADL/Reader.h"

static void
Arcadia_ADL_Reader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reader* self
  );

static void
Arcadia_ADL_Reader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ReaderDispatch* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*) & Arcadia_ADL_Reader_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.Reader", Arcadia_ADL_Reader,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_ADL_Reader_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reader* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_Reader_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 0 + 1);
}

static void
Arcadia_ADL_Reader_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ReaderDispatch* self
  )
{
}

Arcadia_String*
Arcadia_ADL_Reader_getTypeName
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reader* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_ADL_Reader, getTypeName, self); }

Arcadia_ADL_Definition*
Arcadia_ADL_Reader_read
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Reader* self,
    Arcadia_ADL_Context* context,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_DDL_Node* input
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_ADL_Reader, read, self, context, definitions, input); }
