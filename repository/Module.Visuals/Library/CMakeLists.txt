# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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
  enable_testing()
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

set(MyModule Module.Visuals)

if (NOT TARGET ${MyModule})
  BeginProduct(${MyModule} library)

  FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
  FetchProduct(${MyProjectName}.Mil "${REPOSITORY_SOURCE_DIR}/R1/Library" "path to the MIL library directory")

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Module/Visuals/Configure.h @ONLY)

  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Module/Visuals/Configure.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/PixelBuffer.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/PixelBuffer.h)
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
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeLinuxImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeLinuxImageWriter.h)
  endif()

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsBitmap.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsBitmap.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Font.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/Font.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsImageWriter.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsIcon.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsIcon.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsWindow.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Visuals/NativeWindowsWindow.h)
  endif()

  list(APPEND ${MyModule}.PrivateLibraries ${MyProjectName}.Mil ${MyProjectName}.Arms)

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux})
    find_package(PNG)
    if (NOT TARGET PNG::PNG)
      message(FATAL_ERROR "libPNG not found")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries PNG::PNG)
  endif()

  EndProduct(${MyModule})

endif()
