// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_ATOMS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_ATOMS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Configure.h"
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
/// @remarks
/// Caching: Atoms are kept in a data structure which allows efficient lookup of an atom by a sequence of Bytes.
/// Atoms maintain an age. Atoms below a certain age are marked as "life" during premark phase (unless purge cache is specified).
/// If an atom is dead, then in the finalize callback, its ADDRESS and its HASH value are used to effieciently remove the atom from the set of atoms.
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
    Arcadia_Thread* thread,
    Arcadia_Natural8Value flags,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

/// @brief
/// Visit this Arcadia_Atom object.
/// @param thread
/// A pointer to the Arcadia_Thread object.
/// @param self
/// A pointer to this Arcadia_Atom object.
void
Arcadia_Atom_visit
  (
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
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
    Arcadia_Thread* thread,
    Arcadia_AtomValue self,
    Arcadia_AtomValue other
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_ATOMS_H_INCLUDED
