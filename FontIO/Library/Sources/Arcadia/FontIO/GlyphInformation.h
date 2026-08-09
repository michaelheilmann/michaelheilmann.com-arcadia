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

#if !defined(ARCADIA_FONTIO_GLYPHINFORMATION_H_INCLUDED)
#define ARCADIA_FONTIO_GLYPHINFORMATION_H_INCLUDED

#include "Arcadia/Media/Include.h"

/// @brief Information about a glyph.
/// All values are in pixels.
typedef struct Arcadia_FontIO_GlyphInformation {

  /// The width of the glyph image.
  Arcadia_Integer32Value width;

  /// The height of the glyph image.
  Arcadia_Integer32Value height;

  /// The distance in left direction from the pen position to the left edge of the glyph image.
  /// A positive value indicates that the glyph image extends to the right of the pen position,
  /// a negative value indicates that it extends to the left of the pen position.
  Arcadia_Integer32Value bearingX;

  /// The distance in upwards direction from the pen position on the baseline to the top edge of the glyph image.
  /// Usually positive.
  Arcadia_Integer32Value bearingY;

  /// The distance the pen position is advanced in right direction to render the next glyph.
  Arcadia_Integer32Value advanceX;

  /// The distance the pen position is advanced in downwards direction to render the next glyph.
  /// Usually zero for horizontal layouts.
  Arcadia_Integer32Value advanceY;

} Arcadia_FontIO_GlyphInformation;

#endif // ARCADIA_FONTIO_GLYPHINFORMATION_H_INCLUDED
