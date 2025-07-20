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

#if !defined(ARCADIA_IMAGING_WINDOWS_WICIMAGEWRITERBASE_H_INCLUDED)
#define ARCADIA_IMAGING_WINDOWS_WICIMAGEWRITERBASE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Imaging/ImageWriter.h"
#include "Arcadia/Imaging/ImageWriterParameters.h"
#include "Arcadia/Imaging/PixelBuffer.h"

// WIC header
#define COBJMACROS (1)
#include <wincodec.h>

Arcadia_declareObjectType(u8"Arcadia.Imaging.Windows.WicImageWriterBase", Arcadia_Imaging_Windows_WicImageWriterBase,
                          u8"Arcadia.Imaging.ImageWriter");

struct Arcadia_Imaging_Windows_WicImageWriterBase {
  Arcadia_Imaging_ImageWriter _parent;

  IWICImagingFactory* piFactory;
  HGLOBAL hMemory;
  IStream* piMemoryStream; // NULL if there is no memory stream
  IWICStream* piStream;
  IWICBitmapEncoder* piEncoder;

  IWICBitmapFrameEncode* piBitmapFrame;
  IPropertyBag2* pPropertyBag;
  
  void (*getFormat)(Arcadia_Thread* thread, Arcadia_Imaging_Windows_WicImageWriterBase* self, Arcadia_Visuals_PixelBuffer* sourcePixelBuffer, Arcadia_Imaging_ImageWriterParameters* parameters, GUID const** guid);
  void (*configure)(Arcadia_Thread* thread, Arcadia_Imaging_Windows_WicImageWriterBase* self, Arcadia_Visuals_PixelBuffer* sourcePixelBuffer, Arcadia_Imaging_ImageWriterParameters* parameters);
};
  
void
Arcadia_Imaging_Windows_WicImageWriterBase_doWrite
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Windows_WicImageWriterBase* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_Imaging_ImageWriterParameters* parameters
  );

#endif // ARCADIA_IMAGING_WINDOWS_WICIMAGEWRITERBASE_H_INCLUDED
