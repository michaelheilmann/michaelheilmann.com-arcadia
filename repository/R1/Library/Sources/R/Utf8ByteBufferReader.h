#if !defined(R_UTF8BYTEBUFFERREADER_H_INCLUDED)
#define R_UTF8BYTEBUFFERREADER_H_INCLUDED

#include "R/Utf8Reader.h"
#include "Arcadia/Ring1/Implementation/Size.h"
typedef struct R_ByteBuffer R_ByteBuffer;

Rex_declareObjectType(u8"R.Utf8ByteBufferReader", R_Utf8ByteBufferReader, u8"R.Utf8Reader");

struct R_Utf8ByteBufferReader {
  R_Utf8Reader parent;
  R_ByteBuffer* source;
  Arcadia_SizeValue byteIndex;
  Arcadia_Natural32Value codePoint;
};

R_Utf8ByteBufferReader*
R_Utf8ByteBufferReader_create
  (
    Arcadia_Process* process,
    R_ByteBuffer* source
  );

#endif // R_UTF8BYTEBUFFERREADER_H_INCLUDED
