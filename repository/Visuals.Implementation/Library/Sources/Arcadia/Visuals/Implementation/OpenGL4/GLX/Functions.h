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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX_FUNCTIONS_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX_FUNCTIONS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

typedef struct _Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_Functions _Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_Functions;

struct _Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_Functions {
  int dummy;
#define Define(Type, Name) \
  Type Name;
#include "Arcadia/Visuals/Implementation/OpenGL4/GLX/Functions.i"
#undef Define
};

/// @error functions is a null pointer
void
_Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_Functions_initialize
  (
    Arcadia_Thread* thread,
    _Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_Functions* functions
  );

/// @error functions is a null pointer
void
_Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_Functions_uninitialize
  (
    Arcadia_Thread* thread,
    _Arcadia_Engine_Visuals_Implementation_OpenGL4_GLX_Functions* functions
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_GLX_FUNCTIONS_H_INCLUDED
