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

// Last modified: 2025-01-06

#if !defined(ARCADIA_RING1_IMPLEMENTATION_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_H_INCLUDED

#include "R/Configure.h"
#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"
#include "Arcadia/Ring1/Implementation/Size.h"

/// @brief
/// "names" are interned (canoncialized) sequences of Bytes.
/// Furthermore, such sequences fulfil multiple criteria:
/// - they are non-empty UTF8 Byte sequences
/// - they are a qualified name or unqualified name
/// @remarks
/// @code
/// name : namePart ('.' namePart)*
/// namePart : ('_' | letter) ('_' | letter | digit)*
/// letter : ('a' - 'z') | ('A' - 'Z')
/// digit : '0' - '9'
/// @endcode
typedef struct Arcadia_Atom Arcadia_Atom;
/// @brief Type of a pointer to an atom.
typedef Arcadia_Atom* Arcadia_AtomValue;

/// A flag for creating an atom.
/// See R_Atoms_getOrCreateAtom
#define Arcadia_AtomKind_Name (1)

/// @brief
/// Get or create an atom.
/// @param flags
/// The flags. Must be R_AtomKind_Name.
/// @param bytes
/// A pointer to an array of @a numberOfBytes Bytes.
/// @param numberOfBytes
/// The number of Bytes in the array pointed to by @a numberOfBytes.
/// @return
/// A pointer to the atom.
Arcadia_AtomValue
Arcadia_Atoms_getOrCreateAtom
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value flags,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

/// @brief
/// Visit this atom.
/// @param self
/// This atom.
void
Arcadia_Atom_visit
  (
    Arcadia_AtomValue self
  );

/// @brief
/// Get a pointer to the Bytes of this atom.
/// @param self
/// A pointer to this atom.
/// @return
/// A pointer to the Bytes of this atom.
const void*
Arcadia_Atom_getBytes
  (
    Arcadia_AtomValue self
  );

/// @brief
/// Get the number of Bytes of this atom.
/// @param self
/// A pointer to this atom.
/// @return
/// The number of Bytes of this atom.
Arcadia_SizeValue
Arcadia_Atom_getNumberOfBytes
  (
    Arcadia_AtomValue self
  );

/// @brief
/// Get the hash of this atom.
/// @param self
/// A pointer to this atom.
/// @return
/// The hash of this atom.
Arcadia_SizeValue
Arcadia_Atom_getHash
  (
    Arcadia_AtomValue self
  );

/// @brief
/// Get if this atom is equal to another atom.
/// @param self
/// A pointer to this atom.
/// @param other
/// A pointer to the other atom.
/// @return
/// #Arcadia_BooleanValue_True if this atom is equal to the other atom.
/// #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_Atom_isEqualTo
  (
    Arcadia_AtomValue self,
    Arcadia_AtomValue other
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_H_INCLUDED
