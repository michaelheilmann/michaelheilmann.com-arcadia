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

#if !defined(ARCADIA_DDLS_INCLUDE_H_INCLUDED)
#define ARCADIA_DDLS_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_DDLS_PRIVATE")
#define ARCADIA_DDLS_PRIVATE (1)

#include "Arcadia/DDLS/Syntactical/DefaultReader.h"
#include "Arcadia/DDLS/Semantical/SymbolReader.h"

#include "Arcadia/DDLS/Nodes/Include.h"

#include "Arcadia/DDLS/Implementation/ValidationContext.h"

#undef ARCADIA_DDLS_PRIVATE
#pragma pop_macro("ARCADIA_DDLS_PRIVATE")

#endif // ARCADIA_DDLS_INCLUDE_H_INCLUDED
