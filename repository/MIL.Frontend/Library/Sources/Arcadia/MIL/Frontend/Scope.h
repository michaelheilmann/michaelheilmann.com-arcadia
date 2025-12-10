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

#if !defined(ARCADIA_MIL_FRONTEND_SCOPE_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_SCOPE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_MIL_Symbol Arcadia_MIL_Symbol;

Arcadia_declareObjectType(u8"Arcadia.MIL.Scope.Entry", Arcadia_MIL_Scope_Entry,
                          u8"Arcadia.Object");

struct Arcadia_MIL_Scope_EntryDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MIL_Scope_Entry {
  Arcadia_Object _parent;

  // The entry in the enclosing scope shadowed by this entry.
  // This is initially NULL.
  Arcadia_MIL_Scope_Entry* shadowed;

  // The next sibling. A sibling is an entry defined in the same scope.
  // The siblings are sorted in the order they were added starting from the most recently discovered one.
  // This is initially NULL.
  Arcadia_MIL_Scope_Entry* nextSibling;

  // The name of the symbol.
  // This is initially NULL.
  Arcadia_String* name;

};

Arcadia_MIL_Scope_Entry*
Arcadia_MIL_Scope_Entry_create
  (
    Arcadia_Thread* thread
  );

/// @code
/// class Arcadia.MIL.Scope {
///
///   constructor()
///
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.MIL.Scope", Arcadia_MIL_Scope,
                          u8"Arcadia.Object");

struct Arcadia_MIL_ScopeDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MIL_Scope {
  Arcadia_Object _parent;
  /// The entries.
  struct {
    Arcadia_MIL_Scope_Entry** buckets;
    Arcadia_SizeValue size;
    Arcadia_SizeValue capacity;
  } hash;
  /// The siblings
  Arcadia_MIL_Scope_Entry* siblings;
};

/// @brief Create a scope.
/// @param thread A pointer to this thread.
/// @return A pointer to the scope.
Arcadia_MIL_Scope*
Arcadia_MIL_Scope_create
  (
    Arcadia_Thread* thread
  );

/// @brief Enter a symbol into this scope.
/// @param thread A pointer to this thread.
/// @param self A pointer to this scope.
/// @param symbol A pointer to the symbol.
/// @remarks If a symbol of the same name already exists,
/// then it is shadowed by that symbol.
void
Arcadia_MIL_Scope_enter
  (
    Arcadia_Thread* thread,
    Arcadia_MIL_Scope* self,
    Arcadia_MIL_Symbol* symbol
  );

#endif // ARCADIA_MIL_FRONTEND_SCOPE_H_INCLUDED
