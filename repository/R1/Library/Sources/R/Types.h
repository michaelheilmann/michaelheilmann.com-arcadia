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
#include "R/TypeNames.h"
typedef struct R_Value R_Value;

/// Type operations for object types.
typedef struct R_ObjectType_Operations {
  void (*construct)(R_Value* self, R_SizeValue numberOfArguments, R_Value* arguments);
  void (*destruct)(void* self);
  void (*visit)(void* self);
} R_ObjectType_Operations;

/// Type operations for all types.
typedef struct R_Type_Operations {
  /// Pointer to the object type operations if the type is an object type.
  /// The null pointer otherwise.
  R_ObjectType_Operations const* objectTypeOperations;
  void (*add)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*and)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*concatenate)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*divide)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*equalTo)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*greaterThan)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*greaterThanOrEqualTo)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*hash)(R_Value* target, R_Value const* self);
  void (*lowerThan)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*lowerThanOrEqualTo)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*multiply)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*negate)(R_Value* target, R_Value const* self);
  void (*not)(R_Value* target, R_Value const* self);
  void (*notEqualTo)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*or )(R_Value* target, R_Value const* self, R_Value const* other);
  void (*subtract)(R_Value* target, R_Value const* self, R_Value const* other);
  void (*toString)(R_Value* target, R_Value const* self);
} R_Type_Operations;

/// @brief Type of a visti callback function.
/// Each object type may have its own visit callback function.
/// For an object of type A1 <: A2 <: ... <: An the callback functions are invoked from the bottom most to the top most type.
typedef void (R_Type_VisitObjectCallbackFunction)(void* object);

/// @brief Type of a destruct callback function.
/// Each object type may have its own destruct callback function.
/// For an object of type A1 <: A2 <: ... <: An the callback functions are invoked from the bottom most to the top most type.
typedef void (R_Type_DestructObjectCallbackFunction)(void* object);

/// @brief Type of a type destructing callback function.
/// Invoked when the type is destructing.
typedef void (R_Type_TypeDestructingCallbackFunction)(void* context);

typedef void R_Type;

typedef R_Type* R_TypeValue;

/// An enumeration of the type kinds.
typedef enum R_TypeKind {

  /// The "internal" type kind.
  /// <code>R.Internal.Atom</code> and <code>R.Internal.Type</code> are examples of this type kind.
  R_TypeKind_Internal,

  /// The "boolean" type kind.
  /// <code>R.Boolean</code> is an example of this type kind.
  R_TypeKind_Boolean,

  /// The "foreign value" type kind.
  /// <code>R.ForeignProcedure</code> and <code>R.ImmutableByteArray</code> are example of this type kind.
  R_TypeKind_ForeignValue,

  /// The "integer" type kind.
  /// <code>R.Integer(8|16|32|64)</code> are examples for this type kind.
  R_TypeKind_Integer,

  /// The "natural" type kind.
  /// <code>R.Natural(8|16|32|64)</code> are examples for this type kind.
  R_TypeKind_Natural,

  /// The "object" type kind.
  R_TypeKind_Object,

  /// The "real" type kind.
  R_TypeKind_Real,

  /// The "size" type kind.
  /// <code>R.Size</code> is an example of this type kind.
  R_TypeKind_Size,

  /// The "void" type kind.
  /// <code>R.Void</code> is of this type.
  R_TypeKind_Void,

} R_TypeKind;

R_Type*
_R_Type_getType
  (
  );

R_Type*
_R_Atom_getType
  (
  );

static inline void
R_Type_visit
  (
    R_TypeValue self
  )
{/*Intentionally empty.*/}

R_SizeValue
R_Type_hash
  (
    R_TypeValue self
  );

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

/// @brief Get if this type is of the kind of type "foreign value".
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if the type is of the kind of type "foreign value". #R_BooleanValue_False otherwise.
static inline R_BooleanValue
R_Type_isForeignValueKind
  (
    R_Type const* self
  )
{ return R_TypeKind_ForeignValue == R_Type_getKind(self); }

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

/// @brief Get if this type is of the kind of type "reak".
/// @param self A pointer to this type.
/// @return #R_BooleanValue_True if the type is of the kind of type "real". #R_BooleanValue_False otherwise.
static inline R_BooleanValue
R_Type_isRealKind
  (
    R_Type const* self
  )
{ return R_TypeKind_Real == R_Type_getKind(self); }

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
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerForeignValueType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerIntegerType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerNaturalType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
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
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerRealType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerSizeType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_AllocationFailed, R_Status_TypeExists */
void
R_registerVoidType
  (
    char const* name,
    size_t nameLength,
    R_Type_Operations const* typeOperations,
    R_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* R_Status_ArgumentValueInvalid, R_Status_TypeNotExists */
R_Type*
R_getType
  (
    char const* name,
    size_t nameLength
  );

R_TypeNameValue
R_Type_getName
  (
    R_Type* type
  );

R_Type_Operations const*
R_Type_getOperations
  (
    R_Type* type
  );

#endif // R_TYPES_H_INCLUDED
