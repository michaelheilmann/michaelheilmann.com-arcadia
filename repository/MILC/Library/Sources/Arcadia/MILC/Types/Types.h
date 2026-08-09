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

#if !defined(ARCADIA_MILC_TYPES_H_INCLUDED)
#define ARCADIA_MILC_TYPES_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
typedef struct Arcadia_MILC_Context Arcadia_MILC_Context;
typedef struct Arcadia_MILC_Type Arcadia_MILC_Type;

/// @brief The base of all types.
Arcadia_declareObjectType(u8"Arcadia.MILC.Types", Arcadia_MILC_Types,
                          u8"Arcadia.Object");

struct Arcadia_MILC_TypesDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_Types {
  Arcadia_Object _parent;

  /// @brief The context.
  Arcadia_MILC_Context* context;
  
  /// @code
  /// Arcadia.Integer16
  /// @endcode
  Arcadia_MILC_Type* integer16;
  /// @code
  /// Arcadia.Integer32
  /// @endcode
  Arcadia_MILC_Type* integer32;
  /// @code
  /// Arcadia.Integer64
  /// @endcode
  Arcadia_MILC_Type* integer64;
  /// @code
  /// Arcadia.Integer8
  /// @endcode
  Arcadia_MILC_Type* integer8;
  
  /// @code
  /// Arcadia.Natural16
  /// @endcode
  Arcadia_MILC_Type* natural16;
  /// @code
  /// Arcadia.Natural32
  /// @endcode
  Arcadia_MILC_Type* natural32;
  /// @code
  /// Arcadia.Natural64
  /// @endcode
  Arcadia_MILC_Type* natural64;
  /// @code
  /// Arcadia.Natural8
  /// @endcode
  Arcadia_MILC_Type* natural8;
};

Arcadia_MILC_Types*
Arcadia_MILC_Types_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

Arcadia_MILC_Types*
Arcadia_MILC_Type_getInstance
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

#endif // ARCADIA_MILC_TYPES_H_INCLUDED
