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
#include "Arcadia/MILC/TypeResolutionPhase/ClassCompleter.h"

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/Diagnostics/Include.h"
#include "Arcadia/MILC/Symbols/Include.h"
#include "Arcadia/MILC/Names.h"
#include "Arcadia/MILC/Environment.h"
#include <assert.h>

static void
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleterDispatch* self
  );

static void
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self
  );

static Arcadia_MILC_Symbol*
getEnclosingClassSymbol
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbol* symbol,
    Arcadia_MILC_Context* context
  );

static void
onCompleteField
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_VariableSymbol* symbol
  );

static void
resolveParentClass
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* symbol
  );
 
static void
onCompleteParentClass
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* symbol
  );

static void
onCompleteClass
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* symbol
  );

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_ClassCompleter_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_ClassCompleter_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_ClassCompleter_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_TypeResolutionPhase_ClassCompleter_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.TypeResolutionPhase.ClassCompleter", Arcadia_MILC_TypeResolutionPhase_ClassCompleter,
                         u8"Arcadia.MILC.Completer", Arcadia_MILC_Completer,
                         &_typeOperations);

static void
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_TypeResolutionPhase_ClassCompleter);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->cycleCheck = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));
  Arcadia_LeaveConstructor(Arcadia_MILC_TypeResolutionPhase_ClassCompleter);
}

static void
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleterDispatch* self
  )
{
  ((Arcadia_MILC_CompleterDispatch*)self)->complete = (void (*)(Arcadia_Thread*, Arcadia_MILC_Completer*, Arcadia_MILC_Context*, Arcadia_MILC_Symbol*)) & completeImpl;
}

static void
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self
  )
{
  if (self->cycleCheck) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->cycleCheck);
  }
}

static Arcadia_MILC_Symbol*
getEnclosingClassSymbol
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbol* symbol,
    Arcadia_MILC_Context* context
  )
{
  while (symbol && !Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)symbol, _Arcadia_MILC_ClassSymbol_getType(thread))) {
    symbol = symbol->enclosing;
  }
  if (!symbol) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return symbol;
}

