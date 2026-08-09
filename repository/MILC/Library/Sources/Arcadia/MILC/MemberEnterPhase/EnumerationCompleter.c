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
#include "Arcadia/MILC/MemberEnterPhase/EnumerationCompleter.h"

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/Diagnostics/Include.h"
#include "Arcadia/MILC/Symbols/Include.h"
#include <assert.h>

static void
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleter* self
  );

static void
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleter* self
  );

static void
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleterDispatch* self
  );

static void
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleter* self
  );

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_visitImpl,

};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.MemberEnterPhase.EnumerationCompleter", Arcadia_MILC_MemberEnterPhase_EnumerationCompleter,
                         u8"Arcadia.MILC.Completer", Arcadia_MILC_Completer,
                         &_typeOperations);

static void
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleter* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_MemberEnterPhase_EnumerationCompleter);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_MemberEnterPhase_EnumerationCompleter);
}

static void
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleter* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleterDispatch* self
  )
{
  ((Arcadia_MILC_CompleterDispatch*)self)->complete = (void (*)(Arcadia_Thread*, Arcadia_MILC_Completer*, Arcadia_MILC_Context*, Arcadia_MILC_Symbol*)) & completeImpl;
}

static void
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleter* self
  )
{/*Intentionally empty.*/}

static Arcadia_String*
makeFullQualifiedName
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuilder* temporary,
    Arcadia_String* prefix,
    Arcadia_String* suffix
  )
{ 
  Arcadia_StringBuilder_clear(thread, temporary);
  Arcadia_StringBuilder_insertBackString(thread, temporary, prefix);
  Arcadia_StringBuilder_insertBackCxxString(thread, temporary, u8".");
  Arcadia_StringBuilder_insertBackString(thread, temporary, suffix);
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(temporary));

}

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_EnumerationCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  )
{ 
  assert(symbol->completer == (Arcadia_MILC_Completer*)self);
  Arcadia_MILC_AST_EnumerationDefinitionNode* node = ((Arcadia_MILC_EnumerationSymbol*)symbol)->ast;
  if (!node) {
    symbol->completer = NULL;
    return;
  }
  Arcadia_StringBuilder* temporary = Arcadia_StringBuilder_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)node->enumerationBody); i < n; ++i) {
    Arcadia_MILC_AST_EnumerationConstantDefinitionNode* childNode = (Arcadia_MILC_AST_EnumerationConstantDefinitionNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, node->enumerationBody, i, _Arcadia_MILC_AST_EnumerationConstantDefinitionNode_getType(thread));
    Arcadia_MILC_EnumerationConstantSymbol* childSymbol = Arcadia_MILC_EnumerationConstantSymbol_create(thread, makeFullQualifiedName(thread, temporary, symbol->name, childNode->name));
    ((Arcadia_MILC_Symbol*)childSymbol)->enclosing = (Arcadia_MILC_Symbol*)symbol;
    assert(((Arcadia_MILC_EnumerationSymbol*)symbol)->scope);
    childSymbol->ast = childNode;
    if (Arcadia_Languages_Scope_contains(thread, ((Arcadia_MILC_EnumerationSymbol*)symbol)->scope, ((Arcadia_MILC_Symbol*)childSymbol)->name, Arcadia_BooleanValue_True)) {
      Arcadia_Languages_Diagnostics_add
        (
          thread, context->diagnostics,
          (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
            (
              thread,
              Arcadia_Languages_DiagnosticType_Error,
              ((Arcadia_MILC_Symbol*)childSymbol)->name
            )
        );
    } else {
      Arcadia_Languages_Scope_enter(thread, ((Arcadia_MILC_EnumerationSymbol*)symbol)->scope, ((Arcadia_MILC_Symbol*)childSymbol)->name, (Arcadia_Object*)childSymbol);
    }
    // We add a diagnostic if the child node is missing an initializer. 
    if (!childNode->initializer) {
      Arcadia_Languages_Diagnostics_add
        (
          thread, context->diagnostics,
          (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_MissingInitializerDiagnostic_create
            (
              thread,
              Arcadia_Languages_DiagnosticType_Error,
              childSymbol
            )
        );
    }
  }
  symbol->completer = NULL;
}

Arcadia_MILC_MemberEnterPhase_EnumerationCompleter*
Arcadia_MILC_MemberEnterPhase_EnumerationCompleter_create
  (
    Arcadia_Thread* thread
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_MemberEnterPhase_EnumerationCompleter);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  _Arcadia_EndCreate(Arcadia_MILC_MemberEnterPhase_EnumerationCompleter);
}
