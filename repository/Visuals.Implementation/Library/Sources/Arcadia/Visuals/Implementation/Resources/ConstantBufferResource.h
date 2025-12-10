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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_CONSTANTBUFFERRESOURCE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_CONSTANTBUFFERRESOURCE_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Resource.h"

Arcadia_declareObjectType(u8"Arcadia.Visuals.Implementation.ConstantBufferResource", Arcadia_Visuals_Implementation_ConstantBufferResource,
                          u8"Arcadia.Visuals.Implementation.Resource");

struct Arcadia_Visuals_Implementation_ConstantBufferResourceDispatch {
  Arcadia_Visuals_Implementation_ResourceDispatch _parent;

  void (*setData)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ConstantBufferResource*, const void*, Arcadia_SizeValue);
  void (*clear)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ConstantBufferResource*);
  void (*writeMatrix4x4Real32)(Arcadia_Thread*, Arcadia_Visuals_Implementation_ConstantBufferResource*, Arcadia_BooleanValue transpose, Arcadia_Math_Matrix4Real32 const* source);
};

struct Arcadia_Visuals_Implementation_ConstantBufferResource {
  Arcadia_Visuals_Implementation_Resource _parent;
};

void
Arcadia_Visuals_Implementation_ConstantBufferResource_setData
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_ConstantBufferResource* self,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

void
Arcadia_Visuals_Implementation_ConstantBufferResource_clear
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_ConstantBufferResource* self
  );

void
Arcadia_Visuals_Implementation_ConstantBufferResource_writeMatrix4x4Real32
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_ConstantBufferResource* self,
    Arcadia_BooleanValue transpose,
    Arcadia_Math_Matrix4Real32 const* source
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_CONSTANTBUFFERRESOURCE_H_INCLUDED
