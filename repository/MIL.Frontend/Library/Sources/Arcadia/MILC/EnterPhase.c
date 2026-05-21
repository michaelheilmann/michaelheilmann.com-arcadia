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

#include "Arcadia/MILC/EnterPhase.h"

#include "Arcadia/MILC/Include.h"
#include <assert.h>

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self
  );

static void
Arcadia_MILC_EnterPhase_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhaseDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self
  );

static Arcadia_String*
onIdentifierNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_IdentifierNode* identifierNode
  );

static void
onClassDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_ClassDefinitionNode* classDefinitionNode
  );

static void
onModuleDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_ModuleDefinitionNode* moduleDefinitionNode
  );

static void
onEnumerationDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_EnumerationDefinitionNode* enumerationDefinitionNode
  );

static void
onProcedureDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_ProcedureDefinitionNode* procedureDefinitionNode
  );

static void
onCompilationUnitNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode
  );

static void
onEnterModuleNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_ModuleNode* moduleNode
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&visitImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&Arcadia_MILC_EnterPhase_initializeDispatchImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.EnterPhase", Arcadia_MILC_EnterPhase,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_EnterPhase);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (1 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->lastSymbol = NULL;
  self->deque = (Arcadia_Deque*)Arcadia_ArrayDeque_create(thread);
  self->context = (Arcadia_MILC_Context*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MILC_Context_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_MILC_EnterPhase);
}

static void
Arcadia_MILC_EnterPhase_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhaseDispatch* self
  )
{/*Intentionally empty.*/}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self
  )
{
  if (self->deque) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->deque);
  }
  if (self->lastSymbol) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->lastSymbol);
  }
  if (self->context) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->context);
  }
}

Arcadia_MILC_EnterPhase*
Arcadia_MILC_EnterPhase_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (context) Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)context); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_MILC_EnterPhase);
}

static Arcadia_String*
onIdentifierNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_IdentifierNode* identifierNode
  )
{
  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);
  Arcadia_String* name = (Arcadia_String*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, (Arcadia_List*)identifierNode->names, 0, _Arcadia_String_getType(thread));
  Arcadia_StringBuffer_insertBackString(thread, stringBuffer, name);
  for (Arcadia_SizeValue i = 1, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)identifierNode->names); i < n; ++i) {
    Arcadia_StringBuffer_insertBackCodePoint(thread, stringBuffer, '.');
    name = (Arcadia_String*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, (Arcadia_List*)identifierNode->names, i, _Arcadia_String_getType(thread));
    Arcadia_StringBuffer_insertBackString(thread, stringBuffer, name);
  }
  return Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(stringBuffer));
}

