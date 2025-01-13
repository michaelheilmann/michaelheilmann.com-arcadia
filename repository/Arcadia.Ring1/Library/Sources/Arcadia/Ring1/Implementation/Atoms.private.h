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
/// @warning Internal function.
void
Arcadia_Atoms_startup
  (
    Arcadia_Process1* process
  );

/// @brief Shutdown the atoms module.
/// @warning Internal function.
void
Arcadia_Atoms_shutdown
  (
    Arcadia_Process1* process
  );

/// @brief Must be invoked before the pre mark phase.
/// @remarks
/// This marks all atoms.
/// if now - lastVisited > threshold then the atom is marked live unless purgeCache is true
/// otherwise it is marked dead
/// @warning Internal function.
void
Arcadia_Atoms_onPreMark
  (
    Arcadia_Process1* process,
    Arcadia_BooleanValue purgeCache
  );

/// @brief Must be invoked after the finalize phase.
/// @warning Internal function.
void
Arcadia_Atoms_onFinalize
  (
    Arcadia_Process1* process
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_ATOMS_PRIVATE_H_INCLUDED
