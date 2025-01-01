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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_ATOMS_PRIVATE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_ATOMS_PRIVATE_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Atoms.h"

/// @brief Startup the atoms module.
void
Arcadia_Atoms_startup
  (
    Arcadia_Process* process
  );

/// @brief Shutdown the atoms module.
void
Arcadia_Atoms_shutdown
  (
    Arcadia_Process* process
  );

/// Must be invoked before the pre mark phase.
void
Arcadia_Atoms_onPreMark
  (
  );

/// @brief
/// Must be invoked after the finalize phase.
/// @param purgeCache
/// Purge the caches if @a Arcadia_BooleanValue_True.
/// Otherwise perform @a Arcadia_BooleanValue_False retains the cahces.
/// @remarks
/// When an atom is visited, locked, or get (given a string), then its age is set to 0.
/// If an atom is dead (not visited, not locked) in a garbage collection, then it is still retained unless its age exceeds a certain threshold.
/// "purging" means that any dead atom is removed regardless of its age.
void
Arcadia_Atoms_onFinalize
  (
    Arcadia_Process* process,
    Arcadia_BooleanValue purgeCache
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_ATOMS_PRIVATE_H_INCLUDED
