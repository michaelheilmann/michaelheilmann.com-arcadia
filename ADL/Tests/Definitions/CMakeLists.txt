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

cmake_minimum_required(VERSION 4.1.3)

set(MyFolder ADL)

# Create test.
set(MyTestName ${MyProjectName}.ADL.Tests.Definitions)

if (NOT TARGET ${MyTestName})

  BeginProduct(${MyTestName} test)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h.i
                 ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h @ONLY)
  list(APPEND ${MyTestName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h.i)
  OnHeaderFile(${MyTestName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Configure.h)

  OnSourceFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Main.c)

  OnSourceFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Color.c)
  OnHeaderFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Color.h)
  OnSourceFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Material.c)
  OnHeaderFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Material.h)
  OnSourceFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Mesh.c)
  OnHeaderFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Mesh.h)
  OnSourceFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Model.c)
  OnHeaderFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Model.h)
  OnSourceFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/PixelBuffer.c)
  OnHeaderFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/PixelBuffer.h)
  OnSourceFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Texture.c)
  OnHeaderFile(${MyTestName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.ADL.Tests.Definitions/Texture.h)

  list(APPEND ${MyTestName}.PrivateLibraries ${MyProjectName}.ADL ${MyProjectName}.DDLS ${MyProjectName}.DDL)

  EndProduct(${MyTestName})

  target_include_directories(${MyTestName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Sources ${CMAKE_CURRENT_BINARY_DIR}/Sources)
  set_target_properties(${MyTestName} PROPERTIES FOLDER ${MyFolder})

  CopyProductAssets(${MyTestName}.CopyAssets ${MyFolder} ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets)
  add_dependencies(${MyTestName} ${MyTestName}.CopyAssets)

endif()
