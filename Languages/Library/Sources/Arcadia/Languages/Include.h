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

#if !defined(ARCADIA_LANGUAGES_INCLUDE_H_INCLUDED)
#define ARCADIA_LANGUAGES_INCLUDE_H_INCLUDED

// If a file x belongs to a module a and ARCADIA_a_MODULE is not defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_LANGUAGES_MODULE")
#define ARCADIA_LANGUAGES_MODULE (1)

// If a file x of a module a is not an export file of that module and ARCADIA_a_EXPORT is defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_LANGUAGES_EXPORT")
#define ARCADIA_LANGUAGES_EXPORT (1)

#include "Arcadia/Languages/Diagnostics.h"
#include "Arcadia/Languages/mangleName.h"
#include "Arcadia/Languages/Scanner.h"
#include "Arcadia/Languages/Scope.h"
#include "Arcadia/Languages/StringTable.h"

#undef ARCADIA_LANGUAGES_EXPORT
#pragma pop_macro("ARCADIA_LANGUAGES_EXPORT")

#undef ARCADIA_LANGUAGES_MODULE
#pragma pop_macro("ARCADIA_LANGUAGES_MODULE")

#endif // ARCADIA_LANGUAGES_INCLUDE_H_INCLUDED
