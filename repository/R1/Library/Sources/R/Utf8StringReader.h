#if !defined(R_UTF8STRINGREADER_H_INCLUDED)
#define R_UTF8STRINGREADER_H_INCLUDED

#include "R/Utf8Reader.h"
typedef struct Arcadia_String Arcadia_String;

Rex_declareObjectType(u8"R.Utf8StringReader", R_Utf8StringReader, u8"R.Utf8Reader");

struct R_Utf8StringReader {
  R_Utf8Reader parent;
  Arcadia_String* source;
  Arcadia_SizeValue byteIndex;
  Arcadia_Natural32Value codePoint;
};

R_Utf8StringReader*
R_Utf8StringReader_create
  (
    Arcadia_Process* process,
    Arcadia_String* source
  );

#endif // R_UTF8STRINGREADER_H_INCLUDED
