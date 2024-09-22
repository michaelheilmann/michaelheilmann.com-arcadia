#if !defined(R_UTF8BYTEBUFFERREADER_H_INCLUDED)
#define R_UTF8BYTEBUFFERREADER_H_INCLUDED

#include "R/Utf8Reader.h"
#include "R/Size.h"
typedef struct R_ByteBuffer R_ByteBuffer;

#define R_UTF8BYTEBUFFERREADER(x) ((R_Utf8ByteBufferReader*)(x))
typedef struct R_Utf8ByteBufferReader R_Utf8ByteBufferReader;
void _R_Utf8ByteBufferReader_registerType();

struct R_Utf8ByteBufferReader {
  R_Utf8Reader parent;
  R_ByteBuffer* source;
  R_SizeValue byteIndex;
  R_Natural32Value codePoint;
};

void
R_Utf8ByteBufferReader_construct
  (
    R_Utf8ByteBufferReader* self,
    R_ByteBuffer* source
  );

R_Utf8ByteBufferReader*
R_Utf8ByteBufferReader_create
  (
    R_ByteBuffer* source
  );

#endif // R_UTF8BYTEBUFFERREADER_H_INCLUDED
