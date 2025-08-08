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

#if !defined(ARCADIA_RING2_INCLUDE_H_INCLUDED)
#define ARCADIA_RING2_INCLUDE_H_INCLUDED

#pragma push_macro("ARCADIA_RING2_PRIVATE")
#undef ARCADIA_RING2_PRIVATE
#define ARCADIA_RING2_PRIVATE (1)

#include "Arcadia/Ring2/Implementation/ArgumentsValidation.h"

#include "Arcadia/Ring2/Implementation/ByteBuffer.h"

#include "Arcadia/Ring2/Implementation/CommandLine.h"

#include "Arcadia/Ring2/Implementation/FileHandle.h"
#include "Arcadia/Ring2/Implementation/FilePath.h"
#include "Arcadia/Ring2/Implementation/FileSystem.h"

#include "Arcadia/Ring2/Implementation/Collections/ArrayDeque.h"
#include "Arcadia/Ring2/Implementation/Collections/ArrayList.h"
#include "Arcadia/Ring2/Implementation/Collections/HashMap.h"
#include "Arcadia/Ring2/Implementation/Collections/HashSet.h"
#include "Arcadia/Ring2/Implementation/Collections/ArrayStack.h"
#include "Arcadia/Ring2/Implementation/Collections/ImmutableList.h"

#include "Arcadia/Ring2/Implementation/Utf8Reader.h"
#include "Arcadia/Ring2/Implementation/Utf8ByteBufferReader.h"
#include "Arcadia/Ring2/Implementation/Utf8ByteBufferWriter.h"
#include "Arcadia/Ring2/Implementation/Utf8StringReader.h"
#include "Arcadia/Ring2/Implementation/Utf8Writer.h"

#include "Arcadia/Ring2/Implementation/String.h"
#include "Arcadia/Ring2/Implementation/StringBuffer.h"

#include "Arcadia/Ring2/Implementation/Time/PointInTime.h"
#include "Arcadia/Ring2/Implementation/Time/TimeSpecification.h"

#undef ARCADIA_RING2_PRIVATE
#pragma pop_macro("ARCADIA_RING2_PRIVATE")

#endif // ARCADIA_RING2_INCLUDE_H_INCLUDED
