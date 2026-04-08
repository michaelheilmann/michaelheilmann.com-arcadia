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
set(MyTestName ${MyProjectName}.ADL.Tests.Definitions)

if (NOT TARGET ${MyTestName})

  BeginProduct(${MyTestName} test)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h.i
                 ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h @ONLY)
  list(APPEND ${MyTestName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h.i)
  OnConfigurationFile(${MyTestName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h)

  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Main.c)

  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Color.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Color.h)
  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Material.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Material.h)
  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Mesh.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Mesh.h)
  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Model.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Model.h)
  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/PixelBuffer.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/PixelBuffer.h)
  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Texture.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Visuals/Texture.h)

  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/DSP/Constant.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/DSP/Constant.h)
  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/DSP/SineWave.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/DSP/SineWave.h)
  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/DSP/WhiteNoise.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/DSP/WhiteNoise.h)

  OnSourceFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Audials/SampleBuffer.c)
  OnHeaderFile(${MyTestName} Arcadia.ADL.Tests.Definitions/Audials/SampleBuffer.h)

  list(APPEND ${MyTestName}.PrivateLibraries ${MyProjectName}.ADL ${MyProjectName}.DDLS ${MyProjectName}.DDL)

  EndProduct(${MyTestName})

  target_include_directories(${MyTestName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources ${CMAKE_CURRENT_BINARY_DIR}/Sources)
  set_target_properties(${MyTestName} PROPERTIES FOLDER ${MyFolder})

  CopyProductAssets(${MyTestName}.CopyAssets ${MyFolder} ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets)
  add_dependencies(${MyTestName} ${MyTestName}.CopyAssets)

endif()
