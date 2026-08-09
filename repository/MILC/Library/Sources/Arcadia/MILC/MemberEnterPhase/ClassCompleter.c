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
#include "Arcadia/MILC/MemberEnterPhase/ClassCompleter.h"

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/Diagnostics/Include.h"
#include "Arcadia/MILC/Symbols/Include.h"
#include "Arcadia/MILC/TypeResolutionPhase.h"
#include <assert.h>

static void
Arcadia_MILC_MemberEnterPhase_ClassCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self
  );

static void
Arcadia_MILC_MemberEnterPhase_ClassCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self
  );

static void
Arcadia_MILC_MemberEnterPhase_ClassCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleterDispatch* self
  );

static void
Arcadia_MILC_MemberEnterPhase_ClassCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self
  );

static void
onCompleteConstructor
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* classSymbol,
    Arcadia_MILC_AST_ConstructorDefinitionNode* node
  );

static void
onCompleteField
  ( 
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* classSymbol,
    Arcadia_MILC_AST_FieldDefinitionNode* node
  );

static void
onCompleteMethod
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* classSymbol,
    Arcadia_MILC_AST_MethodDefinitionNode* node
  );

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_MILC_MemberEnterPhase_ClassCompleter_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_MILC_MemberEnterPhase_ClassCompleter_destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_MemberEnterPhase_ClassCompleter_initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_MILC_MemberEnterPhase_ClassCompleter_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.MemberEnterPhase.ClassCompleter", Arcadia_MILC_MemberEnterPhase_ClassCompleter,
                         u8"Arcadia.MILC.Completer", Arcadia_MILC_Completer,
                         &_typeOperations);

static void
Arcadia_MILC_MemberEnterPhase_ClassCompleter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_MemberEnterPhase_ClassCompleter);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_MILC_MemberEnterPhase_ClassCompleter);
}

static void
Arcadia_MILC_MemberEnterPhase_ClassCompleter_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_MILC_MemberEnterPhase_ClassCompleter_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleterDispatch* self
  )
{
  ((Arcadia_MILC_CompleterDispatch*)self)->complete = (void (*)(Arcadia_Thread*, Arcadia_MILC_Completer*, Arcadia_MILC_Context*, Arcadia_MILC_Symbol*)) & completeImpl;
}

static void
Arcadia_MILC_MemberEnterPhase_ClassCompleter_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self
  )
{/*Intentionally empty.*/}

static void
onCompleteConstructor
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* classSymbol,
    Arcadia_MILC_AST_ConstructorDefinitionNode* node
  )
{ 
  Arcadia_String* name = Arcadia_String_createFromCxxString(thread, u8"<constructor>");
  // Enter the constructor symbol into the class symbol.
  Arcadia_MILC_ConstructorSymbol* constructorSymbol = Arcadia_MILC_ConstructorSymbol_create(thread, name);
  constructorSymbol->ast = node;
  Arcadia_List_insertBack(thread, ((Arcadia_MILC_ClassSymbol*)classSymbol)->members, Arcadia_Value_makeObjectReferenceValue((Arcadia_Object*)constructorSymbol));
  if (Arcadia_Languages_Scope_contains(thread, classSymbol->scope, ((Arcadia_MILC_Symbol*)constructorSymbol)->name, Arcadia_BooleanValue_False)) {
    Arcadia_Languages_Diagnostics_add
      (
        thread, context->diagnostics,
        (Arcadia_Languages_Diagnostic*)
        Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
          (
            thread,
            Arcadia_Languages_DiagnosticType_Error,
            name
          )
      );
  } else {
    Arcadia_Languages_Scope_enter(thread, classSymbol->scope, ((Arcadia_MILC_Symbol*)constructorSymbol)->name, (Arcadia_Object*)constructorSymbol);
  }
  // Enter the parameter symbols into the constructor symbol.
  if (!constructorSymbol->scope) {
    constructorSymbol->scope = Arcadia_Languages_Scope_create(thread, NULL);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)node->parameters); i < n; ++i) {
    Arcadia_MILC_AST_FieldDefinitionNode* fieldDefinitionNode = (Arcadia_MILC_AST_FieldDefinitionNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, node->parameters, i, _Arcadia_MILC_AST_FieldDefinitionNode_getType(thread));
    Arcadia_MILC_VariableSymbol* fieldSymbol = Arcadia_MILC_VariableSymbol_create(thread, fieldDefinitionNode->name);
    ((Arcadia_MILC_Symbol*)fieldSymbol)->enclosing = (Arcadia_MILC_Symbol*)constructorSymbol;
    fieldSymbol->ast = fieldDefinitionNode;
    Arcadia_List_insertBack(thread, ((Arcadia_MILC_ConstructorSymbol*)constructorSymbol)->parameters, Arcadia_Value_makeObjectReferenceValue((Arcadia_Object*)fieldSymbol));
    if (Arcadia_Languages_Scope_contains(thread, constructorSymbol->scope, ((Arcadia_MILC_Symbol*)fieldSymbol)->name, Arcadia_BooleanValue_False)) {
      Arcadia_Languages_Diagnostics_add
        (
          thread, context->diagnostics,
          (Arcadia_Languages_Diagnostic*)
          Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
            (
              thread,
              Arcadia_Languages_DiagnosticType_Error,
              fieldDefinitionNode->name
            )
        );
    } else {
      Arcadia_Languages_Scope_enter(thread, constructorSymbol->scope, ((Arcadia_MILC_Symbol*)fieldSymbol)->name, (Arcadia_Object*)fieldSymbol);
    }
  }
  // This is why we use completers (among other reasons). We cannot resolve a constructor's types here.
  ((Arcadia_MILC_Symbol*)constructorSymbol)->completer = Arcadia_MILC_TypeResolutionPhase_getInstance(thread, context)->constructorCompleter;
}

