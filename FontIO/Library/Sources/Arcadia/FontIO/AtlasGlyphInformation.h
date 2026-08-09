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

#if !defined(ARCADIA_FONTIO_ATLASGLYPHINFORMATION_H_INCLUDED)
#define ARCADIA_FONTIO_ATLASGLYPHINFORMATION_H_INCLUDED

#include "Arcadia/Media/Include.h"
#include "Arcadia/FontIO/GlyphInformation.h"

/// @brief Information about a glyph image stored within the atlas of an atlas bitmap font.
typedef struct Arcadia_FontIO_AtlasGlyphInformation {

  /// The information about the glyph image.
  Arcadia_FontIO_GlyphInformation glyphInformation;

  /// The position, in pixels, of the left edge of the glyph image within the atlas.
  Arcadia_Integer32Value x;

  /// The position, in pixels, of the top edge of the glyph image within the atlas.
  Arcadia_Integer32Value y;

} Arcadia_FontIO_AtlasGlyphInformation;

#endif // ARCADIA_FONTIO_ATLASGLYPHINFORMATION_H_INCLUDED
