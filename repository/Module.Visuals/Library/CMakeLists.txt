# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
#
# Permission to use, copy, modify, and distribute this software for any
# purpose without fee is hereby granted, provided that this entire notice
# is included in all copies of any software which is or includes a copy
# or modification of this software and in all copies of the supporting
# documentation for such software.
#
# THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
# REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
# OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

# Last modified: 2024-09-16

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

set(MyModule ${MyProjectName}.Visuals)

if (NOT TARGET ${MyModule})
  BeginProduct(${MyModule} library)

  FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
  FetchProduct(${MyProjectName}.Machine "${REPOSITORY_SOURCE_DIR}/Arcadia.Machine/Library" "path to the Arcadia Machine library directory")
  
  if (NOT DEFINED ${MyModule}.OpenGl.Enabled)
    set(${MyModule}.OpenGl.Enabled 0)
  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Module/Visuals/Configure.h @ONLY)

  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Module/Visuals/Configure.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/CullMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/CullMode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/DepthCompareFunction.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/DepthCompareFunction.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/FillMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/FillMode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/PixelBuffer.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/PixelBuffer.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/PixelFormat.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/PixelFormat.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/TextureAddressMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/TextureAddressMode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/TextureFilter.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/TextureFilter.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/VertexElementSemantics.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/VertexElementSemantics.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/VertexElementSyntax.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/VertexElementSyntax.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/WindingMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/WindingMode.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/ImageWriterParameters.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/ImageWriterParameters.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/ImageWriter.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/ImageWriter.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeIcon.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeIcon.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindow.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindow.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Include.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Include.h)

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Linux/Include.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Linux/Include.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Linux/NativeIcon.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Linux/NativeIcon.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeLinuxImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeLinuxImageWriter.h)
    if (${${MyModule}.OpenGl.Enabled})
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Linux/NativeIcon.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Linux/NativeIcon.h)
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Linux/NativeWindow.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Linux/NativeWindow.h)
    endif()
  endif()

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Windows/NativeBitmap.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Windows/NativeBitmap.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Windows/NativeIcon.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Windows/NativeIcon.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Font.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Font.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsImageWriter.h)
    if (${${MyModule}.OpenGl.Enabled})
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Windows/NativeWindow.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Windows/NativeWindow.h)
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Windows/WglIntermediateWindow.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Windows/WglIntermediateWindow.h)
    endif()
  endif()

  list(APPEND ${MyModule}.PrivateLibraries ${MyProjectName}.Machine ${MyProjectName}.Arms)

  # X11/OpenGL under Linux.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux} AND ${MyModule}.OpenGl.Enabled)
    # Find X11.
    find_package(X11)
    if (NOT X11_FOUND)
      message(FATAL_ERROR " - X11 not found")
    else()
      #message(STATUS " - X11 found - X11_LIBRARIES = ${X11_LIBRARIES}")
      list(APPEND ${MyModule}.PrivateLibraries ${X11_LIBRARIES})
    endif()
    # Find OpenGL.
    find_package(OpenGL)
    if (NOT OPENGL_FOUND)
      message(FATAL_ERROR " - OpenGL not found")
    else()
      #message(STATUS " - OpenGL found - OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")
      list(APPEND ${MyModule}.PrivateLibraries ${OPENGL_LIBRARIES})
    endif()
  endif()
  
  # Always use libPNG under Linux.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux})
    find_package(PNG)
    if (NOT TARGET PNG::PNG)
      message(FATAL_ERROR "libPNG not found")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries PNG::PNG)
  endif()

  # WGL/OpenGL under Windows.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows} AND ${${MyModule}.OpenGl.Enabled})
    set(MyDependenciesDirectory "C:/arcadia-dependencies")
    find_package(OpenGL REQUIRED)
    list(APPEND ${MyModule}.PrivateLibraries ${OPENGL_LIBRARIES})
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.OpenGl.HeaderFilesDirectory ${MyDependenciesDirectory}/my-opengl-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.OpenGl.HeaderFilesDirectory ${MyDependenciesDirectory}/my-opengl-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    message(STATUS " - ${MyModule}.OpenGl.HeaderFilesDirectory = ${${MyModule}.OpenGl.HeaderFilesDirectory}")
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.OpenGl.HeaderFilesDirectory})
  endif()

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Arcadia.Modules")

endif()
