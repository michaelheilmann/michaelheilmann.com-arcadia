#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_H_INCLUDED

#include "Arcadia/Visuals/Implementation/Configure.h"

#if 1 == Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled && \
   Arcadia_Visuals_Implementation_Configuration_OperatingSystem == Arcadia_Visuals_Implementation_Configuration_OperatingSystem_Windows
  #include <GL/glcorearb.h> // For GLuint.
#elif  1 == Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled && \
       Arcadia_Visuals_Implementation_Configuration_OperatingSystem == Arcadia_Visuals_Implementation_Configuration_OperatingSystem_Linux
  #include <GL/glcorearb.h> // For GLuint.
#else
  #error("environment not (yet) supported")
#endif

#endif // ARCADIA_VISUALS_IMPLEMENTATION_OPENGL4_H_INCLUDED
