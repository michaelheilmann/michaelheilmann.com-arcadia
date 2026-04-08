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

#if !defined(ARCADIA_MEDIA_INCLUDE_H_INCLUDED)
#define ARCADIA_MEDIA_INCLUDE_H_INCLUDED

// If a file x belongs to a module a and ARCADIA_a_MODULE is not defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_MEDIA_MODULE")
#define ARCADIA_MEDIA_MODULE (1)

// If a file x of a module a is not an export file of that module and ARCADIA_a_EXPORT is defined, then that file shall raise a compile-time error.
#pragma push_macro("ARCADIA_MEDIA_EXPORT")
#define ARCADIA_MEDIA_EXPORT (1)

#include "Arcadia/Media/PixelBuffer.h"
#include "Arcadia/Media/PixelBufferOperations/CheckerboardFill.h"
#include "Arcadia/Media/PixelBufferOperations/Fill.h"
#include "Arcadia/Media/PixelBufferOperation.h"
#include "Arcadia/Media/PixelFormat.h"

#include "Arcadia/Media/SampleBuffer.h"
#include "Arcadia/Media/DSP/SineWave.h"
#include "Arcadia/Media/DSP/WhiteNoise.h"
#include "Arcadia/Media/SampleFormat.h"

#undef ARCADIA_MEDIA_EXPORT
#pragma pop_macro("ARCADIA_MEDIA_EXPORT")

#undef ARCADIA_MEDIA_MODULE
#pragma pop_macro("ARCADIA_MEDIA_MODULE")

#endif // ARCADIA_MEDIA_INCLUDE_H_INCLUDED
