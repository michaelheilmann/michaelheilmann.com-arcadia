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

#if !defined(R_TYPENAMEW_H_INCLUDED)
#define R_TYPENAMES_H_INCLUDED

#include "R/Configure.h"
#include "Arms.h"
#include "R/Atoms.h"
#include "R/Boolean.h"
#include "R/Natural64.h"
#include "R/Size.h"

// An type name is a a string of the form
// <code>
// key : &lt;name&gt;('.'&lt;name&gt;)
// </code>
// where
// <code>
// &lt;name&gt; : ('_' | &lt;letter&gt;) ('_' | &lt;letter&gt; | &lt;digit&gt;)
// &lt;letter&gt; : 'a'-'z'|'A'-'Z'
// &lt;digit&gt; : '0' - '9'
// </code>
typedef struct R_TypeName R_TypeName;
typedef R_TypeName* R_TypeNameValue;

struct R_TypeName {
  R_TypeName* next;
  /// If the key was visited.
  R_BooleanValue visited;
  /// The last time this key was visited.
  R_Natural64Value lastVisited;
  /// The atom of this type name.
  R_AtomValue atomValue;
};

/* Create a type name. Raise error on failure. */
R_TypeNameValue
R_TypeNames_getOrCreateTypeName
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

/// @brief Startup the type names.
void
R_TypeNames_startup
  ( 
  );

/// @brief Shutdown the type names.
void
R_TypeNames_shutdown
  ( 
  );

/// Must be invoked before the pre mark phase.
void
R_TypeNames_onPreMark
  (
  );

/// Must be invoked after the finalize phase.
void
R_TypeNames_onPostFinalize
  (
    bool shutdown
  );

/// @brief Update the age of this name.
void
R_TypeName_visit
  (
    R_TypeNameValue typeNameValue
  );  

#endif // R_TYPENAME_H_INCLUDED
