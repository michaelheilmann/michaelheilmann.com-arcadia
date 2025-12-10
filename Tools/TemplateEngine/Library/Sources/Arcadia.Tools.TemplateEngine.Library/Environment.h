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

#if !defined(ARCADIA_TEMPLATEENGINE_ENVIRONMENT_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_ENVIRONMENT_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.FileContext", Environment,
                          u8"Arcadia.Object");

struct EnvironmentDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Environment {
  Arcadia_Object _parent;
  /// The enclosing environment or null.
  Environment* enclosing;
  /// Map from strings to strings.
  /// The key string is the variable name, the value string is the variable value.
  Arcadia_Map* variables;
};

Environment*
Environment_create
  (
    Arcadia_Thread* thread,
    Environment* enclosing
  );

Environment*
Environment_loadString
  (
    Arcadia_Thread* thread,
    Arcadia_String* source
  );

/// @brief
/// Get the value of  variable.
/// @param thread
/// A pointer to this thread.
/// @param self
/// A pointer to this environment.
/// @param key
/// The name of the variable (a string value).
/// @param recursive
/// #Arcadia_BooleanValue_True: Search the environments from this environments outwards until the variable is found.
/// #Arcadia_BooleanValue_True: Search this (only) environment.
/// @return
/// The variable value (a string value) if the variable was found, a void value otherwise.
Arcadia_Value
Environment_get
  (
    Arcadia_Thread* thread,
    Environment* self,
    Arcadia_Value key,
    Arcadia_BooleanValue recursive
  );

void
Environment_set
  (
    Arcadia_Thread* thread,
    Environment* self,
    Arcadia_Value key,
    Arcadia_Value value
  );

#endif // ARCADIA_TEMPLATEENGINE_ENVIRONMENT_H_INCLUDED