static void
onCompleteField
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* classSymbol,
    Arcadia_MILC_AST_FieldDefinitionNode* node
  )
{ 
  // Enter the field symbol into the class symbol.
  Arcadia_MILC_VariableSymbol* fieldSymbol = Arcadia_MILC_VariableSymbol_create(thread, node->name);
  ((Arcadia_MILC_Symbol*)fieldSymbol)->enclosing = (Arcadia_MILC_Symbol*)classSymbol;
  fieldSymbol->ast = node;
  Arcadia_List_insertBack(thread, ((Arcadia_MILC_ClassSymbol*)classSymbol)->members, Arcadia_Value_makeObjectReferenceValue((Arcadia_Object*)fieldSymbol));
  if (Arcadia_Languages_Scope_contains(thread, classSymbol->scope, ((Arcadia_MILC_Symbol*)fieldSymbol)->name, Arcadia_BooleanValue_False)) {
    Arcadia_Languages_Diagnostics_add
      (
        thread, context->diagnostics,
        (Arcadia_Languages_Diagnostic*)
        Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
          (
            thread,
            Arcadia_Languages_DiagnosticType_Error,
            node->name
          )
      );
  } else {
    Arcadia_Languages_Scope_enter(thread, classSymbol->scope, ((Arcadia_MILC_Symbol*)fieldSymbol)->name, (Arcadia_Object*)fieldSymbol);
  }
}

