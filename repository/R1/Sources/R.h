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

// Last modified: 2024-08-29

#if !defined(R_H_INCLUDED)
#define R_H_INCLUDED

#include "R/Boolean.h"

#include "R/ByteBuffer.h"

#include "R/clamp.h"
#include "R/CommandLine/Include.h"
#include "R/countLeadingZeroes.h"

#include "R/ForeignFunctionReference.h"

#include "R/FileHandle.h"
#include "R/FilePath.h"
#include "R/FileSystem.h"

#include "R/getTickCount.h"

#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"

#include "R/isPowerOfTwo.h"

#include "R/JumpTarget.h"

#include "R/List.h"

#include "R/maximum.h"
#include "R/minimum.h"

#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"

#include "R/nextPowerOfTwoGt.h"
#include "R/nextPowerOfTwoGte.h"

#include "r/Object.h"

#include "R/Stack.h"

#include "R/swap.h"

#include "R/Size.h"

#include "R/Status.h"

#include "R/String.h"
#include "R/StringBuffer.h"

#include "R/Utf8.h"
#include "R/Utf8Reader.h"
#include "R/Utf8ByteBufferReader.h"
#include "R/Utf8ByteBufferWriter.h"
#include "R/Utf8StringReader.h"
#include "R/Utf8Writer.h"

#include "R/Value.h"

#include "R/Void.h"

R_Status
R_startup
  (
  );

R_Status
R_shutdown
  (
  );

#endif // R_H_INCLUDED
