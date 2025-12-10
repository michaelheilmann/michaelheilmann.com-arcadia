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

#pragma push_macro("ARCADIA_DDL_PRIVATE")
#define ARCADIA_DDL_PRIVATE (1)
#include "Arcadia/DDL/Reader/Keywords.h"
#include "Arcadia/DDL/Reader/DefaultReader.h"
#include "Arcadia/DDL/Reader/Parser.h"
#include "Arcadia/DDL/Reader/Scanner.h"
#include "Arcadia/DDL/Reader/WordType.h"
#include "Arcadia/DDL/SemanticalAnalysis.h"
#include "Arcadia/DDL/Writer/Unparser.h"
#undef ARCADIA_DDL_PRIVATE
#pragma pop_macro("ARCADIA_DDL_PRIVATE")

#endif // ARCADIA_DDL_INCLUDE_H_INCLUDED
