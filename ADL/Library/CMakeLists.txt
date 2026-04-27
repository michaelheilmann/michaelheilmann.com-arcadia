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

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/ConstantDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/ConstantDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/ConstantReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/ConstantReader.module.h)
  
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/SawtoothWaveDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/SawtoothWaveDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/SawtoothWaveReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/SawtoothWaveReader.module.h)
  
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/SineWaveDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/SineWaveDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/SineWaveReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/SineWaveReader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/WhiteNoiseDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/WhiteNoiseDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/WhiteNoiseReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/DSP/WhiteNoiseReader.module.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Audials/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Audials/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Audials/SampleBufferDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Audials/SampleBufferDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Audials/SampleBufferReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Audials/SampleBufferReader.module.h)

  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/CheckerboardFillOperationDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/CheckerboardFillOperationDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/CheckerboardFillOperationReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/CheckerboardFillOperationReader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ColorDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ColorDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ColorReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ColorReader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/FillOperationDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/FillOperationDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/FillOperationReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/FillOperationReader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialReader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialType.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MaterialType.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/AmbientColorSource.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/AmbientColorSource.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MeshDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MeshDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MeshReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/MeshReader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ModelDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ModelDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ModelReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/ModelReader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/PixelBufferDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/PixelBufferDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/PixelBufferReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/PixelBufferReader.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/TextureDefinition.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/TextureDefinition.h)
  OnSourceFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/TextureReader.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/ADL/Definitions/Visuals/TextureReader.module.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.DDLS ${MyProjectName}.DDL ${MyProjectName}.Ring2)

  if (${${MyLibraryName}_OperatingSystem} STREQUAL ${${MyLibraryName}_OperatingSystem_Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER ${MyFolder})

endif()
