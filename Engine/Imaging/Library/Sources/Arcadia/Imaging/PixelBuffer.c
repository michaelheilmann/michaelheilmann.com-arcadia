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

#include "Arcadia/Imaging/PixelBuffer.h"

#include "Arcadia/Ring2/Include.h"

typedef struct PIXEL {
  Arcadia_Natural8Value r, g, b, a;
} PIXEL;

static void inline
DECODE_ABGR
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  pixel->a = *(p + 0);
  pixel->b = *(p + 1);
  pixel->g = *(p + 2);
  pixel->r = *(p + 3);
}

static void inline
DECODE_ARGB
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  pixel->a = *(p + 0);
  pixel->r = *(p + 1);
  pixel->g = *(p + 2);
  pixel->b = *(p + 3);
}

static void inline
DECODE_BGR
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  pixel->b = *(p + 0);
  pixel->g = *(p + 1);
  pixel->r = *(p + 2);
  pixel->a = 255;
}

static void inline
DECODE_BGRA
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  pixel->b = *(p + 0);
  pixel->g = *(p + 1);
  pixel->r = *(p + 2);
  pixel->a = *(p + 3);
}

static void inline
DECODE_RGB
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  pixel->r = *(p + 0);
  pixel->g = *(p + 1);
  pixel->b = *(p + 2);
  pixel->a = 255;
}

static void inline
DECODE_RGBA
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  pixel->r = *(p + 0);
  pixel->g = *(p + 1);
  pixel->b = *(p + 2);
  pixel->a = *(p + 3);
}

static void inline
ENCODE_ABGR
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  *(p + 0) = pixel->a;
  *(p + 1) = pixel->b;
  *(p + 2) = pixel->g;
  *(p + 3) = pixel->r;
}

static void inline
ENCODE_ARGB
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  *(p + 0)=  pixel->a;
  *(p + 1) = pixel->r;
  *(p + 2) = pixel->g;
  *(p + 3) = pixel->b;
}

static void inline
ENCODE_BGR
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  *(p + 0) = pixel->b;
  *(p + 1) = pixel->g;
  *(p + 2) = pixel->r;
}

static void inline
ENCODE_BGRA
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  *(p + 0) = pixel->b;
  *(p + 1) = pixel->g;
  *(p + 2) = pixel->r;
  *(p + 3) = pixel->a;
}

static void inline
ENCODE_RGB
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  *(p + 0) = pixel->r;
  *(p + 1) = pixel->g;
  *(p + 2) = pixel->b;
}

static void inline
ENCODE_RGBA
  (
    Arcadia_Natural8Value* p,
    PIXEL* pixel
  )
{
  *(p + 0) = pixel->r;
  *(p + 1) = pixel->g;
  *(p + 2) = pixel->b;
  *(p + 3) = pixel->a;
}

typedef void (TranscodeCallback)(Arcadia_Natural8Value*, PIXEL*);

static void
getTranscodeCallbacks
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value source,
    size_t* sourceNumberOfBytesPerPixel,
    TranscodeCallback** decode,
    Arcadia_Natural8Value target,
    size_t* targetNumberOfBytesPerPixel,
    TranscodeCallback** encode
  )
{
  typedef struct Entry {
    Arcadia_Natural8Value pixelFormat;
    size_t numberOfBytesPerPixel;
    TranscodeCallback* decodeCallback;
    TranscodeCallback* encodeCallback;
  } Entry;

  static const Entry g_entries[] = {
    { Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8, 4, &DECODE_ABGR, &ENCODE_ABGR },
    { Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8, 4, &DECODE_ARGB, &ENCODE_ARGB },
    { Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8,    3, &DECODE_BGR,  &ENCODE_BGR  },
    { Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8, 4, &DECODE_BGRA, &ENCODE_BGRA },
    { Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8,    3, &DECODE_RGB,  &ENCODE_RGB  },
    { Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8, 4, &DECODE_RGBA, &ENCODE_RGBA },
  };

  static const size_t g_numberOfEntries = sizeof(g_entries) / sizeof(Entry);

  Entry const* sourceEntry = NULL;
  for (size_t i = 0, n = g_numberOfEntries; i < n; ++i) {
    if (g_entries[i].pixelFormat == source) {
      sourceEntry = &g_entries[i];
      break;
    }
  }

  Entry const* targetEntry = NULL;
  for (size_t i = 0, n = g_numberOfEntries; i < n; ++i) {
    if (g_entries[i].pixelFormat == target) {
      targetEntry = &g_entries[i];
      break;
    }
  }

  if (!sourceEntry || !targetEntry) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }

  *decode = sourceEntry->decodeCallback;
  *sourceNumberOfBytesPerPixel = sourceEntry->numberOfBytesPerPixel;
  *encode = targetEntry->encodeCallback;
  *targetNumberOfBytesPerPixel = targetEntry->numberOfBytesPerPixel;
}

