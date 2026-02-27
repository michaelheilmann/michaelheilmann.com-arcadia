#define ARCADIA_VPL_PRIVATE (1)
#include "Arcadia/VPL/SemanticalAnalysis.h"

#include "Arcadia/VPL/Symbols/BuiltinType.h"
#include "Arcadia/VPL/Program.h"
#include "Arcadia/VPL/Symbols/Constant.h"
#include "Arcadia/VPL/Symbols/ConstantRecord.h"
#include "Arcadia/VPL/Symbols/ConstantRecordField.h"
#include "Arcadia/VPL/Symbols/ConstantScalar.h"
#include "Arcadia/VPL/Symbols/Scalar.h"

static void
Arcadia_VPL_SemanticalAnalysis_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self
  );

static void
Arcadia_VPL_SemanticalAnalysis_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysisDispatch* self
  );

static void
Arcadia_VPL_SemanticalAnalysis_visit
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self
  );

static void
Arcadia_VPL_SemanticalAnalysis_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self
  );

static void
conflictingDefinitionError
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_Program* program
  );

static Arcadia_Languages_Scope*
createProgramScope
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_Program* program
  );

static void
onConstantRecordField
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_ConstantRecordField* constantRecordField,
    Arcadia_VPL_Program* program
  );

static void
onConstantRecord
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_ConstantRecord* constantRecord,
    Arcadia_VPL_Program* program
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_VPL_SemanticalAnalysis_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_VPL_SemanticalAnalysis_destruct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_VPL_SemanticalAnalysis_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.VPL.SemanticalAnalysis", Arcadia_VPL_SemanticalAnalysis,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_VPL_SemanticalAnalysis_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self
  )
{
  Arcadia_EnterConstructor(Arcadia_VPL_SemanticalAnalysis);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (0 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_LeaveConstructor(Arcadia_VPL_SemanticalAnalysis);
}

static void
Arcadia_VPL_SemanticalAnalysis_initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysisDispatch* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_VPL_SemanticalAnalysis_visit
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_VPL_SemanticalAnalysis_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self
  )
{/*Intentionally empty.*/}

Arcadia_VPL_SemanticalAnalysis*
Arcadia_VPL_SemanticalAnalysis_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushNatural8Value(thread, 0);
  ARCADIA_CREATEOBJECT(Arcadia_VPL_SemanticalAnalysis);
}

static void
conflictingDefinitionError
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_Program* program
  )
{
  /*@todo Add and use exceptions. The concept is already in Arcadia.Ring2 and Arcadia.Languages but it was not yet used so far.*/
  Arcadia_logf(Arcadia_LogFlags_Error, "conflicting definition\n");
  Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
  Arcadia_Thread_jump(thread);
}

static Arcadia_Languages_Scope*
createProgramScope
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_Program* program
  )
{
  Arcadia_Languages_Scope* scope = Arcadia_Languages_Scope_create(thread, NULL);

  if (!Arcadia_Languages_Scope_enter(thread, scope, program->MAT4->name, (Arcadia_Object*)program->MAT4)) {
    conflictingDefinitionError(thread, self, program);
  }
  if (!Arcadia_Languages_Scope_enter(thread, scope, program->SAMPLER2D->name, (Arcadia_Object*)program->SAMPLER2D)) {
    conflictingDefinitionError(thread, self, program);
  }
  if (!Arcadia_Languages_Scope_enter(thread, scope, program->VEC2->name, (Arcadia_Object*)program->VEC2)) {
    conflictingDefinitionError(thread, self, program);
  }
  if (!Arcadia_Languages_Scope_enter(thread, scope, program->VEC3->name, (Arcadia_Object*)program->VEC3)) {
    conflictingDefinitionError(thread, self, program);
  }
  if (!Arcadia_Languages_Scope_enter(thread, scope, program->VEC4->name, (Arcadia_Object*)program->VEC4)) {
    conflictingDefinitionError(thread, self, program);
  }

  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->variableScalars); i < n; ++i) {
    Arcadia_VPL_VariableScalar* variableScalar =
      (Arcadia_VPL_VariableScalar*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->variableScalars, i,
        _Arcadia_VPL_VariableScalar_getType(thread));
    if (!Arcadia_Languages_Scope_enter(thread, scope, variableScalar->name, (Arcadia_Object*)variableScalar)) {
      conflictingDefinitionError(thread, self, program);
    }
  }

  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->constants); i < n; ++i) {
    Arcadia_VPL_Constant* constant =
      (Arcadia_VPL_Constant*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->constants, i,
        _Arcadia_VPL_Constant_getType(thread));
    if (!Arcadia_Languages_Scope_enter(thread, scope, Arcadia_VPL_Constant_getName(thread, constant), (Arcadia_Object*)constant)) {
      conflictingDefinitionError(thread, self, program);
    }
  }

  return scope;
}

static void
onConstantRecordField
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_ConstantRecordField* constantRecordField,
    Arcadia_VPL_Program* program
  )
{ 

}

static void
onConstantRecord
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_ConstantRecord* constantRecord,
    Arcadia_VPL_Program* program
  )
{
  if (!constantRecord->scope) {
    constantRecord->scope = Arcadia_Languages_Scope_create(thread, program->scope);
  }
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)constantRecord->fields); i < n; ++i) {
    Arcadia_VPL_ConstantRecordField* constantRecordField = (Arcadia_VPL_ConstantRecordField*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, constantRecord->fields, i, _Arcadia_VPL_ConstantRecordField_getType(thread));
    onConstantRecordField(thread, self, constantRecordField, program);
  }
}

void
Arcadia_VPL_SemanticalAnalysis_run
  (
    Arcadia_Thread* thread,
    Arcadia_VPL_SemanticalAnalysis* self,
    Arcadia_VPL_Program* program
  )
{
  // Create the program scope if it does not exist yet.
  if (!program->scope) {
    program->scope = createProgramScope(thread, self, program);
  }
  // Create the constant record scopes.
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)program->constants); i < n; ++i) {
    Arcadia_VPL_Constant* constant = (Arcadia_VPL_Constant*)Arcadia_List_getObjectReferenceValueCheckedAt(thread, program->constants, i, _Arcadia_VPL_Constant_getType(thread));
    if (Arcadia_VPL_Constant_getKind(thread, constant) == Arcadia_VPL_ConstantKind_Record) {
      onConstantRecord(thread, self, (Arcadia_VPL_ConstantRecord*)constant, program);
    }
  }
}
