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

#if !defined(ARCADIA_IMAGING_IMAGEMANAGER_H_INCLUDED)
#define ARCADIA_IMAGING_IMAGEMANAGER_H_INCLUDED

#include "Arcadia/Imaging/PixelBuffer.h"

Arcadia_declareObjectType(u8"Arcadia.Imaging.ImageManager", Arcadia_Imaging_ImageManager, u8"Arcadia.Object");

struct Arcadia_Imaging_ImageManager {
  Arcadia_Object _parent;
  Arcadia_List* writers;
};

/// @brief Get or create the image manager singleton object.
/// @param thread A pointer to this thread.
/// @return A pointer to the image manager singleton object.
Arcadia_Imaging_ImageManager*
Arcadia_Imaging_ImageManager_getOrCreate
  (
    Arcadia_Thread* thread
  );

/// @brief Get a list of image writers supporting the specified extension.
/// @param thread A pointer to this thread.
/// @param self A pointer to this image manager.
/// @return A pointer to a list of image writers.
Arcadia_List*
Arcadia_Imaging_ImageManager_getWriters
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_ImageManager* self,
    Arcadia_String* extension
  );

#endif // ARCADIA_IMAGING_IMAGEMANAGER_H_INCLUDED
