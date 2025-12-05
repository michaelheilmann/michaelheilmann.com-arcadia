// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_EXTENSIONS_H_INCLUDED)
#define ARCADIA_EXTENSIONS_H_INCLUDED

#include "Arcadia/DDL/Include.h"
#include "Arcadia/DDLS/Include.h"

/**
 * @brief
 * Get if a is an object value of the specified type.
 * @param thread
 * A pointer to this thread.
 * @param self
 * The value.
 * @param type
 * A pointer to a type.
 * @return
 * A pointer to the object value.
 */
static inline Arcadia_Object*
Arcadia_Value_getObjectReferenceValueChecked
  (
    Arcadia_Thread* thread,
    Arcadia_Value self,
    Arcadia_Type* type
  )
{
  if (!Arcadia_Value_isObjectReferenceValue(&self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&self);
  if (type && !Arcadia_Object_isInstanceOf(thread, object, type)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  return object;
}

/**
 * @brief
 * Get if a node is a boolean node.
 * @param thread
 * A pointer to this thread.
 * @param node
 * A pointer to a node.
 * @return
 * #Arcadia_BooleanValue_True if the node is a boolean node.
 * #Arcadia_BooleanValue_alse otherwise.
 */
static inline Arcadia_BooleanValue
Arcadia_DDL_Node_isBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* node
  )
{
  return
    Arcadia_Object_isInstanceOf
      (
        thread,
        (Arcadia_Object*)node,
        _Arcadia_DDL_BooleanNode_getType(thread)
      );
}

/**
 * @brief
 * Get if a node is a list node.
 * @param thread
 * A pointer to this thread.
 * @param node
 * A pointer to a node.
 * @return
 * #Arcadia_BooleanValue_True if the node is a list node.
 * #Arcadia_BooleanValue_alse otherwise.
 */
static inline Arcadia_BooleanValue
Arcadia_DDL_Node_isList
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* node
  )
{
  return
    Arcadia_Object_isInstanceOf
      (
        thread,
        (Arcadia_Object*)node,
        _Arcadia_DDL_ListNode_getType(thread)
      );
}

/**
 * @brief
 * Get if a node is a map node.
 * @param thread
 * A pointer to this thread.
 * @param node
 * A pointer to a node.
 * @return
 * #Arcadia_BooleanValue_True if the node is a map node.
 * #Arcadia_BooleanValue_alse otherwise.
 */
static inline Arcadia_BooleanValue
Arcadia_DDL_Node_isMap
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* node
  )
{
  return
    Arcadia_Object_isInstanceOf
      (
        thread,
        (Arcadia_Object*)node,
        _Arcadia_DDL_MapNode_getType(thread)
      );
}

/**
 * @brief
 * Get if a node is a name node.
 * @param thread
 * A pointer to this thread.
 * @param node
 * A pointer to a node.
 * @return
 * #Arcadia_BooleanValue_True if the node is a name node.
 * #Arcadia_BooleanValue_alse otherwise.
 */
static inline Arcadia_BooleanValue
Arcadia_DDL_Node_isName
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* node
  )
{
  return
    Arcadia_Object_isInstanceOf
    (
      thread,
      (Arcadia_Object*)node,
      _Arcadia_DDL_NameNode_getType(thread)
    );
}

/**
 * @brief
 * Get if a node is a number node.
 * @param thread
 * A pointer to this thread.
 * @param node
 * A pointer to a node.
 * @return
 * #Arcadia_BooleanValue_True if the node is a number node.
 * #Arcadia_BooleanValue_alse otherwise.
 */
static inline Arcadia_BooleanValue
Arcadia_DDL_Node_isNumber
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* node
  )
{
  return
    Arcadia_Object_isInstanceOf
      (
        thread,
        (Arcadia_Object*)node,
        _Arcadia_DDL_NumberNode_getType(thread)
      );
}

/**
 * @brief
 * Get if a node is a string node.
 * @param thread
 * A pointer to this thread.
 * @param node
 * A pointer to a node.
 * @return
 * #Arcadia_BooleanValue_True if the node is a string node.
 * #Arcadia_BooleanValue_alse otherwise.
 */
static inline Arcadia_BooleanValue
Arcadia_DDL_Node_isString
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* node
  )
{
  return
    Arcadia_Object_isInstanceOf
      (
        thread,
        (Arcadia_Object*)node,
        _Arcadia_DDL_StringNode_getType(thread)
      );
}

/**
 * @brief
 * Get if a node is a void node.
 * @param thread
 * A pointer to this thread.
 * @param node
 * A pointer to a node.
 * @return
 * #Arcadia_BooleanValue_True if the node is a void node.
 * #Arcadia_BooleanValue_alse otherwise.
 */
static inline Arcadia_BooleanValue
Arcadia_DDL_Node_isVoid
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* node
  )
{
  return
    Arcadia_Object_isInstanceOf
      (
        thread,
        (Arcadia_Object*)node,
        _Arcadia_DDL_VoidNode_getType(thread)
      );
}

static inline Arcadia_BooleanValue
Arcadia_DDLS_isAny
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{
  return Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_AnyNode_getType(thread));
}

static inline Arcadia_BooleanValue
Arcadia_DDLS_isBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_ScalarNode_getType(thread)))
  { return Arcadia_BooleanValue_False; }
  return Arcadia_String_isEqualTo_pn(thread, ((Arcadia_DDLS_ScalarNode*)ddlsNode)->name, u8"Boolean", sizeof(u8"Boolean") - 1);
}

static inline Arcadia_BooleanValue
Arcadia_DDLS_isNumber
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_ScalarNode_getType(thread)))     {
  return Arcadia_BooleanValue_False; }
  return Arcadia_String_isEqualTo_pn(thread, ((Arcadia_DDLS_ScalarNode*)ddlsNode)->name, u8"Number", sizeof(u8"Number") - 1);
}

static inline Arcadia_BooleanValue
Arcadia_DDLS_isSchema
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{ return Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_SchemaNode_getType(thread)); }

static inline Arcadia_BooleanValue
Arcadia_DDLS_isSchemaReference
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{ return Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_SchemaReferenceNode_getType(thread)); }

static inline Arcadia_BooleanValue
Arcadia_DDLS_isString
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_ScalarNode_getType(thread)))
  { return Arcadia_BooleanValue_False; }
  return Arcadia_String_isEqualTo_pn(thread, ((Arcadia_DDLS_ScalarNode*)ddlsNode)->name, u8"String", sizeof(u8"String") - 1);
}

static inline Arcadia_BooleanValue
Arcadia_DDLS_isVoid
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_ScalarNode_getType(thread)))
  { return Arcadia_BooleanValue_False; }
  return Arcadia_String_isEqualTo_pn(thread, ((Arcadia_DDLS_ScalarNode*)ddlsNode)->name, u8"Boolean", sizeof(u8"Boolean") - 1);
}

static inline Arcadia_BooleanValue
Arcadia_DDLS_isList
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{ return Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_ListNode_getType(thread)); }

static inline Arcadia_BooleanValue
Arcadia_DDLS_isMap
  (
    Arcadia_Thread* thread,
    Arcadia_DDLS_Node* ddlsNode
  )
{ return Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_MapNode_getType(thread)); }

#endif // ARCADIA_EXTENSIONS_H_INCLUDED