/// @code
/// construct(linePadding:Integer32,width:Integer32,height:Integer32,pixelFormat:Natural8)
/// @endcode
///
/// @code
/// construct(pixelBuffer:Arcadia.Imaging.PixelBuffer)
/// @endcode
static void
Arcadia_Imaging_PixelBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

static void
Arcadia_Imaging_PixelBuffer_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Imaging_PixelBuffer_constructImpl,
  .destruct = (Arcadia_Object_DestructorCallbackFunction*)&Arcadia_Imaging_PixelBuffer_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.PixelBuffer", Arcadia_Imaging_PixelBuffer,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Imaging_PixelBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value numberOfArgumentValues1 = Arcadia_ValueStack_getNatural8Value(thread, 0);

  if (1 == numberOfArgumentValues1) {
    Arcadia_TypeValue _type = _Arcadia_Imaging_PixelBuffer_getType(thread);
    {
      Arcadia_ValueStack_pushNatural8Value(thread, 0);
      Arcadia_superTypeConstructor(thread, _type, self);
    }
    Arcadia_Imaging_PixelBuffer* other = (Arcadia_Imaging_PixelBuffer*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Imaging_PixelBuffer_getType(thread));
    self->width = Arcadia_Imaging_PixelBuffer_getNumberOfColumns(thread, other);
    self->height = Arcadia_Imaging_PixelBuffer_getNumberOfRows(thread, other);
    self->linePadding = Arcadia_Imaging_PixelBuffer_getLinePadding(thread, other);
    self->pixelFormat = Arcadia_Imaging_PixelBuffer_getPixelFormat(thread, other);
    Arcadia_SizeValue bytesPerPixel = Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, other);
    Arcadia_SizeValue bytes = (bytesPerPixel * self->width + self->linePadding) * self->height;
    self->bytes = Arcadia_Memory_allocateUnmanaged(thread, bytes);
    Arcadia_Memory_copy(thread, self->bytes, other->bytes, bytes);
    Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
    Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
  } else if (4 == numberOfArgumentValues1) {
    Arcadia_TypeValue _type = _Arcadia_Imaging_PixelBuffer_getType(thread);
    {
      Arcadia_ValueStack_pushNatural8Value(thread, 0);
      Arcadia_superTypeConstructor(thread, _type, self);
    }
    self->bytes = NULL;
    self->linePadding = Arcadia_ValueStack_getInteger32Value(thread, 4);
    self->width = Arcadia_ValueStack_getInteger32Value(thread, 3);
    self->height = Arcadia_ValueStack_getInteger32Value(thread, 2);
    self->pixelFormat = Arcadia_ValueStack_getNatural32Value(thread, 1);

    Arcadia_SizeValue bytesPerPixel = 0;
    switch (self->pixelFormat) {
      case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8:
      case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8:
      case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8:
      case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
        bytesPerPixel = 4;
      } break;
      case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8:
      case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
        bytesPerPixel = 3;
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
    self->bytes = Arcadia_Memory_allocateUnmanaged(thread, (self->width * bytesPerPixel + self->linePadding) * self->height);
    switch (self->pixelFormat) {
      case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8: {
        Arcadia_SizeValue lineStride = self->width * bytesPerPixel + self->linePadding;
        for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
          Arcadia_Natural8Value* p = self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_ABGR(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8: {
        Arcadia_SizeValue lineStride = self->width * bytesPerPixel + self->linePadding;
        for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
          Arcadia_Natural8Value* p = self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_ARGB(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8: {
        Arcadia_SizeValue lineStride = self->width * bytesPerPixel + self->linePadding;
        for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
          Arcadia_Natural8Value* p = self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_BGR(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8: {
        Arcadia_SizeValue lineStride = self->width * bytesPerPixel + self->linePadding;
        for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
          Arcadia_Natural8Value* p = self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_BGRA(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
        Arcadia_SizeValue lineStride = self->width * bytesPerPixel + self->linePadding;
        for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
          Arcadia_Natural8Value* p = self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_RGB(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
        Arcadia_SizeValue lineStride = self->width * bytesPerPixel + self->linePadding;
        for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
          Arcadia_Natural8Value* p = self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_RGBA(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
    Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
    Arcadia_ValueStack_popValues(thread, numberOfArgumentValues1 + 1);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
Arcadia_Imaging_PixelBuffer_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{
  if (self->bytes) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->bytes);
    self->bytes = NULL;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Natural8Value
Arcadia_Imaging_PixelBuffer_getPixelFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{
  return self->pixelFormat;
}

void
Arcadia_Imaging_PixelBuffer_setPixelFormat
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Natural8Value pixelFormat
  )
{
  if (pixelFormat == self->pixelFormat) {
    return;
  }
  TranscodeCallback* decodeCallback = NULL;
  size_t sourceNumberOfBytesPerPixel = 0;
  TranscodeCallback* encodeCallback = NULL;
  size_t targetNumberOfBytesPerPixel = 0;
  getTranscodeCallbacks(thread, self->pixelFormat, &sourceNumberOfBytesPerPixel, &decodeCallback, pixelFormat, &targetNumberOfBytesPerPixel, &encodeCallback);

  Arcadia_Natural8Value* sourceBytes = self->bytes;
  Arcadia_Natural8Value* targetBytes = NULL;
  if (sourceNumberOfBytesPerPixel != targetNumberOfBytesPerPixel) {
    targetBytes = Arcadia_Memory_allocateUnmanaged(thread, (self->width * sourceNumberOfBytesPerPixel + self->linePadding) * self->height);
  } else {
    targetBytes = self->bytes;
  }

  Arcadia_SizeValue sourceLineStride = self->width * sourceNumberOfBytesPerPixel + self->linePadding;
  Arcadia_SizeValue targetLineStride = self->width * targetNumberOfBytesPerPixel + self->linePadding;
  for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
    Arcadia_Natural8Value* p = sourceBytes + (y * sourceLineStride);
    Arcadia_Natural8Value* q = targetBytes + (y * targetLineStride);
    for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
      PIXEL pixel;
      (*decodeCallback)(p + x * sourceNumberOfBytesPerPixel, &pixel);
      (*encodeCallback)(q + x * targetNumberOfBytesPerPixel, &pixel);
    }
  }
  if (sourceNumberOfBytesPerPixel != targetNumberOfBytesPerPixel) {
    Arcadia_Memory_deallocateUnmanaged(thread, sourceBytes);
    self->bytes = targetBytes;
  }
  self->pixelFormat = pixelFormat;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getLinePadding
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{ return self->linePadding; }

void
Arcadia_Imaging_PixelBuffer_setLinePadding
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value linePadding
  )
{
  if (self->linePadding != linePadding) {
    if (linePadding < 0) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Integer32Value bytesPerPixel = 0;
    switch (self->pixelFormat) {
      case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8:
      case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8:
      case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8:
      case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8:
      {
        bytesPerPixel = 4;
      } break;
      case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8:
      case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
        bytesPerPixel = 3;
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    }
    Arcadia_Integer32Value oldLinePadding = self->linePadding;
    Arcadia_Integer32Value newLinePadding = linePadding;
    Arcadia_Natural8Value* oldBytes = self->bytes;
    Arcadia_Natural8Value* newBytes = NULL;
    newBytes = Arcadia_Memory_allocateUnmanaged(thread, (self->width * bytesPerPixel + newLinePadding) * self->height);
    for (Arcadia_SizeValue rowIndex = 0; rowIndex < self->height; ++rowIndex) {
      Arcadia_Natural8Value* oldLine = oldBytes + rowIndex * (self->width * bytesPerPixel + oldLinePadding);
      Arcadia_Natural8Value* newLine = newBytes + rowIndex * (self->width * bytesPerPixel + newLinePadding);
      Arcadia_Memory_copy(thread, newLine, oldLine, self->width * bytesPerPixel);
    }
    Arcadia_Memory_deallocateUnmanaged(thread, oldBytes);
    self->bytes = newBytes;
    self->linePadding = linePadding;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Arcadia_Imaging_PixelBuffer_getPixelRgba
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value column,
    Arcadia_Integer32Value row,
    Arcadia_Natural8Value* r,
    Arcadia_Natural8Value* g,
    Arcadia_Natural8Value* b,
    Arcadia_Natural8Value* a
  )
{
  if (column < 0 || column > Arcadia_Imaging_PixelBuffer_getNumberOfColumns(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (row < 0 || row > Arcadia_Imaging_PixelBuffer_getNumberOfRows(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue offset = row * Arcadia_Imaging_PixelBuffer_getLineStride(thread, self) + column * Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Natural8Value* bytes = self->bytes + offset;
  PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
  switch (self->pixelFormat) {
    case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8: {
      DECODE_ABGR(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8: {
      DECODE_ARGB(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8: {
      DECODE_BGR(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8: {
      DECODE_BGRA(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
      DECODE_RGB(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
      DECODE_RGBA(bytes, &pixel);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
  *r = pixel.r;
  *g = pixel.g;
  *b = pixel.b;
  *a = pixel.a;
}

void
Arcadia_Imaging_PixelBuffer_setPixelRgba
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value column,
    Arcadia_Integer32Value row,
    Arcadia_Natural8Value r,
    Arcadia_Natural8Value g,
    Arcadia_Natural8Value b,
    Arcadia_Natural8Value a
  )
{
  if (column < 0 || column >= Arcadia_Imaging_PixelBuffer_getNumberOfColumns(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (row < 0 || row >= Arcadia_Imaging_PixelBuffer_getNumberOfRows(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue offset = row * Arcadia_Imaging_PixelBuffer_getLineStride(thread, self) + column * Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Natural8Value* bytes = self->bytes + offset;
  PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
  switch (self->pixelFormat) {
    case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8: {
      ENCODE_ABGR(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8: {
      ENCODE_ARGB(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8: {
      ENCODE_BGR(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8: {
      ENCODE_BGRA(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
      ENCODE_RGB(bytes, &pixel);
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
      ENCODE_RGBA(bytes, &pixel);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Arcadia_Imaging_PixelBuffer_fill
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Natural8Value r,
    Arcadia_Natural8Value g,
    Arcadia_Natural8Value b,
    Arcadia_Natural8Value a
  )
{
  switch (self->pixelFormat) {
    case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8: {
      Arcadia_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
          ENCODE_ABGR(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8: {
      Arcadia_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
          ENCODE_ARGB(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8: {
      Arcadia_SizeValue bytesPerPixel = 3;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
          ENCODE_BGR(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8: {
      Arcadia_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
          ENCODE_BGRA(p + x * bytesPerPixel, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
      Arcadia_SizeValue bytesPerPixel = 3;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
          ENCODE_RGB(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
      Arcadia_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->height; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->width; ++x) {
          ENCODE_RGBA(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Arcadia_Imaging_PixelBuffer_swapColumns
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value column1,
    Arcadia_Integer32Value column2
  )
{
  if (column1 < 0 || column1 >= self->width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (column2 < 0 || column2 >= self->width) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (column1 == column2) {
    return;
  }
  Arcadia_Integer32Value bytesPerPixel = Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Integer32Value lineStride = Arcadia_Imaging_PixelBuffer_getLineStride(thread, self);
  Arcadia_Natural8Value* source = self->bytes + column1 * Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Natural8Value* target = self->bytes + column2 * Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, self);
  for (Arcadia_SizeValue row = 0; row < self->height; ++row) {
    Arcadia_Memory_swap(thread, source, target, bytesPerPixel);
    source += lineStride;
    target += lineStride;
  }
}

void
Arcadia_Imaging_PixelBuffer_swapRows
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self,
    Arcadia_Integer32Value row1,
    Arcadia_Integer32Value row2
  )
{
  if (row1 < 0 || row1 >= self->height) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (row2 < 0 || row2 >= self->height) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (row1 == row2) {
    return;
  }
  Arcadia_Integer32Value bytesPerPixel = Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Natural8Value* source = self->bytes + Arcadia_Imaging_PixelBuffer_getLineStride(thread, self) * row1;
  Arcadia_Natural8Value* target = self->bytes + Arcadia_Imaging_PixelBuffer_getLineStride(thread, self) * row2;
  Arcadia_Memory_swap(thread, source, target, self->width * bytesPerPixel);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Arcadia_Imaging_PixelBuffer_reflectVertically
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{
  for (Arcadia_Integer32Value column = 0, w = self->width / 2; column < w; ++column) {
    Arcadia_Imaging_PixelBuffer_swapColumns(thread, self, column, self->width - 1 - column);
  }
}

void
Arcadia_Imaging_PixelBuffer_reflectHorizontally
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{
  for (Arcadia_Integer32Value row = 0, h = self->height / 2; row < h; ++row) {
    Arcadia_Imaging_PixelBuffer_swapRows(thread, self, row, self->height - 1 - row);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getNumberOfColumns
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{ return self->width; }

Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getNumberOfRows
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{ return self->height; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getLineStride
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{ return Arcadia_Imaging_PixelBuffer_getNumberOfColumns(thread, self)
       * Arcadia_Imaging_PixelBuffer_getBytesPerPixel(thread, self)
       + Arcadia_Imaging_PixelBuffer_getLinePadding(thread, self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getBytesPerPixel
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{
  size_t bytesPerPixel = 0;
  switch (self->pixelFormat) {
    case Arcadia_Imaging_PixelFormat_An8Bn8Gn8Rn8:
    case Arcadia_Imaging_PixelFormat_An8Rn8Gn8Bn8:
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8An8:
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8An8: {
      bytesPerPixel = 4;
    } break;
    case Arcadia_Imaging_PixelFormat_Bn8Gn8Rn8:
    case Arcadia_Imaging_PixelFormat_Rn8Gn8Bn8: {
      bytesPerPixel = 3;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
  return bytesPerPixel;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Imaging_PixelBuffer*
Arcadia_Imaging_PixelBuffer_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value linePadding,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value pixelFormat
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushInteger32Value(thread, linePadding);
  Arcadia_ValueStack_pushInteger32Value(thread, width);
  Arcadia_ValueStack_pushInteger32Value(thread, height);
  Arcadia_ValueStack_pushNatural32Value(thread, pixelFormat);
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_Imaging_PixelBuffer);
}

Arcadia_Imaging_PixelBuffer*
Arcadia_Imaging_PixelBuffer_createClone
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* other
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (other) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, other);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Imaging_PixelBuffer);
}

Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{ return self->width; }

Arcadia_Integer32Value
Arcadia_Imaging_PixelBuffer_getHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_PixelBuffer* self
  )
{ return self->height; }
