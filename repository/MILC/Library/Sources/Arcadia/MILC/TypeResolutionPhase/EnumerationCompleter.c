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

#define ARCADIA_MILC_PRIVATE (1)
#include "Arcadia/MILC/TypeResolutionPhase/EnumerationCompleter.h"

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/Diagnostics/Include.h"
#include "Arcadia/MILC/Symbols/Include.h"
#include <assert.h>

static void
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleterDispatch* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self
  );

static void
onCompleteVariable
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_VariableSymbol* symbol
  );

static void
onCompleteEnumeration
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_EnumerationSymbol* symbol
  );

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.TypeResolutionPhase.EnumerationCompleter", Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter,
                         u8"Arcadia.MILC.Completer", Arcadia_MILC_Completer,
                         &_typeOperations);

static void
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter);
}

static void
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleterDispatch* self
  )
{
  ((Arcadia_MILC_CompleterDispatch*)self)->complete = (void (*)(Arcadia_Thread*, Arcadia_MILC_Completer*, Arcadia_MILC_Context*, Arcadia_MILC_Symbol*)) & completeImpl;
}

static void
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self
  )
{/*Intentionally empty.*/}

static void
onCompleteEnumerationConstant
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_EnumerationConstantSymbol* symbol
  )
{ 
  Arcadia_MILC_AST_EnumerationConstantDefinitionNode* node = symbol->ast;
  if (!node) {
    return;
  }
  Arcadia_MILC_AST_IntegerLiteralNode* initializer = node->initializer;
  if (!initializer) {
    // A diagnostic was already added by the member enter phase.
    return;
  }
  Arcadia_MILC_Symbols* symbols = Arcadia_MILC_Symbols_getInstance(thread, context);
  // Determine the value of the integer literal.
  Arcadia_BooleanValue overflow = Arcadia_BooleanValue_False;
  Arcadia_Natural64Value value = 0;
  Arcadia_UnicodeCodePointReader* reader = (Arcadia_UnicodeCodePointReader*)Arcadia_ByteReader_UnicodeCodePointReader_create(thread, (Arcadia_ByteReader*)Arcadia_String_ByteReader_create(thread, initializer->value));
  while (Arcadia_UnicodeCodePointReader_hasValue(thread, reader)) {
    Arcadia_Natural32Value codePoint = Arcadia_UnicodeCodePointReader_getValue(thread, reader);
    Arcadia_UnicodeCodePointReader_nextValue(thread, reader);
    if (codePoint < (Arcadia_Natural32Value)'0' || codePoint >(Arcadia_Natural32Value)'9') {
      overflow = Arcadia_BooleanValue_True;
      break;
    }
    Arcadia_Natural64Value digit = (Arcadia_Natural64Value)(codePoint - (Arcadia_Natural32Value)'0');
    if (value > (Arcadia_Natural64Value_Maximum - digit) / 10) {
      overflow = Arcadia_BooleanValue_True;
      break;
    }
    value = value * 10 + digit;
  }
  if (overflow) {
    Arcadia_Languages_Diagnostics_add
      (
        thread,
        context->diagnostics,
        (Arcadia_Languages_Diagnostic*)
        Arcadia_MILC_Diagnostics_IntegerLiteralOutOfRangeDiagnostic_create
          (
            thread,
            Arcadia_Languages_DiagnosticType_Error,
            symbol,
            initializer->value
          )
      );
    return;
  }
  // LANGUAGE DEFINITION: The type of an integer literal is the first of
  // Arcadia.Natural8, Arcadia.Natural16, Arcadia.Natural32, and Arcadia.Natural64
  // which is able to represent its value.
  if (value <= (Arcadia_Natural64Value)Arcadia_Natural8Value_Maximum) {
    initializer->type = symbols->natural8;
  } else if (value <= (Arcadia_Natural64Value)Arcadia_Natural16Value_Maximum) {
    initializer->type = symbols->natural16;
  } else if (value <= (Arcadia_Natural64Value)Arcadia_Natural32Value_Maximum) {
    initializer->type = symbols->natural32;
  } else {
    initializer->type = symbols->natural64;
  }
}

static void
onCompleteEnumeration
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_EnumerationSymbol* symbol
  )
{
  Arcadia_MILC_EnumerationSymbol* enumerationSymbol = (Arcadia_MILC_EnumerationSymbol*)symbol;
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)enumerationSymbol->members); i < n; ++i) {
    Arcadia_MILC_EnumerationConstantSymbol* enumerationConstantSymbol =
      (Arcadia_MILC_EnumerationConstantSymbol*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, enumerationSymbol->members, i, _Arcadia_MILC_EnumerationConstantSymbol_getType(thread));
    onCompleteEnumerationConstant(thread, self, context, enumerationConstantSymbol);
  }
}

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  )
{ 
  assert(symbol->completer == (Arcadia_MILC_Completer*)self);
  onCompleteEnumeration(thread, self, context, (Arcadia_MILC_EnumerationSymbol*)symbol);
  symbol->completer = NULL;
}

Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter*
Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter_create
  (
    Arcadia_Thread* thread
  )
{ 
  _Arcadia_BeginCreate(Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  _Arcadia_EndCreate(Arcadia_MILC_TypeResolutionPhase_EnumerationCompleter);
}
