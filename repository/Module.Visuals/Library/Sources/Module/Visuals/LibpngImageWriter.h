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

// Last modified: 2024-09-19

#if !defined(MODULE_VISUALS_LIBPNGIMAGEWRITER_H_INCLUDED)
#define MODULE_VISUALS_LIBPNGIMAGEWRITER_H_INCLUDED

#include "R/Include.h"
#include "Module/Visuals/ImageWriter.h"
#include "Module/Visuals/PixelBuffer.h"

Arcadia_declareObjectType(u8"LibPngImageWriter", LibPngImageWriter, u8"ImageWriter");

struct LibPngImageWriter {
  ImageWriter _parent;
};

LibPngImageWriter*
LibPngImageWriter_create
  (
    Arcadia_Thread* thread
  );

#endif // MODULE_VISUALS_LIBPNGIMAGEWRITER_H_INCLUDED
