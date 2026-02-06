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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_NODEFACTORY_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_NODEFACTORY_H_INCLUDED

#include "Arcadia/Visuals/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.NodeFactory", Arcadia_Visuals_Implementation_NodeFactory,
                          Arcadia_Engine_Visuals_NodeFactory);

struct Arcadia_Visuals_Implementation_NodeFactoryDispatch {
  Arcadia_Engine_Visuals_NodeFactoryDispatch parent;
};

struct Arcadia_Visuals_Implementation_NodeFactory {
  Arcadia_Engine_Visuals_NodeFactory parent;
};

Arcadia_Visuals_Implementation_NodeFactory*
Arcadia_Visuals_Implementation_NodeFactory_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_NODEFACTORY_H_INCLUDED
