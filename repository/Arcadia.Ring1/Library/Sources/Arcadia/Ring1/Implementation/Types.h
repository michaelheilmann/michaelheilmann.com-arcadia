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

// Last modified: 2024-09-22

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPES_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPES_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"
#include "Arcadia/Ring1/Implementation/Value.h"
typedef struct Arcadia_Value Arcadia_Value;

/// Type operations for object types.
typedef struct Arcadia_ObjectType_Operations {
  Arcadia_ForeignProcedure* construct;
  void (*destruct)(Arcadia_Process* process, void* self);
  void (*visit)(Arcadia_Process* process, void* self);
} Arcadia_ObjectType_Operations;

/// Type operations for all types.
typedef struct Arcadia_Type_Operations {
  /// Pointer to the object type operations if the type is an object type.
  /// The null pointer otherwise.
  Arcadia_ObjectType_Operations const* objectTypeOperations;
  Arcadia_ForeignProcedure* add;
  Arcadia_ForeignProcedure* and;
  Arcadia_ForeignProcedure* concatenate;
  Arcadia_ForeignProcedure* divide;
  Arcadia_ForeignProcedure* equalTo;
  Arcadia_ForeignProcedure* greaterThan;
  Arcadia_ForeignProcedure* greaterThanOrEqualTo;
  Arcadia_ForeignProcedure* hash;
  Arcadia_ForeignProcedure* lowerThan;
  Arcadia_ForeignProcedure* lowerThanOrEqualTo;
  Arcadia_ForeignProcedure* multiply;
  Arcadia_ForeignProcedure* negate;
  Arcadia_ForeignProcedure* not;
  Arcadia_ForeignProcedure* notEqualTo;
  Arcadia_ForeignProcedure* or;
  Arcadia_ForeignProcedure* subtract;
  Arcadia_ForeignProcedure* toString;
} Arcadia_Type_Operations;

/// @brief Type of a visti callback function.
/// Each object type may have its own visit callback function.
/// For an object of type A1 <: A2 <: ... <: An the callback functions are invoked from the bottom most to the top most type.
/// @warning Such a function MAY set the by-thread status variable. Such a function MAY NOT jump.
typedef void (Arcadia_Type_VisitObjectCallbackFunction)(Arcadia_Process* process, void* object);

/// @brief Type of a destruct callback function.
/// Each object type may have its own destruct callback function.
/// For an object of type A1 <: A2 <: ... <: An the callback functions are invoked from the bottom most to the top most type.
/// @warning Such a function MAY set the by-thread status variable. Such a function MAY NOT jump.
typedef void (Arcadia_Type_DestructObjectCallbackFunction)(Arcadia_Process*, void* object);

/// @brief Type of a type destructing callback function.
/// Invoked when the type is destructing.
typedef void (Arcadia_Type_TypeDestructingCallbackFunction)(void* context);

/// The opaque C type representing a type.
/// Types are not garbage collected. Once a type was added, it remains there until the process terminates.
typedef void Arcadia_Type;
typedef Arcadia_Type* Arcadia_TypeValue;

/// An enumeration of the type kinds.
typedef enum Arcadia_TypeKind {

  /// The "internal" type kind.
  /// Examples of this type kind are
  /// - <code>Arcadia.Atom</code>
  /// - <code>Arcadia.ImmutableByteArray</code>
  /// - <code>Arcadia.Memory</code>
  /// - <code>Arcadia.Type</code>
  Arcadia_TypeKind_Internal,

  /// The "scalar" type kind.
  /// Examples of this type are:
  /// - <code>Arcadia.Boolean</code>
  /// - <code>Arcadia.ForeignProcedure</code> 
  /// - <code>Arcadia.Integer(8|16|32|64)</code>
  /// - <code>Arcadia.Natural(8|16|32|64)</code>
  /// - <code>Arcadia.Real(32|64)</code>
  /// - <code>Arcadia.Size</code>
  /// - <code>Arcadia.Void</code>
  Arcadia_TypeKind_Scalar,

  /// The "object" type kind.
  Arcadia_TypeKind_Object,

} Arcadia_TypeKind;

static inline void
Arcadia_Type_visit
  (
    Arcadia_TypeValue self
  )
{/*Intentionally empty.*/}

Arcadia_SizeValue
Arcadia_Type_hash
  (
    Arcadia_TypeValue self
  );

/// @brief Get the size, in Bytes, of a value of this type.
/// @param self A pointer to this type.
/// @return The size, in Bytes, of a value of this type.
Arcadia_SizeValue
Arcadia_Type_getValueSize
  (
    Arcadia_TypeValue self
  );

/// @brief Get the parent object type of this type.
/// @param self A pointer to this type.
/// @return A pointer to the parent object type of this type if any. The null pointer otherwise.
Arcadia_TypeValue
Arcadia_Type_getParentObjectType
  (
    Arcadia_TypeValue self
  );

