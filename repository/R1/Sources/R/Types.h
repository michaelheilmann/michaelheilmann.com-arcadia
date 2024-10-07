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

// Last modified: 2024-09-22

#if !defined(R_TYPES_H_INCLUDED)
#define R_TYPES_H_INCLUDED

#include "R/Configure.h"
#include "R/Boolean.h"
#include "R/Size.h"

/// @brief Type of a visti callback function.
/// Each object type may have its own visit callback function.
/// For an object of type A1 <: A2 <: ... <: An the callback functions are invoked from the bottom most to the top most type.
typedef void (R_Type_VisitObjectCallbackFunction)(void *);

/// @brief Type of a destruct callback function.
/// Each object type may have its own destruct callback function.
/// For an object of type A1 <: A2 <: ... <: An the callback functions are invoked from the bottom most to the top most type.
typedef void (R_Type_DestructObjectCallbackFunction)(void*);

/// @brief Type of a type destructing callback function.
/// Invoked when the type is destructing.
typedef void (R_Type_TypeDestructingCallbackFunction)(void*);

typedef void R_Type;

/// An enumeration of the type kinds.
typedef enum R_TypeKind {

  /// The boolean type kind.
  /// <code>R.Boolean</code> is of this type.
  R_TypeKind_Boolean,

  /// The integer type kind.
  /// <code>R.Integer(8|16|32|64)</code> are examples for this type kind.
  R_TypeKind_Integer,

  /// The natural type kind.
  /// <code>R.Natural(8|16|32|64)</code> are examples for this type kind.
  R_TypeKind_Natural,

  /// An object type.
  R_TypeKind_Object,

  /// The size type.
  /// <code>R.Size</code> is an example of this type kind.
  R_TypeKind_Size,

  /// The void type kind.
  /// <code>R.Void</code> is of this type.
  R_TypeKind_Void,

} R_TypeKind;

/// @brief Get the size, in Bytes, of a value of this type.
/// @param self A pointer to this type.
/// @return The size, in Bytes, of a value of this type.
R_SizeValue
R_Type_getValueSize
  (
    R_Type const* self
  );

/// @brief Get the parent object type of this type.
/// @param self A pointer to this type.
/// @return A pointer to the parent object type of this type if any. The null pointer otherwise.
R_Type*
R_Type_getParentObjectType
  (
    R_Type const* self
  );

/// @brief Get the visit object callback function of this type.
/// @param self A pointer to this type.
/// @return A pointer to the visit callback function of this type if any. The null pointer otherwise.
R_Type_VisitObjectCallbackFunction*
R_Type_getVisitObjectCallbackFunction
  (
    R_Type const* self
  );

/// @brief Get the destruct object callback function of this type.
/// @param self A pointer to this type.
/// @return A pointer to the destruct callback function of this type if any. The null pointer otherwise.
R_Type_DestructObjectCallbackFunction*
R_Type_getDestructObjectCallbackFunction
  (
    R_Type const* self
  );

/// @brief Get if this type has child types.
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if this type has child types. #R_BooleanValue_False otherwise.
R_BooleanValue
R_Type_hasChildren
  (
    R_Type const* self
  );

/// @brief Get the type kind of this type.
/// @param self A pointer to this type.
/// @return The type kind of this type type.
R_TypeKind
R_Type_getKind
  (
    R_Type const* self
  );

/// @brief Get if this type is a subtype of another type.
/// @param self A pointer to this type.
/// @param other A pointer to the other type.
/// @return R_BooleanValue_True if this type is a subtype of the othe type. R_BooleanValue_False otherwise.
R_BooleanValue
R_Type_isSubType
  (
    R_Type const* self,
    R_Type const* other
  );

/// @brief Get if this type is of the kind of type "boolean".
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if the type is of the kind of type "boolean". #R_BooleanValue_False otherwise.
static inline R_BooleanValue
R_Type_isBooleanKind
  (
    R_Type const* self
  )
{ return R_TypeKind_Boolean == R_Type_getKind(self); }

/// @brief Get if this type is of the kind of type "integer".
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if the type is of the kind of type "integer". #R_BooleanValue_False otherwise.
static inline R_BooleanValue
R_Type_isIntegerKind
  (
    R_Type const* self
  )
{ return R_TypeKind_Integer == R_Type_getKind(self); }

/// @brief Get if this type is of the kind of type "natural".
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if this type of the kind of type "natural". #R_BooleanValue_False otherwise.
static inline R_BooleanValue
R_Type_isNaturalKind
  (
    R_Type const* self
  )
{ return R_TypeKind_Natural == R_Type_getKind(self); }

/// @brief Get if this type is of the kind of type "object".
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if the type is of the kind of type "object". #R_BooleanValue_False otherwise.
static inline R_BooleanValue
R_Type_isObjectKind
  (
    R_Type const* self
  )
{ return R_TypeKind_Object == R_Type_getKind(self); }

/// @brief Get if this type is of the kind of type "size".
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if the type is of the kind of type "size". #R_BooleanValue_False otherwise.
static inline R_BooleanValue
R_Type_isSizeKind
  (
    R_Type const* self
  )
{ return R_TypeKind_Size == R_Type_getKind(self); }

/// @brief Get if this type is of the kind of type "void".
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if the type is of the kind of type "void". #R_BooleanValue_False otherwise.
static inline R_BooleanValue
R_Type_isVoidKind
  (
    R_Type const* self
  )
{ return R_TypeKind_Void == R_Type_getKind(self); }

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerBooleanType
  (
    char const* name,
    size_t nameLength,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerIntegerType
  (
    char const* name,
    size_t nameLength,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerNaturalType
  (
    char const* name,
    size_t nameLength,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerObjectType
  (
    char const* name,
    size_t nameLength,
    size_t valueSize,
    R_Type* parentObjectType,
    R_Type_TypeDestructingCallbackFunction* typeDestructing,
    R_Type_VisitObjectCallbackFunction* visit,
    R_Type_DestructObjectCallbackFunction* destruct
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerSizeType
  (
    char const* name,
    size_t nameLength,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerVoidType
  (
    char const* name,
    size_t nameLength,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_TypeNotExists */
R_Type*
R_getObjectType
  (
    char const* name,
    size_t nameLength
  );

#endif // R_TYPES_H_INCLUDED
