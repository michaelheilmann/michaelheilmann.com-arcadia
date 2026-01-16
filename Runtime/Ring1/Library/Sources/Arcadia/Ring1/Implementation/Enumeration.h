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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_ENUMERATION_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_ENUMERATION_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Configure.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
typedef struct Arcadia_Thread Arcadia_Thread;
typedef void Arcadia_Type;

/// R(untime) ex(tension) macro.
/// @param _cilName UTF-8 string literal for the Machine Interface Language type name of the type.
/// @param _cName C name of the type.
#define Arcadia_declareEnumerationType(_cilName, _cName) \
  typedef enum _cName _cName; \
  Arcadia_TypeValue \
  _##_cName##_getType \
    ( \
      Arcadia_Thread* thread \
    );

/// R(untime) ex(tension) macro.
/// @param _cilName UTF-8 string literal for the Machine Interface Language type name of the type.
/// @param _cName C name of the type.
#define Arcadia_defineEnumerationType(_cilName, _cName, _cTypeOperations) \
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
      g_##_cName##_type = Arcadia_registerEnumerationType(thread, Arcadia_Names_getOrCreateName(thread, _cilName, sizeof(_cilName) - 1), sizeof(_cName), _cTypeOperations, &_##_cName##_typeDestructing); \
    } \
    return g_##_cName##_type; \
  }
  
typedef struct Arcadia_EnumerationValue {
  Arcadia_Type* type;
  Arcadia_Integer32Value value;  
} Arcadia_EnumerationValue;

static inline Arcadia_EnumerationValue
Arcadia_EnumerationValue_make
  (
    Arcadia_Type* type,
    Arcadia_Integer32Value value
  )
{
  Arcadia_EnumerationValue temporary = { .type = type, .value = value };
  return temporary;
}

#endif // ARCADIA_RING1_IMPLEMENTATION_ENUMERATION_H_INCLUDED
