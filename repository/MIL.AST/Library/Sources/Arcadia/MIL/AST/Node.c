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

#include "Arcadia/MIL/AST/Node.h"

#include "Arcadia/MIL/AST/Include.h"

static void
Arcadia_MIL_AST_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_Node* self
  );

static void
Arcadia_MIL_AST_Node_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_Node* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_MIL_AST_Node_objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_MIL_AST_Node_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_MIL_AST_Node_visit,
};

static const Arcadia_Type_Operations _Arcadia_MIL_AST_Node_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_MIL_AST_Node_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MIL.AST.Node", Arcadia_MIL_AST_Node,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_MIL_AST_Node_typeOperations);

static void
Arcadia_MIL_AST_Node_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_Node* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_MIL_AST_Node_getType(thread);
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
Arcadia_MIL_AST_Node_visit
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_AST_Node* self
  )
{/*Initially empty.*/}

