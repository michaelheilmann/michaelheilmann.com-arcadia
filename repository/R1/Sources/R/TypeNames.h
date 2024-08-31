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
#include "R/Boolean.h"
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
typedef struct _TypeName _TypeName;

struct _TypeName {
  char* bytes;
  R_SizeValue numberOfBytes;
  R_SizeValue hash;
};

/* Create a type name. Raise error on failure. */
_TypeName*
_TypeNames_createTypeName
  (
    void const* bytes,
    R_SizeValue numberOfBytes
  );

/* Does not fail. */
void
_TypeNames_destroyTypeName
  (
    _TypeName* typeName
  );

/* Does not fail. */
R_BooleanValue
TypeNames_areTypeNamesEqual
  (
    _TypeName const* x,
    _TypeName const* y
  );

void
_R_TypeNames_startup
  ( 
  );

void
_R_TypeNames_shutdown
  ( 
  );

#endif // R_TYPENAME_H_INCLUDED
