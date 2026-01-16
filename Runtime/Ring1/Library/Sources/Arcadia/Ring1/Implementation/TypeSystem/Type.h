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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif
#include "Arcadia/Ring1/Implementation/TypeSystem/TypeKind.h"
#include "Arcadia/Ring1/Implementation/TypeSystem/Names.h"

/// @brief The opaque C type representing a type.
/// Types are not garbage collected. Once a type was added, it remains there until the process terminates.
typedef void Arcadia_Type;

/// @brief A pointer to a type or the null pointer.
typedef Arcadia_Type* Arcadia_TypeValue;

/// @brief Get the type of a specified name.
/// @param thread A pointer to this thread.
/// @param name A poiner to the name.
/// @return A pointer to the type.
/// @error #Arcadia_Status_ArgumentValueInvalid @a name is a null pointer
/// @error Arcadia_Status_TypeNotExists no type of the specified name was found
Arcadia_TypeValue
Arcadia_getType
  (
    Arcadia_Thread* thread,
    Arcadia_Name* name
  );

/// @brief Get the name of this type.
/// @param thread A pointer to this thread.
/// @param self A pointer to this type.
/// @return A pointer to the name off this type.
Arcadia_Name*
Arcadia_Type_getName
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  );

/// @brief Get the hash of this type.
/// @param thread A pointer to this thread.
/// @param self A pointer to this type.
/// @return The hash of this type.
size_t
Arcadia_Type_getHash
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  );

/// @brief Get the type kind of this type.
/// @param thread A pointer to this thread.
/// @param self A pointer to this type.
/// @return The kind of this type.
Arcadia_TypeKind
Arcadia_Type_getKind
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  );

/// @brief Get if this type is of the kind of type "internal".
/// @param self A pointer to this type.
/// @return #Arcadia_BooleanValue_True if the type is of the kind of type "internal". #Arcadia_BooleanValue_False otherwise.
static inline bool
Arcadia_Type_isInternalKind
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  )
{ return Arcadia_TypeKind_Internal == Arcadia_Type_getKind(thread, self); }

/// @brief Get if this type is of the kind of type "scalar".
/// @param self A pointer to this type.
/// @return #Arcadia_BooleanValue_True if the type is of the kind of type "scalar". #Arcadia_BooleanValue_False otherwise.
static inline bool
Arcadia_Type_isScalarKind
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  )
{ return Arcadia_TypeKind_Scalar == Arcadia_Type_getKind(thread, self); }

/// @brief Get if this type is of the kind of type "object".
/// @param self A pointer to this type.
/// @return #Arcadia_BooleanValue_True if the type is of the kind of type "object". #Arcadia_BooleanValue_False otherwise.
static inline bool
Arcadia_Type_isObjectKind
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  )
{ return Arcadia_TypeKind_Object == Arcadia_Type_getKind(thread, self); }

/// @brief Get if this type is of the kind of type "enumeration".
/// @param self A pointer to this type.
/// @return #Arcadia_BooleanValue_True if the type is of the kind of type "enumeration". #Arcadia_BooleanValue_False otherwise.
static inline bool
Arcadia_Type_isEnumerationtKind
  (
    Arcadia_Thread* thread,
    Arcadia_TypeValue self
  )
{ return Arcadia_TypeKind_Enumeration == Arcadia_Type_getKind(thread, self); }

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPE_H_INCLUDED
