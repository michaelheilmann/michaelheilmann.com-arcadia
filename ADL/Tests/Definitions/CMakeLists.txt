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

# Create test.
set(this ${MyProjectName}.ADL.Tests.Definitions)

if (NOT TARGET ${this})

  BeginProduct(${this} test)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h.i)

  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/Main.c)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Color.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Color.h)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Material.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Material.h)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Mesh.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Mesh.h)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Model.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Model.h)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/PixelBuffer.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/PixelBuffer.h)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Texture.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/Visuals/Texture.h)

  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/DSP/Constant.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/DSP/Constant.h)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/DSP/SawtoothWave.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/DSP/SawtoothWave.h)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/DSP/SineWave.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/DSP/SineWave.h)
  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/DSP/WhiteNoise.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/DSP/WhiteNoise.h)

  OnSourceFile(${this} Arcadia.ADL.Tests.Definitions/Audials/SampleBuffer.c)
  OnHeaderFile(${this} Arcadia.ADL.Tests.Definitions/Audials/SampleBuffer.h)

  OnAssetsDirectory(${this}.CopyAssets ${CMAKE_CURRENT_SOURCE_DIR}/Assets)

  OnModuleDependency(${this} ${MyProjectName}.ADL PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.DDLS PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.DDL PRIVATE)

  EndProduct(${this})

  target_include_directories(${this} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources ${CMAKE_CURRENT_BINARY_DIR}/Sources)
  set_target_properties(${this} PROPERTIES FOLDER ${MyFolder})

  CopyProductAssets(${this} ${MyFolder} ${CMAKE_CURRENT_BINARY_DIR}/Assets)

endif()
