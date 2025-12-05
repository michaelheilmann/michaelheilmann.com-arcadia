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

cmake_minimum_required(VERSION 4.1.3)

set(MyModule ${MyProjectName}.Imaging)

if (NOT TARGET ${MyModule})
  #option(${MyModule}.OpenGl.Enabled "TRUE enables OpenGL support. FALSE disables OpenGL support. Default is FALSE" FALSE)

  BeginProduct(${MyModule} library)

  # Always use libpng under Linux.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux})
    find_package(PNG)
    if (NOT TARGET PNG::PNG)
      message(FATAL_ERROR "libPNG not found")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries PNG::PNG)
  endif()

  # Always use zlib, libpng and freetype under Windows.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    set(MyDependenciesDirectory "C:/arcadia-dependencies")

    # zlib.
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.zlib.Libraries ${MyDependenciesDirectory}/my-zlib-$<LOWER_CASE:$<CONFIG>>-x64/lib/zlib.lib)
      set(${MyModule}.zlib.HeaderFilesDirectory ${MyDependenciesDirectory}/my-zlib-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.zlib.Libraries ${MyDependenciesDirectory}/my-zlib-$<LOWER_CASE:$<CONFIG>>-x86/lib/zlib.lib)
      set(${MyModule}.zlib.HeaderFilesDirectory ${MyDependenciesDirectory}/my-zlib-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.zlib.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.zlib.HeaderFilesDirectory})

    # libpng.
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.LibPng.Libraries ${MyDependenciesDirectory}/my-libpng-$<LOWER_CASE:$<CONFIG>>-x64/lib/libpng.lib)
      set(${MyModule}.LibPng.HeaderFilesDirectory ${MyDependenciesDirectory}/my-libpng-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.LibPng.Libraries ${MyDependenciesDirectory}/my-libpng-$<LOWER_CASE:$<CONFIG>>-x86/lib/libpng.lib)
      set(${MyModule}.LibPng.HeaderFilesDirectory ${MyDependenciesDirectory}/my-libpng-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.LibPng.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.LibPng.HeaderFilesDirectory})

    # freetype.
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.FreeType.Libraries ${MyDependenciesDirectory}/my-freetype-$<LOWER_CASE:$<CONFIG>>-x64/lib/freetype.lib)
      set(${MyModule}.FreeType.HeaderFilesDirectory ${MyDependenciesDirectory}/my-freetype-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.FreeType.Libraries ${MyDependenciesDirectory}/my-freetype-$<LOWER_CASE:$<CONFIG>>-x86/lib/freetype.lib)
      set(${MyModule}.FreeType.HeaderFilesDirectory ${MyDependenciesDirectory}/my-freetype-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.FreeType.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.FreeType.HeaderFilesDirectory})

  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Imaging/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Configure.h.i)
  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Imaging/Configure.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/ImageWriterParameters.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/ImageWriterParameters.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/ImageWriter.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/ImageWriter.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/ImageManager.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/ImageManager.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Include.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Include.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/PixelBuffer.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/PixelBuffer.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/PixelFormat.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/PixelFormat.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/IcoImageWriter.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/IcoImageWriter.h)

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Linux/PngImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Linux/PngImageWriter.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Linux/BmpImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Linux/BmpImageWriter.h)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Linux/_stb_image_write.h)
  endif()

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/WicImageWriterBase.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/WicImageWriterBase.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/BmpImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/BmpImageWriter.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/PngImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/PngImageWriter.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/TifImageWriter.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/TifImageWriter.h)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Imaging/Windows/MultiByteToWideCharZeroTerminated.h)
  endif()

  list(APPEND ${MyModule}.PrivateLibraries ${MyProjectName}.Ring2 ${MyProjectName}.DDL ${MyProjectName}.ARMS)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Engine")

endif()
