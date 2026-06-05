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

set(this ${MyProjectName}.PixelBufferIO)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  # Always use libpng under Linux.
  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    find_package(PNG)
    if (NOT TARGET PNG::PNG)
      message(FATAL_ERROR "libPNG not found")
    endif()
    list(APPEND ${this}.PrivateLibraries PNG::PNG)
  endif()

  # Always use zlib, libpng and freetype under Windows.
  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Windows})
    # zlib.
    if (${${this}_InstructionSetArchitecture} STREQUAL ${${this}_InstructionSetArchitecture_X64})
      set(${this}.zlib.Libraries ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/zlib/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,zsd.lib,zs.lib>)
      set(${this}.zlib.HeaderFilesDirectory ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/zlib/include)
    elseif (${${this}_InstructionSetArchitecture} STREQUAL ${${this}_InstructionSetArchitecture_X86})
      set(${this}.zlib.Libraries ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/zlib/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,zsd.lib,zs.lib>)
      set(${this}.zlib.HeaderFilesDirectory ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/zlib/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${this}.PrivateLibraries ${${this}.zlib.Libraries})
    list(APPEND ${this}.IncludeDirectories ${${this}.zlib.HeaderFilesDirectory})

    # libpng.
    if (${${this}_InstructionSetArchitecture} STREQUAL ${${this}_InstructionSetArchitecture_X64})
      set(${this}.libPNG.Libraries ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/libpng/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,libpng18_staticd.lib,libpng18_static.lib>)
      set(${this}.libPNG.HeaderFilesDirectory ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/libpng/include)
    elseif (${${this}_InstructionSetArchitecture} STREQUAL ${${this}_InstructionSetArchitecture_X86})
      set(${this}.libPNG.Libraries ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/libpng/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,libpng18_staticd.lib,libpng18_static.lib>)
      set(${this}.libPNG.HeaderFilesDirectory ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/libpng/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${this}.PrivateLibraries ${${this}.libPNG.Libraries})
    list(APPEND ${this}.IncludeDirectories ${${this}.libPNG.HeaderFilesDirectory})

    # freetype.
    if (${${this}_InstructionSetArchitecture} STREQUAL ${${this}_InstructionSetArchitecture_X64})
      set(${this}.FreeType.Libraries ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/freetype/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,freetyped.lib,freetype.lib>)
      set(${this}.FreeType.HeaderFilesDirectory ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/freetype/include)
    elseif (${${this}_InstructionSetArchitecture} STREQUAL ${${this}_InstructionSetArchitecture_X86})
      set(${this}.FreeType.Libraries ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/freetype/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,freetyped.lib,freetype.lib>)
      set(${this}.FreeType.HeaderFilesDirectory ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/freetype/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${this}.PrivateLibraries ${${this}.FreeType.Libraries})
    list(APPEND ${this}.IncludeDirectories ${${this}.FreeType.HeaderFilesDirectory})

  endif()

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/PixelBufferIO/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/PixelBufferIO/Configure.h.i)

  OnSourceFile(${this} Arcadia/PixelBufferIO/ImageWriterParameters.c)
  OnHeaderFile(${this} Arcadia/PixelBufferIO/ImageWriterParameters.h)
  OnSourceFile(${this} Arcadia/PixelBufferIO/ImageWriter.c)
  OnHeaderFile(${this} Arcadia/PixelBufferIO/ImageWriter.h)
  OnSourceFile(${this} Arcadia/PixelBufferIO/ImageManager.c)
  OnHeaderFile(${this} Arcadia/PixelBufferIO/ImageManager.h)
  OnSourceFile(${this} Arcadia/PixelBufferIO/Include.c)
  OnHeaderFile(${this} Arcadia/PixelBufferIO/Include.h)

  OnSourceFile(${this} Arcadia/PixelBufferIO/ICOImageWriter.c)
  OnHeaderFile(${this} Arcadia/PixelBufferIO/ICOImageWriter.h)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    OnSourceFile(${this} Arcadia/PixelBufferIO/Linux/PNGImageWriter.c)
    OnHeaderFile(${this} Arcadia/PixelBufferIO/Linux/PNGImageWriter.h)
    OnSourceFile(${this} Arcadia/PixelBufferIO/Linux/BMPImageWriter.c)
    OnHeaderFile(${this} Arcadia/PixelBufferIO/Linux/BMPImageWriter.h)
    OnHeaderFile(${this} Arcadia/PixelBufferIO/Linux/_stb_image_write.h)
  endif()

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Windows})
    OnSourceFile(${this} Arcadia/PixelBufferIO/Windows/WICImageWriterBase.c)
    OnHeaderFile(${this} Arcadia/PixelBufferIO/Windows/WICImageWriterBase.h)
    OnSourceFile(${this} Arcadia/PixelBufferIO/Windows/BMPImageWriter.c)
    OnHeaderFile(${this} Arcadia/PixelBufferIO/Windows/BMPImageWriter.h)
    OnSourceFile(${this} Arcadia/PixelBufferIO/Windows/PNGImageWriter.c)
    OnHeaderFile(${this} Arcadia/PixelBufferIO/Windows/PNGImageWriter.h)
    OnSourceFile(${this} Arcadia/PixelBufferIO/Windows/TIFImageWriter.c)
    OnHeaderFile(${this} Arcadia/PixelBufferIO/Windows/TIFImageWriter.h)
    OnHeaderFile(${this} Arcadia/PixelBufferIO/Windows/MultiByteToWideCharZeroTerminated.h)
  endif()

  OnModuleDependency(${this} ${MyProjectName}.Media)
  OnModuleDependency(${this} ${MyProjectName}.ADL)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "PixelBufferIO")

endif()
