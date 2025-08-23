#if !defined(ARCADIA_RING2_IMPLEMENTATION_STRINGEXTENSIONS_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_STRINGEXTENSIONS_H_INCLUDED

#include "Arcadia/Ring2/Implementation/String.h"
#include "Arcadia/Ring2/Implementation/StringBuffer.h"

Arcadia_String*
Arcadia_String_createFromCxxInt
  (
    Arcadia_Thread* thread,
    int x
  );

int
Arcadia_String_toCxxInt
  (
    Arcadia_Thread* thread,
    Arcadia_String* self
  );

Arcadia_String*
Arcadia_String_createFromCxxString
  (
    Arcadia_Thread* thread,
    const char *x
  );
  
void
Arcadia_StringBuffer_insertBackCxxInt
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    int x
  );
  
void
Arcadia_StringBuffer_insertBackCxxString
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    const char *x
  );

void
Arcadia_StringBuffer_insertBackString
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* self,
    Arcadia_String* x
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_STRINGEXTENSIONS_H_INCLUDED