static void
onClassDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_ClassDefinitionNode* classDefinitionNode
  )
{ 
  Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode = ((Arcadia_MILC_AST_DefinitionNode*)classDefinitionNode)->compilationUnitNode;
  assert(NULL != compilationUnitNode);
  Arcadia_MILC_AST_ModuleNode* moduleNode = compilationUnitNode->moduleNode;
  assert(NULL != moduleNode);
  Arcadia_MILC_ModuleSymbol* moduleSymbol = moduleNode->moduleSymbol;
  assert(NULL != moduleSymbol);

  Arcadia_String* symbolName = onIdentifierNode(thread, self, classDefinitionNode->className);
  Arcadia_MILC_ClassSymbol* symbol = Arcadia_MILC_ClassSymbol_create(thread, symbolName);
  ((Arcadia_MILC_Symbol*)symbol)->enclosing = (Arcadia_MILC_Symbol*)moduleSymbol;
  if (!moduleSymbol->scope) {
    moduleSymbol->scope = Arcadia_Languages_Scope_create(thread, self->context->scope);
  }
  if (Arcadia_Languages_Scope_contains(thread, moduleSymbol->scope, symbolName, Arcadia_BooleanValue_False)) {
    Arcadia_Languages_Diagnostics_add
      (
        thread, self->context->diagnostics,
        (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
          (
            thread,
            Arcadia_Languages_DiagnosticType_Error,
            symbolName
          )
      );
  } else {
    Arcadia_Languages_Scope_enter(thread, moduleSymbol->scope, symbolName,  (Arcadia_Object*)symbol);
  }
}

static void
onModuleDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_ModuleDefinitionNode* moduleDefinitionNode
  )
{ 
  Arcadia_String* moduleSymbolName = onIdentifierNode(thread, self, moduleDefinitionNode->moduleName);
  // Get the compilation unit node.
  Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode = ((Arcadia_MILC_AST_DefinitionNode*)moduleDefinitionNode)->compilationUnitNode;
  assert(NULL != compilationUnitNode);
  // Get the module node.
  Arcadia_MILC_AST_ModuleNode* moduleNode = compilationUnitNode->moduleNode;
  assert(NULL != moduleNode);
  // Create the module symbol.
  Arcadia_MILC_ModuleSymbol* moduleSymbol = Arcadia_MILC_ModuleSymbol_create(thread, moduleSymbolName);
  // LANGUAGE DEFINITION: Assert no two definitions of the same name exist in the root scope.
  if (Arcadia_Languages_Scope_contains(thread, self->context->scope, moduleSymbolName, Arcadia_BooleanValue_False)) {
    Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create(thread, Arcadia_Languages_DiagnosticType_Error, moduleSymbolName);
  } else {
    Arcadia_Languages_Scope_enter(thread, self->context->scope, moduleSymbolName, (Arcadia_Object*)moduleSymbol);
  }
  if (self->lastSymbol) {
    // LANGUAGE DEFINITION: Assert not more than one module definition exists in a module.
    Arcadia_Languages_Diagnostics_add
      (
        thread,
        self->context->diagnostics,
        (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_MultipleModuleDefinitionsDiagnostic_create
          (
            thread,
            Arcadia_Languages_DiagnosticType_Error,
            moduleNode->moduleDirectoryPath
          )
      );
  }
  self->lastSymbol = moduleSymbol;
  // Associate the module symbolw ith this module node.
  moduleNode->moduleSymbol = moduleSymbol;
  // Associate te module definition node with the module symbol.
  moduleSymbol->moduleDefinitionNode = moduleDefinitionNode;
}

static void
onEnumerationDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_EnumerationDefinitionNode* enumerationDefinitionNode
  )
{ 
  Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode = ((Arcadia_MILC_AST_DefinitionNode*)enumerationDefinitionNode)->compilationUnitNode;
  assert(NULL != compilationUnitNode);
  Arcadia_MILC_AST_ModuleNode* moduleNode = compilationUnitNode->moduleNode;
  assert(NULL != moduleNode);
  Arcadia_MILC_ModuleSymbol* moduleSymbol = moduleNode->moduleSymbol;
  assert(NULL != moduleSymbol);

  Arcadia_String* symbolName = onIdentifierNode(thread, self, enumerationDefinitionNode->enumerationName);
  Arcadia_MILC_EnumerationSymbol* symbol = Arcadia_MILC_EnumerationSymbol_create(thread, symbolName);
  ((Arcadia_MILC_Symbol*)symbol)->enclosing = (Arcadia_MILC_Symbol*)moduleSymbol;
  if (!moduleSymbol->scope) {
    moduleSymbol->scope = Arcadia_Languages_Scope_create(thread, self->context->scope);
  }
  if (Arcadia_Languages_Scope_contains(thread, moduleSymbol->scope, symbolName, Arcadia_BooleanValue_False)) {
    Arcadia_Languages_Diagnostics_add
      (
        thread, self->context->diagnostics,
        (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
          (
            thread,
            Arcadia_Languages_DiagnosticType_Error,
            symbolName
          )
      );
  } else {
    Arcadia_Languages_Scope_enter(thread, moduleSymbol->scope, symbolName, (Arcadia_Object*)symbol);
  }
}

static void
onProcedureDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_ProcedureDefinitionNode* procedureDefinitionNode
  )
{ 
  Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode = ((Arcadia_MILC_AST_DefinitionNode*)procedureDefinitionNode)->compilationUnitNode;
  assert(NULL != compilationUnitNode);
  Arcadia_MILC_AST_ModuleNode* moduleNode = compilationUnitNode->moduleNode;
  assert(NULL != moduleNode);
  Arcadia_MILC_ModuleSymbol* moduleSymbol = moduleNode->moduleSymbol;
  assert(NULL != moduleSymbol);

  Arcadia_String* symbolName = onIdentifierNode(thread, self, procedureDefinitionNode->procedureName);
  Arcadia_MILC_ProcedureSymbol* symbol = Arcadia_MILC_ProcedureSymbol_create(thread, symbolName);
  ((Arcadia_MILC_Symbol*)symbol)->enclosing = (Arcadia_MILC_Symbol*)moduleSymbol;
  if (!moduleSymbol->scope) {
    moduleSymbol->scope = Arcadia_Languages_Scope_create(thread, self->context->scope);
  }
  if (Arcadia_Languages_Scope_contains(thread, moduleSymbol->scope, symbolName, Arcadia_BooleanValue_False)) {
    Arcadia_Languages_Diagnostics_add
      (
        thread, self->context->diagnostics,
        (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_SymbolAlreadyDefinedDiagnostic_create
          (
            thread,
            Arcadia_Languages_DiagnosticType_Error,
            symbolName
          )
      );
  } else {
    Arcadia_Languages_Scope_enter(thread, moduleSymbol->scope, symbolName, (Arcadia_Object*)symbol);
  }
}

static void
onDefinitionNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_DefinitionNode* definitionNode
  )
{
  if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)definitionNode, _Arcadia_MILC_AST_ModuleDefinitionNode_getType(thread))) {
    onModuleDefinitionNode(thread, self, (Arcadia_MILC_AST_ModuleDefinitionNode*)definitionNode);
  } else {
    Arcadia_Deque_insertBackObjectReferenceValue(thread, self->deque, (Arcadia_Object*)definitionNode);
  }
}

