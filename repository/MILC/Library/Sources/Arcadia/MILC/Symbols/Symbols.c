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

#include "Arcadia/MILC/Symbols/Symbols.h"

#include "Arcadia/MILC/Include.h"
#include "Arcadia/MILC/Environment.h"
#include <assert.h>

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_SymbolsDispatch* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self
  );

static const Arcadia_ObjectType_Operations _objectTypesOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypesOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.Symbols", Arcadia_MILC_Symbols,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Symbols);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }

  self->context = (Arcadia_MILC_Context*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MILC_Context_getType(thread));

  self->integer16 = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Integer16"));
  self->integer32 = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Integer32"));
  self->integer64 = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Integer64"));
  self->integer8  = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Integer8"));

  self->natural16 = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural16"));
  self->natural32 = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural32"));
  self->natural64 = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural64"));
  self->natural8  = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Natural8"));

  self->boolean = (Arcadia_MILC_Symbol*)Arcadia_MILC_PrimitiveTypeSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Boolean"));

  self->object = (Arcadia_MILC_Symbol*)Arcadia_MILC_ClassSymbol_create(thread, Arcadia_String_createFromCxxString(thread, u8"Arcadia.Object"));

  Arcadia_LeaveConstructor(Arcadia_MILC_Symbols);
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self
  )
{/*Intentionally empty.*/}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_SymbolsDispatch* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self
  )
{
  if (self->context) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->context);
  }

  if (self->integer16) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->integer16);
  }
  if  (self->integer32) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->integer32);
  }
  if (self->integer64) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->integer64);
  }
  if (self->integer8) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->integer8);
  }
  
  if (self->natural16) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->natural16);
  }
  if (self->natural32) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->natural32);
  }
  if (self->natural64) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->natural64);
  }
  if (self->natural8) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->natural8);
  }

  if (self->boolean) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->boolean);
  }

  if (self->object) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->object);
  }
}

Arcadia_MILC_Symbols*
Arcadia_MILC_Symbols_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  )
{ 
  _Arcadia_BeginCreate(Arcadia_MILC_Symbols);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)context);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  _Arcadia_EndCreate(Arcadia_MILC_Symbols);
}

Arcadia_MILC_Symbols*
Arcadia_MILC_Symbols_getInstance
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  )
{ 
  Arcadia_Value k = Arcadia_Value_makeTypeValue(_Arcadia_MILC_Symbols_getType(thread));
  Arcadia_Value v = Arcadia_Map_get(thread, context->instances, k);  
  if (Arcadia_Value_isVoidValue(&v)) {
    v = Arcadia_Value_makeObjectReferenceValue(Arcadia_MILC_Symbols_create(thread, context));
    Arcadia_Map_set(thread, context->instances, k, v, NULL, NULL);
  }
  return (Arcadia_MILC_Symbols*)Arcadia_Value_getObjectReferenceValue(&v);
}

Arcadia_MILC_Environment*
Arcadia_MILC_Symbols_getEnvironment
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self,
    Arcadia_MILC_Symbol* symbol
  )
{
  while (symbol && !Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)symbol, _Arcadia_MILC_ClassSymbol_getType(thread))) {
    symbol = symbol->enclosing;
  }
  if (!symbol) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_MILC_Environment* environment = (Arcadia_MILC_Environment*)Arcadia_Map_getObjectReferenceValueChecked(thread, self->context->environments, Arcadia_Value_makeObjectReferenceValue(symbol), _Arcadia_MILC_Environment_getType(thread));
  return environment;
}
