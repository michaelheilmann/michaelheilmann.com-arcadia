// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R.h"
#include "R/cstdlib.h"

static inline void
Memory_copy
  (
    R_Natural8Value* target,
    R_Natural8Value const* source,
    size_t count
  )
{
  for (size_t i = 0, n = count; i < n; ++i) {
    *target = *source;
    source++;
    target++;
  }
}

static inline void
Memory_swap
  (
    R_Natural8Value* target,
    R_Natural8Value* source,
    size_t count
  )
{
  for (size_t i = 0, n = count; i < n; ++i) {
    R_Natural8Value temporary = *source;
    *source = *target;
    *target = temporary;
    source++;
    target++;
  }
}

typedef struct PIXEL {
  R_Natural8Value r, g, b, a;
} PIXEL;

static void inline
DECODE_ABGR
  (
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
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
    R_Natural8Value* p,
    PIXEL* pixel
  )
{
  *(p + 0) = pixel->r;
  *(p + 1) = pixel->g;
  *(p + 2) = pixel->b;
  *(p + 3) = pixel->a;
}

typedef void (TranscodeCallback)(R_Natural8Value*, PIXEL*);

static void
getTranscodeCallbacks
  (
    R_Natural8Value source,
    size_t* sourceNumberOfBytesPerPixel,
    TranscodeCallback** decode,
    R_Natural8Value target,
    size_t* targetNumberOfBytesPerPixel,
    TranscodeCallback** encode
  )
{
  typedef struct Entry {
    R_Natural8Value pixelFormat;
    size_t numberOfBytesPerPixel;
    TranscodeCallback* decodeCallback;
    TranscodeCallback* encodeCallback;
  } Entry;

  static const Entry g_entries[] = {
    { PixelFormat_An8Bn8Gn8Rn8, 4, &DECODE_ABGR, &ENCODE_ABGR },
    { PixelFormat_An8Rn8Gn8Bn8, 4, &DECODE_ARGB, &ENCODE_ARGB },
    { PixelFormat_Bn8Gn8Rn8,    3, &DECODE_BGR,  &ENCODE_BGR  },
    { PixelFormat_Bn8Gn8Rn8An8, 4, &DECODE_BGRA, &ENCODE_BGRA },
    { PixelFormat_Rn8Gn8Bn8,    3, &DECODE_RGB,  &ENCODE_RGB  },
    { PixelFormat_Rn8Gn8Bn8An8, 4, &DECODE_RGBA, &ENCODE_RGBA },
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
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
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
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
PixelBuffer_destruct
  (
    PixelBuffer* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &PixelBuffer_constructImpl,
  .destruct = &PixelBuffer_destruct,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("PixelBuffer", PixelBuffer, "R.Object", R_Object, &_typeOperations);

static void
PixelBuffer_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  if (1 == numberOfArgumentValues) {
    PixelBuffer* _self = R_Value_getObjectReferenceValue(self);
    R_Type* _type = _PixelBuffer_getType();
    {
      R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
      R_Object_constructImpl(self, 0, &argumentValues[0]);
    }
    if (!R_Type_isSubType(R_Value_getType(&argumentValues[0]), _PixelBuffer_getType())) {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
    PixelBuffer* other = (PixelBuffer*)R_Value_getObjectReferenceValue(&argumentValues[0]);
    _self->numberOfColumns = PixelBuffer_getNumberOfColumns(other);
    _self->numberOfRows = PixelBuffer_getNumberOfRows(other);
    _self->linePadding = PixelBuffer_getLinePadding(other);
    _self->pixelFormat = PixelBuffer_getPixelFormat(other);
    R_SizeValue bytesPerPixel = PixelBuffer_getBytesPerPixel(other);
    R_SizeValue bytes = (bytesPerPixel * _self->numberOfColumns + _self->linePadding) * _self->numberOfRows;
    if (!R_allocateUnmanaged_nojump(&_self->bytes, bytes)) {
      R_jump();
    }
    c_memcpy(_self->bytes, other->bytes, bytes);
    R_Object_setType((R_Object*)_self, _type);
  } else if (4 == numberOfArgumentValues) {
    R_Type* _type = _PixelBuffer_getType();
    PixelBuffer* _self = R_Value_getObjectReferenceValue(self);
    {
      R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
      R_Object_constructImpl(self, 0, &argumentValues[0]);
    }
    if (!R_Value_isInteger32Value(&argumentValues[0])) {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
    if (!R_Value_isInteger32Value(&argumentValues[1])) {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
    if (!R_Value_isInteger32Value(&argumentValues[2])) {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
    if (!R_Value_isNatural32Value(&argumentValues[3])) {
      R_setStatus(R_Status_ArgumentTypeInvalid);
      R_jump();
    }
    _self->bytes = NULL;
    _self->pixelFormat = R_Value_getNatural32Value(&argumentValues[3]);
    _self->numberOfColumns = R_Value_getInteger32Value(&argumentValues[1]);
    _self->numberOfRows = R_Value_getInteger32Value(&argumentValues[2]);
    _self->linePadding = R_Value_getInteger32Value(&argumentValues[0]);
    R_SizeValue bytesPerPixel = 0;
    switch (_self->pixelFormat) {
      case PixelFormat_An8Bn8Gn8Rn8:
      case PixelFormat_An8Rn8Gn8Bn8:
      case PixelFormat_Bn8Gn8Rn8An8:
      case PixelFormat_Rn8Gn8Bn8An8: {
        bytesPerPixel = 4;
      } break;
      case PixelFormat_Bn8Gn8Rn8:
      case PixelFormat_Rn8Gn8Bn8: {
        bytesPerPixel = 3;
      } break;
      default: {
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
    };
    if (!R_allocateUnmanaged_nojump(&_self->bytes, (_self->numberOfColumns * bytesPerPixel + _self->linePadding) * _self->numberOfRows)) {
      R_jump();
    }
    switch (_self->pixelFormat) {
      case PixelFormat_An8Bn8Gn8Rn8: {
        R_SizeValue lineStride = _self->numberOfColumns * bytesPerPixel + _self->linePadding;
        for (R_SizeValue y = 0; y < _self->numberOfRows; ++y) {
          R_Natural8Value* p = _self->bytes + (y * lineStride);
          for (R_SizeValue x = 0; x < _self->numberOfColumns; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_ABGR(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case PixelFormat_An8Rn8Gn8Bn8: {
        R_SizeValue lineStride = _self->numberOfColumns * bytesPerPixel + _self->linePadding;
        for (R_SizeValue y = 0; y < _self->numberOfRows; ++y) {
          R_Natural8Value* p = _self->bytes + (y * lineStride);
          for (R_SizeValue x = 0; x < _self->numberOfColumns; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_ARGB(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case PixelFormat_Bn8Gn8Rn8: {
        R_SizeValue lineStride = _self->numberOfColumns * bytesPerPixel + _self->linePadding;
        for (R_SizeValue y = 0; y < _self->numberOfRows; ++y) {
          R_Natural8Value* p = _self->bytes + (y * lineStride);
          for (R_SizeValue x = 0; x < _self->numberOfColumns; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_BGR(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      case PixelFormat_Rn8Gn8Bn8: {
        R_SizeValue lineStride = _self->numberOfColumns * bytesPerPixel + _self->linePadding;
        for (R_SizeValue y = 0; y < _self->numberOfRows; ++y) {
          R_Natural8Value* p = _self->bytes + (y * lineStride);
          for (R_SizeValue x = 0; x < _self->numberOfColumns; ++x) {
            PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
            ENCODE_RGB(p + x * bytesPerPixel, &pixel);
          }
        }
      } break;
      default: {
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
    };
    R_Object_setType((R_Object*)_self, _type);
  } else {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
}

static void
PixelBuffer_destruct
  (
    PixelBuffer* self
  )
{
  if (self->bytes) {
    R_deallocateUnmanaged_nojump(self->bytes);
    self->bytes = NULL;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

R_Natural8Value
PixelBuffer_getPixelFormat
  (
    PixelBuffer* self
  )
{
  return self->pixelFormat;
}

void
PixelBuffer_setPixelFormat
  (
    PixelBuffer* self,
    R_Natural8Value pixelFormat
  )
{
  if (pixelFormat == self->pixelFormat) {
    return;
  }
  TranscodeCallback* decodeCallback = NULL;
  size_t sourceNumberOfBytesPerPixel = 0;
  TranscodeCallback* encodeCallback = NULL;
  size_t targetNumberOfBytesPerPixel = 0;
  getTranscodeCallbacks(self->pixelFormat, &sourceNumberOfBytesPerPixel, &decodeCallback, pixelFormat, &targetNumberOfBytesPerPixel, &encodeCallback);

  R_Natural8Value* sourceBytes = self->bytes;
  R_Natural8Value* targetBytes = NULL;
  if (sourceNumberOfBytesPerPixel != targetNumberOfBytesPerPixel) {
    if (R_allocateUnmanaged_nojump(&targetBytes, (self->numberOfColumns * sourceNumberOfBytesPerPixel + self->linePadding) * self->numberOfRows)) {
      R_jump();
    }
  } else {
    targetBytes = self->bytes;
  }

  R_SizeValue sourceLineStride = self->numberOfColumns * sourceNumberOfBytesPerPixel + self->linePadding;
  R_SizeValue targetLineStride = self->numberOfColumns * targetNumberOfBytesPerPixel + self->linePadding;
  for (R_SizeValue y = 0; y < self->numberOfRows; ++y) {
    R_Natural8Value* p = sourceBytes + (y * sourceLineStride);
    R_Natural8Value* q = targetBytes + (y * targetLineStride);
    for (R_SizeValue x = 0; x < self->numberOfColumns; ++x) {
      PIXEL pixel;
      (*decodeCallback)(p + x * sourceNumberOfBytesPerPixel, &pixel);
      (*encodeCallback)(q + x * targetNumberOfBytesPerPixel, &pixel);
    }
  }
  if (sourceNumberOfBytesPerPixel != targetNumberOfBytesPerPixel) {
    R_deallocateUnmanaged_nojump(sourceBytes);
    self->bytes = targetBytes;
  }
  self->pixelFormat = pixelFormat;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

R_Integer32Value
PixelBuffer_getLinePadding
  (
    PixelBuffer* self
  )
{ return self->linePadding; }

void
PixelBuffer_setLinePadding
  (
    PixelBuffer* self,
    R_Integer32Value linePadding
  )
{
  if (self->linePadding != linePadding) {
    if (linePadding < 0) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    R_Integer32Value bytesPerPixel = 0;
    switch (self->pixelFormat) {
      case PixelFormat_An8Bn8Gn8Rn8:
      case PixelFormat_An8Rn8Gn8Bn8: 
      case PixelFormat_Bn8Gn8Rn8An8:
      case PixelFormat_Rn8Gn8Bn8An8:
      {
        bytesPerPixel = 4;
      } break;
      case PixelFormat_Bn8Gn8Rn8:
      case PixelFormat_Rn8Gn8Bn8: {
        bytesPerPixel = 3;
      } break;
      default: {
        R_setStatus(R_Status_ArgumentValueInvalid);
        R_jump();
      } break;
    }
    R_Integer32Value oldLinePadding = self->linePadding;
    R_Integer32Value newLinePadding = linePadding;
    R_Natural8Value* oldBytes = self->bytes;
    R_Natural8Value* newBytes = NULL;
    if (!R_allocateUnmanaged_nojump(&newBytes, (self->numberOfColumns * bytesPerPixel + newLinePadding) * self->numberOfRows)) {
      R_jump();
    }
    for (R_SizeValue rowIndex = 0; rowIndex < self->numberOfRows; ++rowIndex) {
      R_Natural8Value* oldLine = oldBytes + rowIndex * (self->numberOfColumns * bytesPerPixel + oldLinePadding);
      R_Natural8Value* newLine = newBytes + rowIndex * (self->numberOfColumns * bytesPerPixel + newLinePadding);
      c_memcpy(newLine, oldLine, self->numberOfColumns * bytesPerPixel);
    }
    R_deallocateUnmanaged_nojump(oldBytes);
    self->bytes = newBytes;
    self->linePadding = linePadding;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
PixelBuffer_getPixelRgba
  (
    PixelBuffer* self,
    R_Integer32Value column,
    R_Integer32Value row,
    R_Natural8Value* r,
    R_Natural8Value* g,
    R_Natural8Value* b,
    R_Natural8Value* a
  )
{
  if (column < 0 || column > PixelBuffer_getNumberOfColumns(self)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (row < 0 || row > PixelBuffer_getNumberOfRows(self)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_SizeValue offset = row * PixelBuffer_getLineStride(self) + column * PixelBuffer_getBytesPerPixel(self);
  R_Natural8Value* bytes = self->bytes + offset;
  PIXEL pixel = { .r = 0, .g = 0, .b = 0, .a = 255 };
  switch (self->pixelFormat) {
    case PixelFormat_An8Bn8Gn8Rn8: {
      DECODE_ABGR(bytes, &pixel);
    } break;
    case PixelFormat_An8Rn8Gn8Bn8: {
      DECODE_ARGB(bytes, &pixel);
    } break;
    case PixelFormat_Bn8Gn8Rn8: {
      DECODE_BGR(bytes, &pixel);
    } break;
    case PixelFormat_Bn8Gn8Rn8An8: {
      DECODE_BGRA(bytes, &pixel);
    } break;
    case PixelFormat_Rn8Gn8Bn8: {
      DECODE_RGB(bytes, &pixel);
    } break;
    case PixelFormat_Rn8Gn8Bn8An8: {
      DECODE_RGBA(bytes, &pixel);
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
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
    PixelBuffer* self,
    R_Integer32Value column,
    R_Integer32Value row,
    R_Natural8Value r,
    R_Natural8Value g,
    R_Natural8Value b,
    R_Natural8Value a
  )
{
  if (column < 0 || column >= PixelBuffer_getNumberOfColumns(self)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (row < 0 || row >= PixelBuffer_getNumberOfRows(self)) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_SizeValue offset = row * PixelBuffer_getLineStride(self) + column * PixelBuffer_getBytesPerPixel(self);
  R_Natural8Value* bytes = self->bytes + offset;
  PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
  switch (self->pixelFormat) {
    case PixelFormat_An8Bn8Gn8Rn8: {
      ENCODE_ABGR(bytes, &pixel);
    } break;
    case PixelFormat_An8Rn8Gn8Bn8: {
      ENCODE_ARGB(bytes, &pixel);
    } break;
    case PixelFormat_Bn8Gn8Rn8: {
      ENCODE_BGR(bytes, &pixel);
    } break;
    case PixelFormat_Bn8Gn8Rn8An8: {
      ENCODE_BGRA(bytes, &pixel);
    } break;
    case PixelFormat_Rn8Gn8Bn8: {
      ENCODE_RGB(bytes, &pixel);
    } break;
    case PixelFormat_Rn8Gn8Bn8An8: {
      ENCODE_RGBA(bytes, &pixel);
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  };
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
PixelBuffer_fill
  (
    PixelBuffer* self,
    R_Natural8Value r,
    R_Natural8Value g,
    R_Natural8Value b,
    R_Natural8Value a
  )
{
  switch (self->pixelFormat) {
    case PixelFormat_An8Bn8Gn8Rn8: {
      R_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      R_Natural8Value* p = self->bytes;
      for (R_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (R_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_ABGR(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case PixelFormat_An8Rn8Gn8Bn8: {
      R_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      R_Natural8Value* p = self->bytes;
      for (R_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (R_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_ARGB(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case PixelFormat_Bn8Gn8Rn8: {
      R_SizeValue bytesPerPixel = 3;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      R_Natural8Value* p = self->bytes;
      for (R_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (R_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_BGR(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case PixelFormat_Bn8Gn8Rn8An8: {
      R_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      R_Natural8Value* p = self->bytes;
      for (R_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (R_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_BGRA(p + x * bytesPerPixel, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case PixelFormat_Rn8Gn8Bn8: {
      R_SizeValue bytesPerPixel = 3;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      R_Natural8Value* p = self->bytes;
      for (R_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (R_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_RGB(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    case PixelFormat_Rn8Gn8Bn8An8: {
      R_SizeValue bytesPerPixel = 4;
      PIXEL pixel = { .r = r, .g = g, .b = b, .a = a };
      R_Natural8Value* p = self->bytes;
      for (R_SizeValue y = 0; y < self->numberOfRows; ++y) {
        for (R_SizeValue x = 0; x < self->numberOfColumns; ++x) {
          ENCODE_RGBA(p, &pixel);
          p += bytesPerPixel;
        }
        p += self->linePadding;
      }
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  };
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
PixelBuffer_swapColumns
  (
    PixelBuffer* self,
    R_Integer32Value column1,
    R_Integer32Value column2
  )
{
  if (column1 < 0 || column1 >= self->numberOfColumns) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (column2 < 0 || column2 >= self->numberOfColumns) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (column1 == column2) {
    return;
  }
  R_Integer32Value bytesPerPixel = PixelBuffer_getBytesPerPixel(self);
  R_Integer32Value lineStride = PixelBuffer_getLineStride(self);
  R_Natural8Value* source = self->bytes + column1 * PixelBuffer_getBytesPerPixel(self);
  R_Natural8Value* target = self->bytes + column2 * PixelBuffer_getBytesPerPixel(self);
  for (R_SizeValue row = 0; row < self->numberOfRows; ++row) {
    Memory_swap(source, target, bytesPerPixel);
    source += lineStride;
    target += lineStride;
  }
}

void
PixelBuffer_swapRows
  (
    PixelBuffer* self,
    R_Integer32Value row1,
    R_Integer32Value row2
  )
{
  if (row1 < 0 || row1 >= self->numberOfRows) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (row2 < 0 || row2 >= self->numberOfRows) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (row1 == row2) {
    return;
  }
  R_Integer32Value bytesPerPixel = PixelBuffer_getBytesPerPixel(self);
  R_Natural8Value* source = self->bytes + PixelBuffer_getLineStride(self) * row1;
  R_Natural8Value* target = self->bytes + PixelBuffer_getLineStride(self) * row2;
  Memory_swap(source, target, self->numberOfColumns * bytesPerPixel);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
PixelBuffer_reflectVertically
  (
    PixelBuffer* self
  )
{
  for (R_Integer32Value column = 0, w = self->numberOfColumns / 2; column < w; ++column) {
    PixelBuffer_swapColumns(self, column, self->numberOfColumns - 1 - column);
  }
}

void
PixelBuffer_reflectHorizontally
  (
    PixelBuffer* self
  )
{
  for (R_Integer32Value row = 0, h = self->numberOfRows / 2; row < h; ++row) {
    PixelBuffer_swapRows(self, row, self->numberOfRows - 1 - row);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

R_Integer32Value
PixelBuffer_getNumberOfColumns
  (
    PixelBuffer* self
  )
{ return self->numberOfColumns; }

R_Integer32Value
PixelBuffer_getNumberOfRows
  (
    PixelBuffer* self
  )
{ return self->numberOfRows; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

R_Integer32Value
PixelBuffer_getLineStride
  (
    PixelBuffer* self
  )
{ return PixelBuffer_getNumberOfColumns(self) * PixelBuffer_getBytesPerPixel(self) + PixelBuffer_getLinePadding(self); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

R_Integer32Value
PixelBuffer_getBytesPerPixel
  (
    PixelBuffer* self
  )
{
  size_t bytesPerPixel = 0;
  switch (self->pixelFormat) {
    case PixelFormat_An8Bn8Gn8Rn8:
    case PixelFormat_An8Rn8Gn8Bn8:
    case PixelFormat_Bn8Gn8Rn8An8:
    case PixelFormat_Rn8Gn8Bn8An8: {
      bytesPerPixel = 4;
    } break;
    case PixelFormat_Bn8Gn8Rn8:
    case PixelFormat_Rn8Gn8Bn8: {
      bytesPerPixel = 3;
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  }
  return bytesPerPixel;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

PixelBuffer*
PixelBuffer_create
  (
    R_Integer32Value linePadding,
    R_Integer32Value width,
    R_Integer32Value height,
    R_Natural8Value pixelFormat
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Integer32, .integer32Value = linePadding },
                               {.tag = R_ValueTag_Integer32, .integer32Value = width },
                               {.tag = R_ValueTag_Integer32, .integer32Value = height },
                               {.tag = R_ValueTag_Natural32, .natural32Value = pixelFormat } };
  PixelBuffer* self = R_allocateObject(_PixelBuffer_getType(), 4, &argumentValues[0]);
  return self;
}

PixelBuffer*
PixelBuffer_createClone
  (
    PixelBuffer* other
  )
{ 
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = other } };
  PixelBuffer* self = R_allocateObject(_PixelBuffer_getType(), 1, &argumentValues[0]);
  return self;
}

R_Integer32Value
PixelBuffer_getWidth
  (
    PixelBuffer* self
  )
{ return self->numberOfColumns; }

R_Integer32Value
PixelBuffer_getHeight
  (
    PixelBuffer* self
  )
{ return self->numberOfRows; }
