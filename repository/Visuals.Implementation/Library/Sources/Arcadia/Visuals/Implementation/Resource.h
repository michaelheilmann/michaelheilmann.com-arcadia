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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_RESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_RESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Math/Include.h"
typedef struct Arcadia_Visuals_Implementation_RenderingContextResource Arcadia_Visuals_Implementation_RenderingContextResource;
typedef struct Arcadia_Visuals_Implementation_BackendContext Arcadia_Visuals_Implementation_BackendContext;

// A "resource" is owned by a "backend context". That is, the "backend context" holds a STRONG reference to its "resources".
// In addition, the "backend context" retains a GC lock unless its "resources" such that they are only gc'ed if the "backend context" drops this lock.
Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                          u8"Arcadia.Object");

struct Arcadia_Visuals_Implementation_ResourceDispatch {
  Arcadia_ObjectDispatch _parent;

  void (*load)(Arcadia_Thread* thread, Arcadia_Visuals_Implementation_Resource* self);
  void (*unload)(Arcadia_Thread* thread, Arcadia_Visuals_Implementation_Resource* self);
  void (*unlink)(Arcadia_Thread* thread, Arcadia_Visuals_Implementation_Resource* self);
  void (*render)(Arcadia_Thread* thread, Arcadia_Visuals_Implementation_Resource* self, Arcadia_Visuals_Implementation_RenderingContextResource*);
};

struct Arcadia_Visuals_Implementation_Resource {
  Arcadia_Object _parent;
  // The reference count of this resources.
  Arcadia_Integer32Value referenceCount;
  // Unmanaged reference to the "backend context" or the null reference.
  Arcadia_Visuals_Implementation_BackendContext* context;
};

void
Arcadia_Visuals_Implementation_Resource_load
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  );

// Unload the "backend resource" of this resource.
// "Unloading" is a reversible action.
void
Arcadia_Visuals_Implementation_Resource_unload
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  );

// Unlink the of this resource.
// "Unlinking" is an irreversible action.
// The resource must be unloaded before unlinking.
// Unlinking removes all references to:
// a) the backend context
// b) if this resource is referencing a resource:
//    A referencing resource increments the reference count of a referenced resource (usually).
//    This increment is reversed when unlinking the referencing resource.
void
Arcadia_Visuals_Implementation_Resource_unlink
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  );

// Visit this resource during a "rendering".
// a) ensure the resource back representation is created / updated
// b) the "rendering context" resource is updated
void
Arcadia_Visuals_Implementation_Resource_render
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self,
    Arcadia_Visuals_Implementation_RenderingContextResource* renderingContextResource
  );

void
Arcadia_Visuals_Implementation_Resource_ref
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  );

void
Arcadia_Visuals_Implementation_Resource_unref
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_Resource* self
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_RESOURCE_H_INCLUDED