static void
onCompleteField
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_VariableSymbol* symbol
  )
{ 
  Arcadia_MILC_Symbol* moduleSymbol = (Arcadia_MILC_Symbol*)symbol;
  do {
    moduleSymbol = moduleSymbol->enclosing;
    assert(NULL != moduleSymbol);
  } while (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)moduleSymbol, _Arcadia_MILC_ModuleSymbol_getType(thread)));
  Arcadia_String* typeName = Arcadia_MILC_Names_toTypeName(thread, symbol->ast->type->names);
  Arcadia_MILC_Symbol* typeSymbol = (Arcadia_MILC_Symbol*)Arcadia_Languages_Scope_lookup(thread, ((Arcadia_MILC_ModuleSymbol*)moduleSymbol)->scope, typeName, Arcadia_BooleanValue_True);
  if (!typeSymbol) {
    Arcadia_MILC_ClassSymbol* classSymbol = (Arcadia_MILC_ClassSymbol*)getEnclosingClassSymbol(thread, (Arcadia_MILC_Symbol*)symbol, context);
    Arcadia_MILC_Environment* e = (Arcadia_MILC_Environment*)Arcadia_Map_getObjectReferenceValueChecked(thread, context->environments, Arcadia_Value_makeObjectReferenceValue(classSymbol), _Arcadia_MILC_Environment_getType(thread));
    Arcadia_Languages_Diagnostics_add(thread, context->diagnostics, (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic_create(thread, Arcadia_Languages_DiagnosticType_Error, typeName, e->compilationUnitNode->filePath));
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  symbol->type = typeSymbol;
}

static void
resolveParentClass
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* symbol
  )
{ 
  if ((Arcadia_MILC_Symbol*)symbol == Arcadia_MILC_Symbols_getInstance(thread, context)->object) {
    return;
  }
  if (NULL != symbol->parentClassSymbol) {
    return;
  }
  if (!symbol->ast->extendedClassName) {
    Arcadia_String* objectTypeName = Arcadia_String_createFromCxxString(thread, u8"Arcadia.Object");
    Arcadia_MILC_Symbol* objectSymbol = (Arcadia_MILC_Symbol*)Arcadia_Languages_Scope_lookup(thread, context->scope, objectTypeName, Arcadia_BooleanValue_True);
    if (!objectSymbol) {
      Arcadia_MILC_Environment* e = (Arcadia_MILC_Environment*)Arcadia_Map_getObjectReferenceValueChecked(thread, context->environments, Arcadia_Value_makeObjectReferenceValue(symbol), _Arcadia_MILC_Environment_getType(thread));
      Arcadia_Languages_Diagnostics_add(thread, context->diagnostics, (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic_create(thread, Arcadia_Languages_DiagnosticType_Error, objectTypeName, e->compilationUnitNode->filePath));
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    symbol->parentClassSymbol = (Arcadia_MILC_ClassSymbol*)objectSymbol;
  } else {
    Arcadia_MILC_Symbol* moduleSymbol = (Arcadia_MILC_Symbol*)symbol;
    do {
      moduleSymbol = moduleSymbol->enclosing;
      assert(NULL != moduleSymbol);
    } while (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)moduleSymbol, _Arcadia_MILC_ModuleSymbol_getType(thread)));
    Arcadia_String* extendedClassName = Arcadia_MILC_Names_toTypeName(thread, symbol->ast->extendedClassName->names);
    Arcadia_MILC_Symbol* parentClassSymbol = (Arcadia_MILC_Symbol*)Arcadia_Languages_Scope_lookup(thread, ((Arcadia_MILC_ModuleSymbol*)moduleSymbol)->scope, extendedClassName, Arcadia_BooleanValue_True);
    if (!parentClassSymbol) {
      Arcadia_MILC_Environment* e = (Arcadia_MILC_Environment*)Arcadia_Map_getObjectReferenceValueChecked(thread, context->environments, Arcadia_Value_makeObjectReferenceValue(symbol), _Arcadia_MILC_Environment_getType(thread));
      Arcadia_Languages_Diagnostics_add(thread, context->diagnostics, (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolNotDefinedDiagnostic_create(thread, Arcadia_Languages_DiagnosticType_Error, extendedClassName, e->compilationUnitNode->filePath));
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    } else if (parentClassSymbol->kind != Arcadia_MILC_SymbolKind_Class) {
      Arcadia_MILC_Environment* e = (Arcadia_MILC_Environment*)Arcadia_Map_getObjectReferenceValueChecked(thread, context->environments, Arcadia_Value_makeObjectReferenceValue(symbol), _Arcadia_MILC_Environment_getType(thread));
      Arcadia_Languages_Diagnostics_add(thread, context->diagnostics, (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolIsNoClassDiagnostic_create(thread, Arcadia_Languages_DiagnosticType_Error, extendedClassName, e->compilationUnitNode->filePath));
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
    symbol->parentClassSymbol = (Arcadia_MILC_ClassSymbol*)parentClassSymbol;
  }
}

static void
onCompleteParentClass
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* symbol
  )
{
  /* Recursively resolve ancestor classes and ensure there's no inheritance cycle. */
  Arcadia_Collection_clear(thread, (Arcadia_Collection*)self->cycleCheck);
  Arcadia_MILC_Symbol* p = (Arcadia_MILC_Symbol*)symbol;
  while (p) {
    Arcadia_Value value = Arcadia_Map_get(thread, self->cycleCheck, Arcadia_Value_makeObjectReferenceValue(p));
    if (!Arcadia_Value_isVoidValue(&value)) {
      Arcadia_MILC_Environment* e = (Arcadia_MILC_Environment*)Arcadia_Map_getObjectReferenceValueChecked(thread, context->environments, Arcadia_Value_makeObjectReferenceValue(symbol), _Arcadia_MILC_Environment_getType(thread));
      Arcadia_Languages_Diagnostics_add(thread, context->diagnostics, (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_CyclicInheritanceDiagnostic_create(thread, Arcadia_Languages_DiagnosticType_Error, ((Arcadia_MILC_Symbol*)symbol)->name, 
                                                                                                                                                                         e->compilationUnitNode->filePath));
    }
    Arcadia_Map_set(thread, self->cycleCheck, Arcadia_Value_makeObjectReferenceValue(p), Arcadia_Value_makeObjectReferenceValue(p), NULL, NULL);
    resolveParentClass(thread, self, context, (Arcadia_MILC_ClassSymbol*)p); /* Ensure the parent class is resolved. */
    p = (Arcadia_MILC_Symbol*)((Arcadia_MILC_ClassSymbol*)p)->parentClassSymbol;
  }
}

static void
onCompleteClass
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* symbol
  )
{
  onCompleteParentClass(thread, self, context, symbol);
  Arcadia_List* symbols = Arcadia_Map_getValues(thread, symbol->scope->entries);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)symbols); i < n; ++i) {
    Arcadia_MILC_Symbol* childSymbol = (Arcadia_MILC_Symbol*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, symbols, i, _Arcadia_MILC_Symbol_getType(thread));
    if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)childSymbol, _Arcadia_MILC_VariableSymbol_getType(thread))) {
      onCompleteField(thread, self, context, (Arcadia_MILC_VariableSymbol*)childSymbol);
    }
  }
}

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_TypeResolutionPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  )
{ 
  assert(symbol->completer == (Arcadia_MILC_Completer*)self);
  onCompleteClass(thread, self, context, (Arcadia_MILC_ClassSymbol*)symbol);
  symbol->completer = NULL;
}

Arcadia_MILC_TypeResolutionPhase_ClassCompleter*
Arcadia_MILC_TypeResolutionPhase_ClassCompleter_create
  (
    Arcadia_Thread* thread
  )
{ 
  _Arcadia_BeginCreate(Arcadia_MILC_TypeResolutionPhase_ClassCompleter);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  _Arcadia_EndCreate(Arcadia_MILC_TypeResolutionPhase_ClassCompleter);
}
