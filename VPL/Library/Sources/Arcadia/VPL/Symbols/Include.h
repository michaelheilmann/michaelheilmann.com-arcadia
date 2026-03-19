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

#if !defined(ARCADIA_VPL_SYMBOLS_INCLUDE_H_INCLUDED)
#define ARCADIA_VPL_SYMBOLS_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_VPL_PRIVATE")
#undef ARCADIA_VPL_PRIVATE
#define ARCADIA_VPL_PRIVATE (1)

#include "Arcadia/VPL/Symbols/BuiltinType.h"
#include "Arcadia/VPL/Symbols/ConstantRecord.h"
#include "Arcadia/VPL/Symbols/ConstantKind.h"
#include "Arcadia/VPL/Symbols/ConstantRecord.h"
#include "Arcadia/VPL/Symbols/ConstantScalar.h"
#include "Arcadia/VPL/Symbols/Procedure.h"
#include "Arcadia/VPL/Symbols/Program.h"
#include "Arcadia/VPL/Symbols/Stage.h"
#include "Arcadia/VPL/Symbols/Symbol.h"
#include "Arcadia/VPL/Symbols/Variable.h"
#include "Arcadia/VPL/Symbols/VariableScalar.h"

#undef ARCADIA_VPL_PRIVATE
#pragma pop_macro("ARCADIA_VPL_PRIVATE")

#endif // ARCADIA_VPL_SYMBOLS_INCLUDE_H_INCLUDED
