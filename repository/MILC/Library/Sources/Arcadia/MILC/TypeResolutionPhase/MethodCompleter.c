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
#include "Arcadia/MILC/TypeResolutionPhase/MethodCompleter.h"

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/Diagnostics/Include.h"
#include "Arcadia/MILC/Symbols/Include.h"
#include "Arcadia/MILC/Names.h"
#include "Arcadia/MILC/Environment.h"
#include "Arcadia/MILC/TypeResolutionPhase.h"
#include <assert.h>

static void
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleterDispatch* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self
  );

static void
onCompleteParameter
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_VariableSymbol* variableSymbol
  );

static void
onCompleteMethod
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_MethodSymbol* symbol
  );

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_MethodCompleter_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_MethodCompleter_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_MethodCompleter_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_MethodCompleter_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.TypeResolutionPhase.MethodCompleter", Arcadia_MILC_TypeResolutionPhase_MethodCompleter,
                         u8"Arcadia.MILC.Completer", Arcadia_MILC_Completer,
                         &_typeOperations);

static void
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_TypeResolutionPhase_MethodCompleter);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_TypeResolutionPhase_MethodCompleter);
}

static void
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleterDispatch* self
  )
{
  ((Arcadia_MILC_CompleterDispatch*)self)->complete = (void (*)(Arcadia_Thread*, Arcadia_MILC_Completer*, Arcadia_MILC_Context*, Arcadia_MILC_Symbol*)) & completeImpl;
}

static void
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self
  )
{/*Intentionally empty.*/}

static void
onCompleteParameter
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_VariableSymbol* variableSymbol
  )
{ 
  Arcadia_MILC_TypeResolutionPhase_resolveParameter(thread, Arcadia_MILC_TypeResolutionPhase_getInstance(thread, context), variableSymbol);
}

static void
onCompleteMethod
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_MethodSymbol* symbol
  )
{ 
  // Complete parameter types.
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)symbol->parameters); i < n; ++i) {
    Arcadia_MILC_VariableSymbol* parameter = (Arcadia_MILC_VariableSymbol*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, symbol->parameters, i, _Arcadia_MILC_VariableSymbol_getType(thread));
    onCompleteParameter(thread, self, context, parameter);
  }
#if 0
  // Complete return value type.
  Arcadia_MILC_TypeResolutionPhase_resolveReturnValue(thread, Arcadia_MILC_TypeResolutionPhase_getInstance(thread, context), symbol->ast->name);
#endif

  // Search for the method this method overrides if any.
  // We currently search 'by name'
  Arcadia_String* n = ((Arcadia_MILC_Symbol*)symbol)->name;
  Arcadia_MILC_ClassSymbol* p = (Arcadia_MILC_ClassSymbol*)((Arcadia_MILC_Symbol*)symbol)->enclosing;
  do {
    p = p->parentClassSymbol;
    Arcadia_MILC_Symbol* overrideOf = (Arcadia_MILC_Symbol*)Arcadia_Languages_Scope_lookup(thread, p->scope, n, Arcadia_BooleanValue_False);
    if (overrideOf) {
      if (overrideOf->kind != Arcadia_MILC_SymbolKind_Method) {
        Arcadia_MILC_Environment* e = Arcadia_MILC_Symbols_getEnvironment(thread, Arcadia_MILC_Symbols_getInstance(thread, context), (Arcadia_MILC_Symbol*)symbol);
        Arcadia_Languages_Diagnostics_add(thread, context->diagnostics, (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolIsNoMethodDiagnostic_create(thread, Arcadia_Languages_DiagnosticType_Error, overrideOf->name, e->compilationUnitNode->filePath));
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      symbol->overrideOf = (Arcadia_MILC_MethodSymbol*)overrideOf;
      break;
    }
  } while (NULL != p);
}

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_MethodCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  )
{ 
  assert(symbol->completer == (Arcadia_MILC_Completer*)self);
  onCompleteMethod(thread, self, context, (Arcadia_MILC_MethodSymbol*)symbol);
  symbol->completer = NULL;
}

Arcadia_MILC_TypeResolutionPhase_MethodCompleter*
Arcadia_MILC_TypeResolutionPhase_MethodCompleter_create
  (
    Arcadia_Thread* thread
  )
{ 
  _Arcadia_BeginCreate(Arcadia_MILC_TypeResolutionPhase_MethodCompleter);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  _Arcadia_EndCreate(Arcadia_MILC_TypeResolutionPhase_MethodCompleter);
}
