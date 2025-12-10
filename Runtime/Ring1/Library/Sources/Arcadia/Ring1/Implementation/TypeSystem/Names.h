// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_NAMES_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_NAMES_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif
#include "Arcadia/Ring1/Implementation/Module.h"
#include <stdint.h>

typedef struct Arcadia_Name Arcadia_Name;

typedef struct Arcadia_Names Arcadia_Names;

struct Arcadia_Name {
  Arcadia_Name* next;
  uint64_t lastVisited;
  size_t hashValue;
  size_t numberOfBytes;
  char bytes[];
};

/// @brief Visit this name.
/// @param thread A pointer to this thread.
/// @param self A pointer to this name.
void
Arcadia_Name_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Name* self
  );

/// @brief Get the hash value of this name.
/// @param thread A pointer to this thread.
/// @param self A pointer to this name.
/// @return The hash value of this name.
size_t
Arcadia_Name_getHash
  (
    Arcadia_Thread* thread,
    Arcadia_Name* self
  );

/// @brief Get the number of Bytes of this name.
/// @param thread A pointer to this thread.
/// @param self A pointer to this name.
/// @return The number of Bytes of this name.
size_t
Arcadia_Name_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Name* self
  );

/// @brief Get the Bytes of this name.
/// @param thread A pointer to this thread.
/// @param self A pointer to this name.
/// @return A pointer to the Bytes of this name.
/// @warning The Bytes are valid as long as the name is live.
const char*
Arcadia_Name_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Name* self
  );

struct Arcadia_Names {
  Arcadia_Name** buckets;
  size_t size;
  size_t capacity;
};

Arcadia_DeclareModule("Arcadia.Names", Arcadia_Names);

Arcadia_Name*
Arcadia_Names_getOrCreateName
  (
    Arcadia_Thread* thread,
    char const* bytes,
    size_t numberOfBytes
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_NAMES_H_INCLUDED
