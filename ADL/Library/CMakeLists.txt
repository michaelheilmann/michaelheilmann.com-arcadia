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

set(MyFolder ADL)

# Create library.
set(MyLibraryName ${MyProjectName}.ADL)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/ADL/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/ADL/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/ADL/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/ADL/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Diagnostics.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Diagnostics.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Reader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Reader.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Reader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Reader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Context.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Context.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Reference.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Reference.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/CheckerboardFillOperationDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/CheckerboardFillOperationDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/CheckerboardFillOperationReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/CheckerboardFillOperationReader.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ColorDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ColorDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ColorReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ColorReader.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/FillOperationDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/FillOperationDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/FillOperationReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/FillOperationReader.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialReader.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialType.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/AmbientColorSource.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/AmbientColorSource.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MeshDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MeshDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MeshReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MeshReader.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ModelDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ModelDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ModelReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ModelReader.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/PixelBufferDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/PixelBufferDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/PixelBufferReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/PixelBufferReader.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/TextureDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/TextureDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/TextureReader.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/TextureReader.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.DDLS ${MyProjectName}.DDL ${MyProjectName}.Ring2)

  if (${${MyLibraryName}_OperatingSystem} STREQUAL ${${MyLibraryName}_OperatingSystem_Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER ${MyFolder})

endif()