static void
onCompilationUnitNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)compilationUnitNode->definitions); i < n; ++i) {
    Arcadia_MILC_AST_DefinitionNode* definitionNode = (Arcadia_MILC_AST_DefinitionNode*)Arcadia_List_getObjectReferenceValueAt(thread, compilationUnitNode->definitions, i);
    onDefinitionNode(thread, self, definitionNode);
  }
}

static void
onEnterModuleNode
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self,
    Arcadia_MILC_AST_ModuleNode* moduleNode
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)moduleNode->compilationUnits); i < n; ++i) {
    Arcadia_MILC_AST_CompilationUnitNode* compilationUnitNode = (Arcadia_MILC_AST_CompilationUnitNode*)Arcadia_List_getObjectReferenceValueAt(thread, moduleNode->compilationUnits, i);
    onCompilationUnitNode(thread, self, compilationUnitNode);
  }
}

void
Arcadia_MILC_EnterPhase_run
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_EnterPhase* self
  )
{
  Arcadia_MILC_Context* context = self->context;
  if (!context->scope) {
    context->scope = Arcadia_Languages_Scope_create(thread, NULL);
  } else {
    Arcadia_Languages_Scope_clear(thread, context->scope);
  }
  // (1)
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self->context->moduleNodes); i < n; ++i) {
    self->lastSymbol = NULL;
    Arcadia_MILC_AST_ModuleNode* moduleNode = (Arcadia_MILC_AST_ModuleNode*)Arcadia_List_getObjectReferenceValueAt(thread, self->context->moduleNodes, i);
    onEnterModuleNode(thread, self, moduleNode);
    if (!self->lastSymbol) {
      // LANGUAGE DEFINITION: Assert at least one one module definition exists in a module.
      Arcadia_Languages_Diagnostics_add
        (
          thread,
          context->diagnostics,
          (Arcadia_Languages_Diagnostic*)Arcadia_MILC_Diagnostics_MissingModuleDefinitionDiagnostic_create
            (
              thread,
              Arcadia_Languages_DiagnosticType_Error,
              moduleNode->moduleDirectoryPath
            )
        );
    }
    self->lastSymbol = NULL;
  }
  // (3)
  while (!Arcadia_Collection_isEmpty(thread, (Arcadia_Collection*)self->deque)) {
    Arcadia_Value temporary = Arcadia_Deque_getFront(thread, self->deque);
    Arcadia_MILC_AST_DefinitionNode* definitionNode = (Arcadia_MILC_AST_DefinitionNode*)Arcadia_Value_getObjectReferenceValueChecked(thread, temporary, _Arcadia_MILC_AST_DefinitionNode_getType(thread));
    if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)definitionNode, _Arcadia_MILC_AST_ClassDefinitionNode_getType(thread))) {
      onClassDefinitionNode(thread, self, (Arcadia_MILC_AST_ClassDefinitionNode*)definitionNode);
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)definitionNode, _Arcadia_MILC_AST_EnumerationDefinitionNode_getType(thread))) {
      onEnumerationDefinitionNode(thread, self, (Arcadia_MILC_AST_EnumerationDefinitionNode*)definitionNode);
    } else if (Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)definitionNode, _Arcadia_MILC_AST_ProcedureDefinitionNode_getType(thread))) {
      onProcedureDefinitionNode(thread, self, (Arcadia_MILC_AST_ProcedureDefinitionNode*)definitionNode);
    } else {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Deque_removeFront(thread, self->deque);
  }
}
