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

#if !defined(ARCADIA_VPL_TREEBUILDER_H_INCLUDED)
#define ARCADIA_VPL_TREEBUILDER_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia/VPL/Symbols/Include.h"

// read Arcadia_Object* pointers and put them into a list until a null pointer is reached.
static inline void
gather
  (
    Arcadia_Thread* thread,
    Arcadia_List* list,
    va_list arguments
  )
{
  Arcadia_Object* argument = va_arg(arguments, Arcadia_Object*);
  while (argument) {
    Arcadia_List_insertBackObjectReferenceValue(thread, list, argument);
    argument = va_arg(arguments, Arcadia_Object*);
  }
}

static inline Arcadia_VPL_Tree_Node*
TreeBuilder_callExpr1
(
  Arcadia_Thread* thread,
  Arcadia_VPL_Tree_Node* target,
  ...
) {
  va_list arguments;
  va_start(arguments, target);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_VPL_Tree_Node* tree = Arcadia_VPL_Tree_NodeFactory_makeCallExpr(thread, target);
    gather(thread, ((Arcadia_VPL_Tree_CallExprNode*)tree)->arguments, arguments);
    va_end(arguments);
    Arcadia_Thread_popJumpTarget(thread);
    return tree;
  } else {
    va_end(arguments);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

static inline Arcadia_List*
TreeBuilder_list1
(
  Arcadia_Thread* thread,
  ...
) {
  va_list elements;
  va_start(elements, thread);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_List* list = (Arcadia_List*)Arcadia_ArrayList_create(thread);
    gather(thread, list, elements);
    va_end(elements);
    Arcadia_Thread_popJumpTarget(thread);
    return list;
  } else {
    va_end(elements);
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

#define TreeBuilder_variableDefn(_type, _name) \
  Arcadia_VPL_Tree_NodeFactory_makeVariableDefn(thread, _name, _type)

#define TreeBuilder_assignmentExpr(_lhs, _rhs) \
  Arcadia_VPL_Tree_NodeFactory_makeAssignmentExpr(thread, _lhs, _rhs)

#define TreeBuilder_multiplyExpr(_lhs, _rhs) \
  Arcadia_VPL_Tree_NodeFactory_makeMultiplyExpr(thread, _lhs, _rhs)

#define TreeBuilder_divideExpr(_lhs, _rhs) \
  Arcadia_VPL_Tree_NodeFactory_makeDivideExpr(thread, _lhs, _rhs)

#define TreeBuilder_addExpr(_lhs, _rhs) \
  Arcadia_VPL_Tree_NodeFactory_makeAddExpr(thread, _lhs, _rhs)

#define TreeBuilder_subtractExpr(_lhs, _rhs) \
  Arcadia_VPL_Tree_NodeFactory_makeSubtractExpr(thread, _lhs, _rhs)

#define TreeBuilder_accessExpr(_lhs, _rhs) \
  Arcadia_VPL_Tree_NodeFactory_makeAccessExpr(thread, _lhs, _rhs)

#define TreeBuilder_realNumberExpr(_number) \
  Arcadia_VPL_Tree_NodeFactory_makeNumberExpr(thread, S(thread, _number))

#define TreeBuilder_callExpr(_target, ...) \
  TreeBuilder_callExpr1(thread, _target, __VA_ARGS__ __VA_OPT__(,) NULL)

#define TreeBuilder_statementList(...) \
  TreeBuilder_list1(thread, __VA_ARGS__ __VA_OPT__(,) NULL)

#define TreeBuilder_parameterList(...) \
  TreeBuilder_list1(thread, __VA_ARGS__ __VA_OPT__(,) NULL)

#define TreeBuilder_modifierList(...) \
  TreeBuilder_list1(thread, __VA_ARGS__ __VA_OPT__(,) NULL)

#define TreeBuilder_name(_name) \
  (Arcadia_VPL_Tree_Node*)Arcadia_VPL_Tree_NodeFactory_makeNameExpr(thread, S(thread, _name))

#define TreeBuilder_procedureDefn(_modifiers, _returnValueType, _name, _parameters, _body) \
  Arcadia_VPL_Tree_NodeFactory_makeProcedureDefn(thread, _modifiers, (Arcadia_VPL_Tree_NameExprNode*)_returnValueType, _name, _parameters, _body)

#endif // ARCADIA_VPL_TREEBUILDER_H_INCLUDED
