#if !defined(R_UTF8STRINGREADER_H_INCLUDED)
#define R_UTF8STRINGREADER_H_INCLUDED

#include "R/Utf8Reader.h"
#include "R/Size.h"
typedef struct R_String R_String;

#define R_UTF8STRINGREADER(x) ((R_Utf8StringReader*)(x))
typedef struct R_Utf8StringReader R_Utf8StringReader;
void _R_Utf8StringReader_registerType();

struct R_Utf8StringReader {
  R_Utf8Reader parent;
  R_String* source;
  R_SizeValue byteIndex;
  R_Natural32Value codePoint;
};

void
R_Utf8StringReader_construct
(
  R_Utf8StringReader* self,
  R_String* source
);

R_Utf8StringReader*
R_Utf8StringReader_create
  (
    R_String* source
  );

#endif // R_UTF8STRINGREADER_H_INCLUDED
