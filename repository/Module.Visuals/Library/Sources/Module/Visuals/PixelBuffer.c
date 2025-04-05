// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-07

#include "Module/Visuals/PixelBuffer.h"

#include "R/Include.h"

/* TODO: Add this to Arcadia_Process_swapMemory. */
static inline void
Memory_swap
  (
    Arcadia_Natural8Value* target,
    Arcadia_Natural8Value* source,
    size_t count
  )
{
  for (size_t i = 0, n = count; i < n; ++i) {
    Arcadia_Natural8Value temporary = *source;
    *source = *target;
    *target = temporary;
    source++;
    target++;
  }
}

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
    { Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8, 4, &DECODE_ABGR, &ENCODE_ABGR },
    { Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8, 4, &DECODE_ARGB, &ENCODE_ARGB },
    { Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8,    3, &DECODE_BGR,  &ENCODE_BGR  },
    { Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8, 4, &DECODE_BGRA, &ENCODE_BGRA },
    { Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8,    3, &DECODE_RGB,  &ENCODE_RGB  },
    { Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8, 4, &DECODE_RGBA, &ENCODE_RGBA },
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
/// construct(pixelBuffer:PixelBuffer)
/// @endcode
static void
PixelBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
PixelBuffer_destruct
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &PixelBuffer_constructImpl,
  .destruct = &PixelBuffer_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Arcadia_defineObjectType(u8"PixelBuffer", PixelBuffer, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
PixelBuffer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  if (1 == numberOfArgumentValues) {
    PixelBuffer* _self = Arcadia_Value_getObjectReferenceValue(self);
    Arcadia_TypeValue _type = _PixelBuffer_getType(thread);
    {
      Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
      Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
    }
    if (!Arcadia_Type_isSubType(thread, Arcadia_Value_getType(thread, &argumentValues[0]), _PixelBuffer_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    PixelBuffer* other = (PixelBuffer*)Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
    _self->numberOfColumns = PixelBuffer_getNumberOfColumns(thread, other);
    _self->numberOfRows = PixelBuffer_getNumberOfRows(thread, other);
    _self->linePadding = PixelBuffer_getLinePadding(thread, other);
    _self->pixelFormat = PixelBuffer_getPixelFormat(thread, other);
    Arcadia_SizeValue bytesPerPixel = PixelBuffer_getBytesPerPixel(thread, other);
    Arcadia_SizeValue bytes = (bytesPerPixel * _self->numberOfColumns + _self->linePadding) * _self->numberOfRows;
    Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &_self->bytes, bytes);
    Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), _self->bytes, other->bytes, bytes);
    Arcadia_Object_setType(thread, _self, _type);
  } else if (4 == numberOfArgumentValues) {
    Arcadia_TypeValue _type = _PixelBuffer_getType(thread);
    PixelBuffer* _self = Arcadia_Value_getObjectReferenceValue(self);
    {
      Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
      Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
    }
    if (!Arcadia_Value_isInteger32Value(&argumentValues[0])) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (!Arcadia_Value_isInteger32Value(&argumentValues[1])) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (!Arcadia_Value_isInteger32Value(&argumentValues[2])) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (!Arcadia_Value_isNatural32Value(&argumentValues[3])) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Thread_jump(thread);
    }
    _self->bytes = NULL;
    _self->pixelFormat = Arcadia_Value_getNatural32Value(&argumentValues[3]);
    _self->numberOfColumns = Arcadia_Value_getInteger32Value(&argumentValues[1]);
    _self->numberOfRows = Arcadia_Value_getInteger32Value(&argumentValues[2]);
    _self->linePadding = Arcadia_Value_getInteger32Value(&argumentValues[0]);
    Arcadia_SizeValue bytesPerPixel = 0;
    switch (_self->pixelFormat) {
      case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8:
      case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8:
      case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8:
      case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8: {
        bytesPerPixel = 4;
      } break;
      case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8:
      case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
        bytesPerPixel = 3;
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
    Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &_self->bytes, (_self->numberOfColumns * bytesPerPixel + _self->linePadding) * _self->numberOfRows);
    switch (_self->pixelFormat) {
      case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8: {
        Arcadia_SizeValue lineStride = _self->numberOfColumns * bytesPerPixel + _self->linePadding;
        for (Arcadia_SizeValue y = 0; y < _self->numberOfRows; ++y) {
          Arcadia_Natural8Value* p = _self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < _self->numberOfColumns; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_ABGR(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8: {
        Arcadia_SizeValue lineStride = _self->numberOfColumns * bytesPerPixel + _self->linePadding;
        for (Arcadia_SizeValue y = 0; y < _self->numberOfRows; ++y) {
          Arcadia_Natural8Value* p = _self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < _self->numberOfColumns; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_ARGB(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8: {
        Arcadia_SizeValue lineStride = _self->numberOfColumns * bytesPerPixel + _self->linePadding;
        for (Arcadia_SizeValue y = 0; y < _self->numberOfRows; ++y) {
          Arcadia_Natural8Value* p = _self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < _self->numberOfColumns; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_BGR(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
        Arcadia_SizeValue lineStride = _self->numberOfColumns * bytesPerPixel + _self->linePadding;
        for (Arcadia_SizeValue y = 0; y < _self->numberOfRows; ++y) {
          Arcadia_Natural8Value* p = _self->bytes + (y * lineStride);
          for (Arcadia_SizeValue x = 0; x < _self->numberOfColumns; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_RGB(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      default: {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      } break;
    };
    Arcadia_Object_setType(thread, _self, _type);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
PixelBuffer_destruct
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{
  if (self->bytes) {
    Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), self->bytes);
    self->bytes = NULL;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Natural8Value
PixelBuffer_getPixelFormat
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{
  return self->pixelFormat;
}

void
PixelBuffer_setPixelFormat
  (
    Arcadia_Thread* thread,
    PixelBuffer* self,
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
    Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &targetBytes, (self->numberOfColumns * sourceNumberOfBytesPerPixel + self->linePadding) * self->numberOfRows);
  } else {
    targetBytes = self->bytes;
  }

  Arcadia_SizeValue sourceLineStride = self->numberOfColumns * sourceNumberOfBytesPerPixel + self->linePadding;
  Arcadia_SizeValue targetLineStride = self->numberOfColumns * targetNumberOfBytesPerPixel + self->linePadding;
  for (Arcadia_SizeValue y = 0; y < self->numberOfRows; ++y) {
    Arcadia_Natural8Value* p = sourceBytes + (y * sourceLineStride);
    Arcadia_Natural8Value* q = targetBytes + (y * targetLineStride);
    for (Arcadia_SizeValue x = 0; x < self->numberOfColumns; ++x) {
      PIXEL pixel;
      (*decodeCallback)(p + x * sourceNumberOfBytesPerPixel, &pixel);
      (*encodeCallback)(q + x * targetNumberOfBytesPerPixel, &pixel);
    }
  }
  if (sourceNumberOfBytesPerPixel != targetNumberOfBytesPerPixel) {
    Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), sourceBytes);
    self->bytes = targetBytes;
  }
  self->pixelFormat = pixelFormat;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Integer32Value
PixelBuffer_getLinePadding
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{ return self->linePadding; }

void
PixelBuffer_setLinePadding
  (
    Arcadia_Thread* thread,
    PixelBuffer* self,
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
      case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8:
      case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8:
      case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8:
      case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8:
      {
        bytesPerPixel = 4;
      } break;
      case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8:
      case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
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
    Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &newBytes, (self->numberOfColumns * bytesPerPixel + newLinePadding) * self->numberOfRows);
    for (Arcadia_SizeValue rowIndex = 0; rowIndex < self->numberOfRows; ++rowIndex) {
      Arcadia_Natural8Value* oldLine = oldBytes + rowIndex * (self->numberOfColumns * bytesPerPixel + oldLinePadding);
      Arcadia_Natural8Value* newLine = newBytes + rowIndex * (self->numberOfColumns * bytesPerPixel + newLinePadding);
      Arcadia_Process_copyMemory(Arcadia_Thread_getProcess(thread), newLine, oldLine, self->numberOfColumns * bytesPerPixel);
    }
    Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), oldBytes);
    self->bytes = newBytes;
    self->linePadding = linePadding;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
PixelBuffer_getPixelRgba
  (
    Arcadia_Thread* thread,
    PixelBuffer* self,
    Arcadia_Integer32Value column,
    Arcadia_Integer32Value row,
    Arcadia_Natural8Value* r,
    Arcadia_Natural8Value* g,
    Arcadia_Natural8Value* b,
    Arcadia_Natural8Value* a
  )
{
  if (column < 0 || column > PixelBuffer_getNumberOfColumns(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (row < 0 || row > PixelBuffer_getNumberOfRows(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue offset = row * PixelBuffer_getLineStride(thread, self) + column * PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Natural8Value* bytes = self->bytes + offset;
  PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
  switch (self->pixelFormat) {
    case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8: {
      DECODE_ABGR(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8: {
      DECODE_ARGB(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8: {
      DECODE_BGR(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8: {
      DECODE_BGRA(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
      DECODE_RGB(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8: {
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
PixelBuffer_setPixelRgba
  (
    Arcadia_Thread* thread,
    PixelBuffer* self,
    Arcadia_Integer32Value column,
    Arcadia_Integer32Value row,
    Arcadia_Natural8Value r,
    Arcadia_Natural8Value g,
    Arcadia_Natural8Value b,
    Arcadia_Natural8Value a
  )
{
  if (column < 0 || column >= PixelBuffer_getNumberOfColumns(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (row < 0 || row >= PixelBuffer_getNumberOfRows(thread, self)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue offset = row * PixelBuffer_getLineStride(thread, self) + column * PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Natural8Value* bytes = self->bytes + offset;
  PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
  switch (self->pixelFormat) {
    case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8: {
      ENCODE_ABGR(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8: {
      ENCODE_ARGB(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8: {
      ENCODE_BGR(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8: {
      ENCODE_BGRA(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
      ENCODE_RGB(bytes, &pixel);
    } break;
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8: {
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
PixelBuffer_fill
  (
    Arcadia_Thread* thread,
    PixelBuffer* self,
    Arcadia_Natural8Value r,
    Arcadia_Natural8Value g,
    Arcadia_Natural8Value b,
    Arcadia_Natural8Value a
  )
{
  switch (self->pixelFormat) {
    case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8: {
      Arcadia_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_ABGR(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8: {
      Arcadia_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_ARGB(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8: {
      Arcadia_SizeValue bytesPerPixel = 3;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_BGR(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8: {
      Arcadia_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_BGRA(p + x * bytesPerPixel, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
      Arcadia_SizeValue bytesPerPixel = 3;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_RGB(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8: {
      Arcadia_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      Arcadia_Natural8Value* p = self->bytes;
      for (Arcadia_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (Arcadia_SizeValue x = 0; x < self->numberOfColumns; ++x) {
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
PixelBuffer_swapColumns
  (
    Arcadia_Thread* thread,
    PixelBuffer* self,
    Arcadia_Integer32Value column1,
    Arcadia_Integer32Value column2
  )
{
  if (column1 < 0 || column1 >= self->numberOfColumns) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (column2 < 0 || column2 >= self->numberOfColumns) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (column1 == column2) {
    return;
  }
  Arcadia_Integer32Value bytesPerPixel = PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Integer32Value lineStride = PixelBuffer_getLineStride(thread, self);
  Arcadia_Natural8Value* source = self->bytes + column1 * PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Natural8Value* target = self->bytes + column2 * PixelBuffer_getBytesPerPixel(thread, self);
  for (Arcadia_SizeValue row = 0; row < self->numberOfRows; ++row) {
    Memory_swap(source, target, bytesPerPixel);
    source += lineStride;
    target += lineStride;
  }
}

void
PixelBuffer_swapRows
  (
    Arcadia_Thread* thread,
    PixelBuffer* self,
    Arcadia_Integer32Value row1,
    Arcadia_Integer32Value row2
  )
{
  if (row1 < 0 || row1 >= self->numberOfRows) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (row2 < 0 || row2 >= self->numberOfRows) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (row1 == row2) {
    return;
  }
  Arcadia_Integer32Value bytesPerPixel = PixelBuffer_getBytesPerPixel(thread, self);
  Arcadia_Natural8Value* source = self->bytes + PixelBuffer_getLineStride(thread, self) * row1;
  Arcadia_Natural8Value* target = self->bytes + PixelBuffer_getLineStride(thread, self) * row2;
  Memory_swap(source, target, self->numberOfColumns * bytesPerPixel);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
PixelBuffer_reflectVertically
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{
  for (Arcadia_Integer32Value column = 0, w = self->numberOfColumns / 2; column < w; ++column) {
    PixelBuffer_swapColumns(thread, self, column, self->numberOfColumns - 1 - column);
  }
}

void
PixelBuffer_reflectHorizontally
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{
  for (Arcadia_Integer32Value row = 0, h = self->numberOfRows / 2; row < h; ++row) {
    PixelBuffer_swapRows(thread, self, row, self->numberOfRows - 1 - row);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Integer32Value
PixelBuffer_getNumberOfColumns
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{ return self->numberOfColumns; }

Arcadia_Integer32Value
PixelBuffer_getNumberOfRows
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{ return self->numberOfRows; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Integer32Value
PixelBuffer_getLineStride
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{ return PixelBuffer_getNumberOfColumns(thread, self)
       * PixelBuffer_getBytesPerPixel(thread, self)
       + PixelBuffer_getLinePadding(thread, self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Arcadia_Integer32Value
PixelBuffer_getBytesPerPixel
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{
  size_t bytesPerPixel = 0;
  switch (self->pixelFormat) {
    case Arcadia_Visuals_PixelFormat_An8Bn8Gn8Rn8:
    case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8:
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8:
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8An8: {
      bytesPerPixel = 4;
    } break;
    case Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8:
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
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

PixelBuffer*
PixelBuffer_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value linePadding,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height,
    Arcadia_Natural8Value pixelFormat
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Integer32, .integer32Value = linePadding },
                               {.tag = Arcadia_ValueTag_Integer32, .integer32Value = width },
                               {.tag = Arcadia_ValueTag_Integer32, .integer32Value = height },
                               {.tag = Arcadia_ValueTag_Natural32, .natural32Value = pixelFormat } };
  PixelBuffer* self = Arcadia_allocateObject(thread, _PixelBuffer_getType(thread), 4, &argumentValues[0]);
  return self;
}

PixelBuffer*
PixelBuffer_createClone
  (
    Arcadia_Thread* thread,
    PixelBuffer* other
  )
{ 
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = other } };
  PixelBuffer* self = Arcadia_allocateObject(thread, _PixelBuffer_getType(thread), 1, &argumentValues[0]);
  return self;
}

Arcadia_Integer32Value
PixelBuffer_getWidth
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{ return self->numberOfColumns; }

Arcadia_Integer32Value
PixelBuffer_getHeight
  (
    Arcadia_Thread* thread,
    PixelBuffer* self
  )
{ return self->numberOfRows; }