static void
onCompleteMethod
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_ClassSymbol* classSymbol,
    Arcadia_MILC_AST_MethodDefinitionNode* node
  )
{ 
  // Enter the method symbol into the class symbol.
  Arcadia_MILC_MethodSymbol* methodSymbol = Arcadia_MILC_MethodSymbol_create(thread, node->name);
  methodSymbol->ast = node;
  Arcadia_List_insertBack(thread, ((Arcadia_MILC_ClassSymbol*)classSymbol)->members, Arcadia_Value_makeObjectReferenceValue((Arcadia_Object*)methodSymbol));
  if (Arcadia_Languages_Scope_contains(thread, classSymbol->scope, ((Arcadia_MILC_Symbol*)methodSymbol)->name, Arcadia_BooleanValue_False)) {
    Arcadia_Languages_Diagnostics_add
      (
        thread, context->diagnostics,
        (Arcadia_Languages_Diagnostic*)
        Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
          (
            thread,
            Arcadia_Languages_DiagnosticType_Error,
            node->name
          )
      );
  } else {
    Arcadia_Languages_Scope_enter(thread, classSymbol->scope, ((Arcadia_MILC_Symbol*)methodSymbol)->name, (Arcadia_Object*)methodSymbol);
  }
  // Enter the parameter symbols into the method symbol.
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)node->parameters); i < n; ++i) {
    Arcadia_MILC_AST_FieldDefinitionNode* fieldDefinitionNode = (Arcadia_MILC_AST_FieldDefinitionNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, node->parameters, i, _Arcadia_MILC_AST_FieldDefinitionNode_getType(thread));
    Arcadia_MILC_VariableSymbol* fieldSymbol = Arcadia_MILC_VariableSymbol_create(thread, fieldDefinitionNode->name);
    ((Arcadia_MILC_Symbol*)fieldSymbol)->enclosing = (Arcadia_MILC_Symbol*)methodSymbol;
    fieldSymbol->ast = fieldDefinitionNode;
    Arcadia_List_insertBack(thread, ((Arcadia_MILC_ConstructorSymbol*)methodSymbol)->parameters, Arcadia_Value_makeObjectReferenceValue((Arcadia_Object*)fieldSymbol));
    if (Arcadia_Languages_Scope_contains(thread, methodSymbol->scope, ((Arcadia_MILC_Symbol*)fieldSymbol)->name, Arcadia_BooleanValue_False)) {
      Arcadia_Languages_Diagnostics_add
        (
          thread, context->diagnostics,
          (Arcadia_Languages_Diagnostic*)
          Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
            (
              thread,
              Arcadia_Languages_DiagnosticType_Error,
              fieldDefinitionNode->name
            )
        );
    } else {
      Arcadia_Languages_Scope_enter(thread, methodSymbol->scope, ((Arcadia_MILC_Symbol*)fieldSymbol)->name, (Arcadia_Object*)fieldSymbol);
    }
  }
  // This is why we use completers (among other reasons). We cannot resolve a methods types here.
  ((Arcadia_MILC_Symbol*)methodSymbol)->completer = Arcadia_MILC_TypeResolutionPhase_getInstance(thread, context)->methodCompleter;
}

static void
completeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_MemberEnterPhase_ClassCompleter* self,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  )
{ 
  assert(symbol->completer == (Arcadia_MILC_Completer*)self);
  Arcadia_MILC_AST_ClassDefinitionNode* node = ((Arcadia_MILC_ClassSymbol*)symbol)->ast;
  if (!node) {
    symbol->completer = NULL;
    return;
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)node->classBody); i < n; ++i) {
    Arcadia_MILC_AST_DefinitionNode* childNode = (Arcadia_MILC_AST_DefinitionNode*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, node->classBody, i, _Arcadia_MILC_AST_DefinitionNode_getType(thread));
    if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)childNode, _Arcadia_MILC_AST_ConstructorDefinitionNode_getType(thread))) {
      onCompleteConstructor(thread, self, context, (Arcadia_MILC_ClassSymbol*)symbol, (Arcadia_MILC_AST_ConstructorDefinitionNode*)childNode);
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)childNode, _Arcadia_MILC_AST_FieldDefinitionNode_getType(thread))) {
      onCompleteField(thread, self, context, (Arcadia_MILC_ClassSymbol*)symbol, (Arcadia_MILC_AST_FieldDefinitionNode*)childNode);
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)childNode, _Arcadia_MILC_AST_MethodDefinitionNode_getType(thread))) {
      onCompleteMethod(thread, self, context, (Arcadia_MILC_ClassSymbol*)symbol, (Arcadia_MILC_AST_MethodDefinitionNode*)childNode);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
  // This is for resolving the field types.
  symbol->completer = Arcadia_MILC_TypeResolutionPhase_getInstance(thread, context)->classCompleter;
}

Arcadia_MILC_MemberEnterPhase_ClassCompleter*
Arcadia_MILC_MemberEnterPhase_ClassCompleter_create
  (
    Arcadia_Thread* thread
  )
{ 
  _Arcadia_BeginCreate(Arcadia_MILC_MemberEnterPhase_ClassCompleter);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  _Arcadia_EndCreate(Arcadia_MILC_MemberEnterPhase_ClassCompleter);
}
