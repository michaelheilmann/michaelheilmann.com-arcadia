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

#if !defined(ARCADIA_VISUALS_WINDOWS_BMPIMAGEWRITER_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS_BMPIMAGEWRITER_H_INCLUDED

#include "Arcadia/Imaging/Windows/WicImageWriterBase.h"

Arcadia_declareObjectType(u8"Arcadia.Imaging.Windows.BmpImageWriter", Arcadia_Imaging_Windows_BmpImageWriter,
                          u8"Arcadia.Imaging.Windows.WicImageWriterBase");

struct Arcadia_Imaging_Windows_BmpImageWriter {
  Arcadia_Imaging_Windows_WicImageWriterBase _parent;
  Arcadia_ImmutableList* supportedTypes;
};

Arcadia_Imaging_Windows_BmpImageWriter*
Arcadia_Imaging_Windows_BmpImageWriter_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_WINDOWS_BMPIMAGEWRITER_H_INCLUDED
