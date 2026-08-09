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

#if !defined(ARCADIA_FONTIO_ATLASBITMAPFONT_H_INCLUDED)
#define ARCADIA_FONTIO_ATLASBITMAPFONT_H_INCLUDED

#include "Arcadia/Media/Include.h"
#include "Arcadia/FontIO/GlyphInformation.h"
#include "Arcadia/FontIO/AtlasGlyphInformation.h"
#include "Arcadia/FontIO/BitmapFont.h"

/// @code
/// class AtlasBitmapFont {
///   construct(path:String,pixelSize:Integer32)
/// }
/// @endcode
///
/// A bitmap font which packs the glyph images it renders into a single, growing atlas.
Arcadia_declareObjectType(u8"Arcadia.FontIO.AtlasBitmapFont", Arcadia_FontIO_AtlasBitmapFont,
                          u8"Arcadia.Object");

/// @brief Create an atlas bitmap font.
/// @param thread A pointer to the thread.
/// @param path The path, in UTF-8, of the TrueType/OpenType font file backing the atlas bitmap font.
/// @param pixelSize The size, in pixels, of the glyphs of the atlas bitmap font. Must be positive.
/// @return A pointer to the atlas bitmap font. Its atlas is empty.
/// @error Arcadia_Status_ArgumentValueInvalid @a pixelSize is not positive.
/// @error Arcadia_Status_OperationInvalid The font file could not be loaded.
Arcadia_FontIO_AtlasBitmapFont*
Arcadia_FontIO_AtlasBitmapFont_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* path,
    Arcadia_Integer32Value pixelSize
  );

/// @brief Get the information of the glyph of a unicode code point.
/// If the glyph image is not part of the atlas yet, it is rendered and added to the atlas.
/// @param thread A pointer to the thread.
/// @param self A pointer to this atlas bitmap font.
/// @param codePoint The unicode code point.
/// @param target A pointer to a <code>Arcadia_FontIO_AtlasGlyphInformation</code> variable receiving the glyph information.
/// @error Arcadia_Status_ArgumentValueInvalid No glyph exists for @a codePoint.
/// @error Arcadia_Status_OperationInvalid The glyph could not be loaded or added to the atlas.
void
Arcadia_FontIO_AtlasBitmapFont_getGlyphInformation
  (
    Arcadia_Thread* thread,
    Arcadia_FontIO_AtlasBitmapFont* self,
    Arcadia_Natural32Value codePoint,
    Arcadia_FontIO_AtlasGlyphInformation* target
  );

/// @brief Get the atlas of this atlas bitmap font.
/// @param thread A pointer to the thread.
/// @param self A pointer to this atlas bitmap font.
/// @return A pointer to the atlas as a pixel buffer of the format RGBA.
/// The glyph coverage is stored in the alpha component of the pixels,
/// the red, green, and blue component values are 255.
/// @warning The returned pixel buffer may be replaced by a larger pixel buffer whenever glyphs are added to the atlas.
Arcadia_Media_PixelBuffer*
Arcadia_FontIO_AtlasBitmapFont_getAtlas
  (
    Arcadia_Thread* thread,
    Arcadia_FontIO_AtlasBitmapFont* self
  );

#endif // ARCADIA_FONTIO_ATLASBITMAPFONT_H_INCLUDED
