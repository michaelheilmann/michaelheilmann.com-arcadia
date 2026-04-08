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

#if !defined(ARCADIA_DDL_INCLUDE_H_INCLUDED)
#define ARCADIA_DDL_INCLUDE_H_INCLUDED

// If a file x belongs to a module a and ARCADIA_a_MODULE is not defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_DDL_MODULE")
#define ARCADIA_DDL_MODULE (1)

// If a file x of a module a is not an export file of that module and ARCADIA_a_EXPORT is defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_DDL_EXPORT")
#define ARCADIA_DDL_EXPORT (1)

#include "Arcadia/DDL/Reader/Keywords.h"
#include "Arcadia/DDL/Reader/DefaultReader.h"
#include "Arcadia/DDL/Reader/Parser.h"
#include "Arcadia/DDL/Reader/Scanner.h"
#include "Arcadia/DDL/Reader/WordType.h"
#include "Arcadia/DDL/SemanticalAnalysis.h"
#include "Arcadia/DDL/Writer/Unparser.h"

#undef ARCADIA_DDL_EXPORT
#pragma pop_macro("ARCADIA_DDL_EXPORT")

#undef ARCADIA_DDL_MODULE
#pragma pop_macro("ARCADIA_DDL_MODULE")

#endif // ARCADIA_DDL_INCLUDE_H_INCLUDED
