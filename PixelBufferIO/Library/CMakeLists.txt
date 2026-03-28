# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

cmake_minimum_required(VERSION 3.29)

set(MyModule ${MyProjectName}.PixelBufferIO)

if (NOT TARGET ${MyModule})
  BeginProduct(${MyModule} library)

  # Always use libpng under Linux.
  if (${${MyModule}_OperatingSystem} STREQUAL ${${MyModule}_OperatingSystem_Linux})
    find_package(PNG)
    if (NOT TARGET PNG::PNG)
      message(FATAL_ERROR "libPNG not found")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries PNG::PNG)
  endif()

  # Always use zlib, libpng and freetype under Windows.
  if (${${MyModule}_OperatingSystem} STREQUAL ${${MyModule}_OperatingSystem_Windows})
    # zlib.
    if (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X64})
      set(${MyModule}.zlib.Libraries ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/zlib/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,zsd.lib,zs.lib>)
      set(${MyModule}.zlib.HeaderFilesDirectory ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/zlib/include)
    elseif (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X86})
      set(${MyModule}.zlib.Libraries ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/zlib/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,zsd.lib,zs.lib>)
      set(${MyModule}.zlib.HeaderFilesDirectory ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/zlib/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.zlib.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.zlib.HeaderFilesDirectory})

    # libpng.
    if (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X64})
      set(${MyModule}.libPNG.Libraries ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/libpng/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,libpng18_staticd.lib,libpng18_static.lib>)
      set(${MyModule}.libPNG.HeaderFilesDirectory ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/libpng/include)
    elseif (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X86})
      set(${MyModule}.libPNG.Libraries ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/libpng/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,libpng18_staticd.lib,libpng18_static.lib>)
      set(${MyModule}.libPNG.HeaderFilesDirectory ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/libpng/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.libPNG.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.libPNG.HeaderFilesDirectory})

    # freetype.
    if (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X64})
      set(${MyModule}.FreeType.Libraries ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/freetype/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,freetyped.lib,freetype.lib>)
      set(${MyModule}.FreeType.HeaderFilesDirectory ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/freetype/include)
    elseif (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X86})
      set(${MyModule}.FreeType.Libraries ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/freetype/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,freetyped.lib,freetype.lib>)
      set(${MyModule}.FreeType.HeaderFilesDirectory ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/freetype/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.FreeType.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.FreeType.HeaderFilesDirectory})

  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/PixelBufferIO/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/PixelBufferIO/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/PixelBufferIO/Configure.h.i)
  OnConfigurationFile(${MyModule} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/PixelBufferIO/Configure.h)

  OnSourceFile(${MyModule} Arcadia/PixelBufferIO/ImageWriterParameters.c)
  OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/ImageWriterParameters.h)
  OnSourceFile(${MyModule} Arcadia/PixelBufferIO/ImageWriter.c)
  OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/ImageWriter.h)
  OnSourceFile(${MyModule} Arcadia/PixelBufferIO/ImageManager.c)
  OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/ImageManager.h)
  OnSourceFile(${MyModule} Arcadia/PixelBufferIO/Include.c)
  OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Include.h)

  OnSourceFile(${MyModule} Arcadia/PixelBufferIO/ICOImageWriter.c)
  OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/ICOImageWriter.h)

  if (${${MyModule}_OperatingSystem} STREQUAL ${${MyModule}_OperatingSystem_Linux})
    OnSourceFile(${MyModule} Arcadia/PixelBufferIO/Linux/PNGImageWriter.c)
    OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Linux/PNGImageWriter.h)
    OnSourceFile(${MyModule} Arcadia/PixelBufferIO/Linux/BMPImageWriter.c)
    OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Linux/BMPImageWriter.h)
    OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Linux/_stb_image_write.h)
  endif()

  if (${${MyModule}_OperatingSystem} STREQUAL ${${MyModule}_OperatingSystem_Windows})
    OnSourceFile(${MyModule} Arcadia/PixelBufferIO/Windows/WICImageWriterBase.c)
    OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Windows/WICImageWriterBase.h)
    OnSourceFile(${MyModule} Arcadia/PixelBufferIO/Windows/BMPImageWriter.c)
    OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Windows/BMPImageWriter.h)
    OnSourceFile(${MyModule} Arcadia/PixelBufferIO/Windows/PNGImageWriter.c)
    OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Windows/PNGImageWriter.h)
    OnSourceFile(${MyModule} Arcadia/PixelBufferIO/Windows/TIFImageWriter.c)
    OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Windows/TIFImageWriter.h)
    OnHeaderFile(${MyModule} Arcadia/PixelBufferIO/Windows/MultiByteToWideCharZeroTerminated.h)
  endif()

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Media ${MyProjectName}.ADL)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "PixelBufferIO")

endif()
