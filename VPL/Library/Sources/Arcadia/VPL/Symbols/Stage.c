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
#include "Arcadia/VPL/Symbols/Stage.h"

#include "Arcadia/VPL/Symbols/Program.h"

static void
Arcadia_VPL_Symbols_Stage_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Stage* self
  );

static void
Arcadia_VPL_Symbols_Stage_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_StageDispatch* self
  );

static void
Arcadia_VPL_Symbols_Stage_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Stage* self
  );

static void
Arcadia_VPL_Symbols_Stage_resolveTypesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Stage* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_Symbols_Stage_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_Symbols_Stage_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.Symbols.Stage", Arcadia_VPL_Symbols_Stage,
                         u8"Arcadia.VPL.Symbols.Symbol", Arcadia_VPL_Symbols_Symbol,
                         &_typeOperations);

static void
Arcadia_VPL_Symbols_Stage_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Stage* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_Symbols_Stage);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->program = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_VPL_Symbols_Program_getType(thread));
  self->flags = Arcadia_ValueStack_getNatural8Value(thread, 1);
  self->variableScalars = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  self->mainProcedure = NULL;
  self->scope = NULL;
  Arcadia_LeaveConstructor(Arcadia_VPL_Symbols_Stage);
}

static void
Arcadia_VPL_Symbols_Stage_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_StageDispatch* self
  )
{
  ((Arcadia_VPL_Symbols_SymbolDispatch*)self)->resolveTypes = (void (*)(Arcadia_Thread*, Arcadia_VPL_Symbols_Symbol*)) & Arcadia_VPL_Symbols_Stage_resolveTypesImpl;
}

static void
Arcadia_VPL_Symbols_Stage_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Stage* self
  )
{
  if (self->program) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->program);
  }
  if (self->variableScalars) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->variableScalars);
  }
  if (self->mainProcedure) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->mainProcedure);
  }
  if (self->scope) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->scope);
  }
}

static void
Arcadia_VPL_Symbols_Stage_resolveTypesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Stage* self
  )
{/*Intentionally empty.*/}

Arcadia_VPL_Symbols_Stage*
Arcadia_VPL_Symbols_Stage_create
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_Symbols_Program* program,
    Arcadia_Natural8Value flags
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (program) Arcadia_ValueStack_pushObjectReferenceValue(thread, program); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, flags);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_Symbols_Stage);
}
