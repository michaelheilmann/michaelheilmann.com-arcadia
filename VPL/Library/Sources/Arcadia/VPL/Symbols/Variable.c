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

#define ARCADIA_VPL_PRIVATE (1)
#include "Arcadia/VPL/Symbols/Variable.h"

#include <string.h>

static void
Arcadia_VPL_Symbols_Variable_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Variable* self
  );

static void
Arcadia_VPL_Symbols_Variable_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_VariableDispatch* self
  );

static void
Arcadia_VPL_Symbols_Variable_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Variable* self
  );

static Arcadia_String*
Arcadia_VPL_Symbols_Variable_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Variable* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Symbols_Variable_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Symbols_Variable_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.Symbols.Variable", Arcadia_VPL_Symbols_Variable,
                         u8"Arcadia.VPL.Symbols.Symbol", Arcadia_VPL_Symbols_Symbol,
                         &_typeOperations);

static void
Arcadia_VPL_Symbols_Variable_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Variable* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Symbols_Variable);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (4 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->name = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 4, _Arcadia_String_getType(thread));
  self->type = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 3, _Arcadia_VPL_Symbols_Symbol_getType(thread));
  self->enclosing = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_VPL_Symbols_Symbol_getType(thread));
  self->node = (Arcadia_VPL_Tree_Node*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_VPL_Tree_Node_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_VPL_Symbols_Variable);
}

static void
Arcadia_VPL_Symbols_Variable_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_VariableDispatch* self
  )
{
  ((Arcadia_VPL_Symbols_SymbolDispatch*)self)->getName = (Arcadia_String * (*)(Arcadia_Thread*, Arcadia_VPL_Symbols_Symbol*)) & Arcadia_VPL_Symbols_Variable_getNameImpl;
}

static void
Arcadia_VPL_Symbols_Variable_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Variable* self
  )
{
  if (self->name) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->name);
  }
  if (self->type) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->type);
  }
  if (self->enclosing) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->enclosing);
  }
  if (self->node) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->node);
  }
}

static Arcadia_String*
Arcadia_VPL_Symbols_Variable_getNameImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Variable* self
  )
{ return self->name; }

Arcadia_VPL_Symbols_Variable*
Arcadia_VPL_Symbols_Variable_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_VPL_Symbols_Symbol* type,
    Arcadia_VPL_Symbols_Symbol* enclosing,
    Arcadia_VPL_Tree_Node* node
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (name) Arcadia_ValueStack_pushObjectReferenceValue(thread, name); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (type) Arcadia_ValueStack_pushObjectReferenceValue(thread, type); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (enclosing) Arcadia_ValueStack_pushObjectReferenceValue(thread, enclosing); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (node) Arcadia_ValueStack_pushObjectReferenceValue(thread, node); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Symbols_Variable);
}
