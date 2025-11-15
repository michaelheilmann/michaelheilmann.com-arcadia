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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_OBJECT_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_OBJECT_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Types.h"
#include "Arcadia/ARMS/Include.h"
typedef struct Arcadia_Value Arcadia_Value;

typedef struct Arcadia_Object Arcadia_Object;

Arcadia_TypeValue
_Arcadia_Object_getType
  (
    Arcadia_Thread* thread
  );

struct Arcadia_Object {
  int dummy;
};

#define Arcadia_Configuration_withBarriers (Arcadia_ARMS_Configuration_WithBarriers)

#define Arcadia_superTypeConstructor(_thread, _type, _self) \
  { \
    Arcadia_Type_getOperations(Arcadia_Type_getParentObjectType(thread, _type))->objectTypeOperations->construct(_thread, (Arcadia_Object*)_self); \
  }

/// R(untime) ex(tension) macro.
/// @param _cilName, _cilParentName UTF8 string literals for the Common Intermediate Language type names of the type and its parent type.
#define Arcadia_declareObjectType(_cilName, _cName, _cilParentName) \
  typedef struct _cName _cName; \
  Arcadia_TypeValue \
  _##_cName##_getType \
    ( \
      Arcadia_Thread* thread \
    );

/// R(untime) ex(tension) macro.
/// @param _cilName, _cilParentName UTF8 string literals for the Common Intermediate Language type names of the type and its parent type.
#define Arcadia_defineObjectType(_cilName, _cName, _cilParentName, _cParentName, _cTypeOperations) \
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
      Arcadia_Thread* thread \
    ) \
  { \
    if (!g_##_cName##_type) { \
      Arcadia_TypeValue parentType = _##_cParentName##_getType(thread); \
      g_##_cName##_type = Arcadia_registerObjectType \
        ( \
          thread, \
          _cilName, \
          sizeof(_cilName) - 1, \
          sizeof(_cName), \
          parentType, \
          _cTypeOperations, \
          &_##_cName##_typeDestructing \
        ); \
    } \
    return g_##_cName##_type; \
  }


/// @brief
/// Allocate an "Arcadia.Object" or derived type value.
/// 
/// @details 
/// a) Raise "Arcadia.Status.ArgumentValueInvalid" if "type" is a null pointer.
///    Raise "Arcadia.Status.ArgumentTypeInvalid" if "type" is not an "Arcadia.Object" or derived type.
/// 
/// b) Allocate memory of size "Arcadia_Type_getValueSize(type)" at address "a".
///    Raise "Arcadia.Status.AllocationFailed" if the allocation fails.
///    Assign this memory the "Arcadia.Memory" type.
/// 
/// c) Cast that memory into an object
/// 
/// d) Invoke the constructor of type "type" with the specified number of argument values.
/// 
/// e) Assert the stack is not corrupted if a) - c) are successfull. Otherwise raise Arcadia.Status.StackCorruption.
void*
ARCADIA_CREATEOBJECT0
  (
    Arcadia_Thread* thread,
    Arcadia_Type* type,
    Arcadia_SizeValue oldValueStackSize
  );

/// @transitional
#define ARCADIA_CREATEOBJECT(type) \
  return ARCADIA_CREATEOBJECT0(thread, _##type##_getType(thread), oldValueStackSize);

void
Arcadia_Object_setType
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    Arcadia_TypeValue type
  );

/// @brief Visit an object.
/// @param self A pointer to the object.
void
Arcadia_Object_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  );

void
Arcadia_Object_addNotifyDestroyCallback
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    void* observer,
    void (*callback)(void* observer, Arcadia_Object*)
  );

void
Arcadia_Object_removeNotifyDestroyCallback
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    void* observer,
    void (*callback)(void* observer, Arcadia_Object*)
  );

#if Arcadia_Configuration_withBarriers

/// @brief A "forward" barrier.
/// If both @a source and @a target are not null,
/// and if @a source is black and if @a target is white,
/// then @a target becomes gray.
void
Arcadia_Object_forwardBarrier
  (
    Arcadia_Thread * thread,
    Arcadia_Object * source,
    Arcadia_Object * target
  );

/// @brief A "backward" barrier.
/// If both @a source and @a target are not null,
/// and if @a source is black and if @a target is white,
/// then @a source becomes gray.
void
Arcadia_Object_backwardBarrier
  (
    Arcadia_Thread * thread,
    Arcadia_Object* source,
    Arcadia_Object* target
  );

#endif

/// @brief Increment the lock count of the object.
/// @param self A pointer to the object.
void
Arcadia_Object_lock
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  );

/// @brief Decrement the lock count of the object.
/// @param self A pointer to the object.
void
Arcadia_Object_unlock
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  );

/// @brief Get the type of an object.
/// @param self A pointer to the object.
/// @return The type of an object.
Arcadia_TypeValue
Arcadia_Object_getType
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  );

static inline Arcadia_BooleanValue
Arcadia_Object_isInstanceOf
  (
    Arcadia_Thread* thread,
    Arcadia_Object* object,
    Arcadia_Type* type
  )
{ return Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, object), type); }

/// "isEqualTo"
Arcadia_BooleanValue
Arcadia_Object_isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    Arcadia_Value const* other
  );

/// "isNotEqualTo"
Arcadia_BooleanValue
Arcadia_Object_isNotEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    Arcadia_Value const* other
  );

/// "hash"
Arcadia_SizeValue
Arcadia_Object_getHash
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self
  );

/// "isIdenticalTo"
Arcadia_BooleanValue
Arcadia_Object_isIdenticalTo
  (
    Arcadia_Thread* thread,
    Arcadia_Object* self,
    Arcadia_Value const* other
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_OBJECT_H_INCLUDED
