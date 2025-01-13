#if !defined(ARCADIA_RING1_DIAGNOSTICS_H_INCLUDED)
#define ARCADIA_RING1_DIAGNOSTICS_H_INCLUDED

#include <stdarg.h>
#include <stdint.h>

#define Arcadia_LogFlags_Info (1)
#define Arcadia_LogFlags_Trace (2)
#define Arcadia_LogFlags_Error (4)

typedef uint8_t Arcadia_LogFlags;

void
Arcadia_logf
  (
    Arcadia_LogFlags flags,
    const char* format,
    ...
  );

void
Arcadia_logfv
  (
    Arcadia_LogFlags flags,
    const char* format,
    va_list arguments
  );

#endif // ARCADIA_RING1_DIAGNOSTICS_H_INCLUDED

