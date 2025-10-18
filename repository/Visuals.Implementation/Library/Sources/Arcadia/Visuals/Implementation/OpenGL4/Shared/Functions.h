#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_SHARED_FUNCTIONS_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_SHARED_FUNCTIONS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

#if Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Windows
  #include <GL/glcorearb.h>
#elif Arcadia_Configuration_OperatingSystem == Arcadia_Configuration_OperatingSystem_Linux
  #include <GL/glcorearb.h>
#else
  #error("environment not (yet) supported")
#endif

// unmanaged
typedef struct _Arcadia_Visuals_Implementation_OpenGL4_Functions _Arcadia_Visuals_Implementation_OpenGL4_Functions;
// unmanaged
typedef struct _Arcadia_Visuals_Implementation_OpenGL4_Linker _Arcadia_Visuals_Implementation_OpenGL4_Linker;

struct _Arcadia_Visuals_Implementation_OpenGL4_Linker {
  void* (*link)(Arcadia_Thread* thread, _Arcadia_Visuals_Implementation_OpenGL4_Linker* linker, const char* name);
};

struct _Arcadia_Visuals_Implementation_OpenGL4_Functions {
#define Define(Type, Name) \
  Type Name;
#include "Arcadia/Visuals/Implementation/OpenGL4/Shared/Functions.i"
#undef Define
};

/// @error functions is a null pointer
void
_Arcadia_Visuals_Implementation_OpenGL4_Functions_initialize
  (
    Arcadia_Thread* thread,
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* functions,
    _Arcadia_Visuals_Implementation_OpenGL4_Linker* linker
  );

/// @error functions is a null pointer
void
_Arcadia_Visuals_Implementation_OpenGL4_Functions_uninitialize
  (
    Arcadia_Thread* thread,
    _Arcadia_Visuals_Implementation_OpenGL4_Functions* functions
  );

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_SHARED_FUNCTIONS_H_INCLUDED
