// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-08-27

#if !defined(R_OBJECT_H_INCLUDED)
#define R_OBJECT_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Types.h"
typedef struct R_String R_String;
typedef struct R_Value R_Value;


typedef struct R_Object R_Object;
Arcadia_TypeValue
_R_Object_getType
  (
    Arcadia_Process* process
  );

struct R_Object {
  int dummy;
};

#define Rex_superTypeConstructor(_process, _type, ...) \
  Arcadia_Type_getOperations(Arcadia_Type_getParentObjectType(_type))->objectTypeOperations->construct(_process, __VA_ARGS__)

/// R(untime) ex(tension) macro.
/// @param _cilName, _cilParentName UTF8 string literals for the Common Intermediate Language type names of the type and its parent type.
#define Rex_declareObjectType(_cilName, _cName, _cilParentName) \
  typedef struct _cName _cName; \
  Arcadia_TypeValue \
  _##_cName##_getType \
    ( \
      Arcadia_Process* process \
    );

/// R(untime) ex(tension) macro.
/// @param _cilName, _cilParentName UTF8 string literals for the Common Intermediate Language type names of the type and its parent type.
#define Rex_defineObjectType(_cilName, _cName, _cilParentName, _cParentName, _cTypeOperations) \
  static Arcadia_TypeValue g_##_cName##_type = NULL; \
  \
  static void \
  _##_cName##_typeDestructing \
    ( \
      void *context \
    ) \
  { \
    g_##_cName##_type = NULL; \
  } \
  \
  Arcadia_TypeValue \
  _##_cName##_getType \
    ( \
      Arcadia_Process* process \
    ) \
  { \
    if (!g_##_cName##_type) { \
      Arcadia_TypeValue parentType = _##_cParentName##_getType(process); \
      g_##_cName##_type = R_registerObjectType(process, _cilName, sizeof(_cilName) - 1, sizeof(_cName), parentType, _cTypeOperations, &_##_cName##_typeDestructing); \
    } \
    return g_##_cName##_type; \
  }

/// @todo Make static.
void
R_Object_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

/*
 * @brief Allocate a "Core.Object" or derived type value.
 * Allocate a "Core.Object" value of the specified "Core.Object" or derived type "type".
 * This operation performs the following actions:
 * a) allocate memory of size "Core.Type.getValueSize(type)" at address "a".
 * b) ensure each field denoted by "type" and all its ancestor types is initialized to the default value "void".
 * c) the type of the object is "type" such that "Core.Object.getType(a)" returns "type".
 *
 * All fields of T and all its ancestor types are initialized to the default value "void".
 * @error Core.Status.ArgumentValueInvalid if "type" is "NULL"
 * @error Core.Status.AllocationFailed if step a) fails
 */
void*
R_allocateObject
  (
    Arcadia_Process* process,
    Arcadia_TypeValue type,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

void
R_Object_setType
  (
    void* self,
    Arcadia_TypeValue type
  );

/// @brief Visit an object.
/// @param self A pointer to the object.
void
R_Object_visit
  (
    void* self
  );

/// @brief Increment the lock count of the object.
/// @param self A pointer to the object.
void
R_Object_lock
  (
    Arcadia_Process* process,
    void* self
  );

/// @brief Decrement the lock count of the object.
/// @param self A pointer to the object.
void
R_Object_unlock
  (
    Arcadia_Process* process,
    void* self
  );

/// @brief Get the type of an object.
/// @param self A pointer to the object.
/// @return The type of an object.
Arcadia_TypeValue
R_Object_getType
  (
    void* self
  );

Arcadia_SizeValue
R_Object_hash
  (
    Arcadia_Process* process,
    R_Object* self
  );

R_Object*
R_Object_add
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  );

R_Object*
R_Object_subtract
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  );

Arcadia_BooleanValue
R_Object_equalTo
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  );

Arcadia_BooleanValue
R_Object_greaterThan
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  );

Arcadia_BooleanValue
R_Object_greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  );

Arcadia_BooleanValue
R_Object_lowerThan
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  );

Arcadia_BooleanValue
R_Object_lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  );

Arcadia_BooleanValue
R_Object_notEqualTo
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  );

R_String*
R_Object_toString
  (
    Arcadia_Process* process,
    R_Object* self
  );

#endif // R_OBJECT_H_INCLUDED
