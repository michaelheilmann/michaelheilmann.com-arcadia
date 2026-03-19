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

set(MyDemoName ${MyProjectName}.Engine.Demo)

if (NOT TARGET ${MyDemoName})
  #message(STATUS "${MyDemoName}: ${MyProjectName}.Visuals.Implementation.OpenGL4.Enabled = ${${MyProjectName}.Visuals.Implementation.OpenGL4.Enabled}")
  set(${MyDemoName}.Enabled FALSE)

  # This demo requires at least one rendering backend.
  if (${${MyProjectName}.Engine.Visuals.Implementation.OpenGL4.Enabled})
    set(${MyDemoName}.Enabled TRUE)
  endif()
  if (${${MyProjectName}.Engine.Visuals.Implementation.Direct3D12.Enabled})
    set(${MyDemoName}.Enabled TRUE)
  endif()
  if (${${MyProjectName}.Engine.Visuals.Implementation.Vulkan.Enabled})
    set(${MyDemoName}.Enabled TRUE)
  endif()

  BeginProduct(${MyDemoName} executable)

  set(${MyDemoName}.Windows.ResourceFile ${CMAKE_CURRENT_SOURCE_DIR}/Resources.rc)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Demo/Configure.h @ONLY)
  list(APPEND ${MyDemoName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Configure.h.i)
  OnConfigurationFile(${MyDemoName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Demo/Configure.h)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Main.c)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Audials.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/Audials.h)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Visuals.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/Visuals.h)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Configuration.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/Configuration.h)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Scene.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/Scene.h)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Scenes/ArcadiaLogoScene.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/Scenes/ArcadiaLogoScene.h)
  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Scenes/MainScene.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/Scenes/MainScene.h)
  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Scenes/MainMenuScene.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/Scenes/MainMenuScene.h)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/SceneManager.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/SceneManager.h)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/AssetUtilities.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/AssetUtilities.h)

  OnSourceFile(${MyDemoName} Arcadia/Engine/Demo/Application.c)
  OnHeaderFile(${MyDemoName} Arcadia/Engine/Demo/Application.h)

  list(APPEND ${MyDemoName}.PrivateLibraries ${MyProjectName}.Engine.UI ${MyProjectName}.Application ${MyProjectName}.ADL ${MyProjectName}.DDL ${MyProjectName}.Engine.Audials.Implementation ${MyProjectName}.Engine.Visuals.Implementation)

  EndProduct(${MyDemoName})

  # Copy assets.
  if (${MyDemoName}.Enabled)
    CopyProductAssets(${MyDemoName}.CopyAssets "" ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets)
    add_dependencies(${MyDemoName} ${MyDemoName}.CopyAssets)
  endif()

endif()
