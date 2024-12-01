// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R/Types.h"
typedef struct R_Value R_Value;

typedef struct R_Object R_Object;
R_Type* \
_R_Object_getType
  (
  );

struct R_Object {
  int dummy;
};

// R(untime) ex(tension) macro.
#define Rex_declareObjectType(cilName, cName, cilParentName) \
  typedef struct cName cName; \
  R_Type* \
  _##cName##_getType \
    ( \
    );

// R(untime) ex(tension) macro.
// TODO: FIXME: If _getObjectType fails then _type is still null althought _registerObjectType was successful.
#define Rex_defineObjectType(cilName, cName, cilParentName, cParentName, cTypeOperations) \
  static R_Type* g_##cName##_type = NULL; \
  \
  static void \
  _##cName##_typeDestructing \
    ( \
      void *context \
    ) \
  { \
    g_##cName##_type = NULL; \
  } \
  \
  R_Type* \
  _##cName##_getType \
    ( \
    ) \
  { \
    if (!g_##cName##_type) { \
      R_Type* parentType = _##cParentName##_getType(); \
      R_registerObjectType(u8##cilName, sizeof(u8##cilName) - 1, sizeof(cName), parentType, cTypeOperations, &_##cName##_typeDestructing); \
      g_##cName##_type = R_getType(u8##cilName, sizeof(u8##cilName) - 1); \
    } \
    return g_##cName##_type; \
  }

void
R_Object_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
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
    R_Type* type,
    R_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

void
R_Object_setType
  (
    void* self,
    R_Type* type
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
    void* self
  );

/// @brief Decrement the lock count of the object.
/// @param self A pointer to the object.
void
R_Object_unlock
  (
    void* self
  );

/// @brief Get the type of an object.
/// @param self A pointer to the object.
/// @return The type of an object.
R_Type*
R_Object_getType
  (
    void* self
  );

R_SizeValue
R_Object_getHash
  (
    R_Object* self
  );

R_BooleanValue
R_Object_equalTo
  (
    R_Object* self,
    R_Value const* other
  );

R_BooleanValue
R_Object_notEqualTo
  (
    R_Object* self,
    R_Value const* other
  );

#endif // R_OBJECT_H_INCLUDED