/// @brief Get the visit object callback function of this type.
/// @param self A pointer to this type.
/// @return A pointer to the visit callback function of this type if any. The null pointer otherwise.
Arcadia_Type_VisitObjectCallbackFunction*
Arcadia_Type_getVisitObjectCallbackFunction
  (
    Arcadia_TypeValue self
  );

/// @brief Get the destruct object callback function of this type.
/// @param self A pointer to this type.
/// @return A pointer to the destruct callback function of this type if any. The null pointer otherwise.
Arcadia_Type_DestructObjectCallbackFunction*
Arcadia_Type_getDestructObjectCallbackFunction
  (
    Arcadia_TypeValue self
  );

/// @brief Get if this type has child types.
/// @param self A pointer to this type.
/// @return #Arcadia_BooleanValue_True if this type has child types. #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_Type_hasChildren
  (
    Arcadia_TypeValue self
  );

/// @brief Get the type kind of this type.
/// @param self A pointer to this type.
/// @return The type kind of this type type.
Arcadia_TypeKind
Arcadia_Type_getKind
  (
    Arcadia_TypeValue self
  );

/// @brief Get if this type is a subtype of another type.
/// @param self A pointer to this type.
/// @param other A pointer to the other type.
/// @return Arcadia_BooleanValue_True if this type is a subtype of the othe type. Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_Type_isSubType
  (
    Arcadia_TypeValue self,
    Arcadia_TypeValue other
  );

/// @brief Get if this type is of the kind of type "internal".
/// @param self A pointer to this type.
/// @return #Arcadia_BooleanValue_True if the type is of the kind of type "internal". #Arcadia_BooleanValue_False otherwise.
static inline Arcadia_BooleanValue
Arcadia_Type_isInternalKind
  (
    Arcadia_TypeValue self
  )
{ return Arcadia_TypeKind_Internal == Arcadia_Type_getKind(self); }

/// @brief Get if this type is of the kind of type "scalar".
/// @param self A pointer to this type.
/// @return #Arcadia_BooleanValue_True if the type is of the kind of type "scalar". #Arcadia_BooleanValue_False otherwise.
static inline Arcadia_BooleanValue
Arcadia_Type_isScalarKind
  (
    Arcadia_TypeValue self
  )
{ return Arcadia_TypeKind_Scalar == Arcadia_Type_getKind(self); }

/// @brief Get if this type is of the kind of type "object".
/// @param self A pointer to this type.
/// @return #Arcadia_BooleanValue_True if the type is of the kind of type "object". #Arcadia_BooleanValue_False otherwise.
static inline Arcadia_BooleanValue
Arcadia_Type_isObjectKind
  (
    Arcadia_TypeValue self
  )
{ return Arcadia_TypeKind_Object == Arcadia_Type_getKind(self); }

/* Arcadia_Status_ArgumentValueInvalid, Arcadia_Status_AllocationFailed, Arcadia_Status_TypeExists */
Arcadia_TypeValue
Arcadia_registerInternalType
  (
    Arcadia_Process* process,
    char const* name,
    size_t nameLength,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* Arcadia_Status_ArgumentValueInvalid, Arcadia_Status_AllocationFailed, Arcadia_Status_TypeExists */
Arcadia_TypeValue
Arcadia_registerScalarType
  (
    Arcadia_Process* process,
    char const* name,
    size_t nameLength,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* Arcadia_Status_ArgumentValueInvalid, Arcadia_Status_AllocationFailed, Arcadia_Status_TypeExists */
Arcadia_TypeValue
Arcadia_registerObjectType
  (
    Arcadia_Process* process,
    char const* name,
    size_t nameLength,
    size_t valueSize,
    Arcadia_TypeValue parentObjectType,
    Arcadia_Type_Operations const* typeOperations,
    Arcadia_Type_TypeDestructingCallbackFunction* typeDestructing
  );

/* Arcadia_Status_ArgumentValueInvalid, Arcadia_Status_TypeNotExists */
Arcadia_TypeValue
Arcadia_getType
  (
    Arcadia_Process* process,
    char const* name,
    size_t nameLength
  );

Arcadia_AtomValue
Arcadia_Type_getName
  (
    Arcadia_TypeValue type
  );

Arcadia_Type_Operations const*
Arcadia_Type_getOperations
  (
    Arcadia_TypeValue type
  );

/// @brief Get the "Arcadia.Memory" type.
/// @param process A pointer to the Arcadia_Process object.
/// @return The "Arcadia.Memory" type.
Arcadia_TypeValue
_Arcadia_Memory_getType
  (
    Arcadia_Process* process
  );

/// @brief Get the "Arcadia.Type" type.
/// @param process A pointer to the Arcadia_Proces object.
/// @return The "Arcadia.Type" type.
Arcadia_TypeValue
_Arcadia_Type_getType
  (
    Arcadia_Process* process
  );

/// @brief Get the "Arcadia.Atom" type.
/// @param process A pointer to the Arcadia_Proces object.
/// @return The "Arcadia.Atom" type.
Arcadia_TypeValue
_Arcadia_AtomValue_getType
  (
    Arcadia_Process* process
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPES_H_INCLUDED
