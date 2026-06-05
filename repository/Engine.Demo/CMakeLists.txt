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

set(this ${MyProjectName}.Engine.Demo)

if (NOT TARGET ${this})
  #message(STATUS "${this}: ${MyProjectName}.Visuals.Implementation.OpenGL4.Enabled = ${${MyProjectName}.Visuals.Implementation.OpenGL4.Enabled}")
  set(${this}.Enabled FALSE)

  # This demo requires at least one rendering backend.
  if (${${MyProjectName}.Engine.Visuals.Implementation.OpenGL4.Enabled})
    set(${this}.Enabled TRUE)
  endif()
  if (${${MyProjectName}.Engine.Visuals.Implementation.Direct3D12.Enabled})
    set(${this}.Enabled TRUE)
  endif()
  if (${${MyProjectName}.Engine.Visuals.Implementation.Vulkan.Enabled})
    set(${this}.Enabled TRUE)
  endif()

  BeginProduct(${this} executable)

  set(${this}.Windows.ResourceFile ${CMAKE_CURRENT_SOURCE_DIR}/Resources.rc)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Demo/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Demo/Configure.h.i)

  OnSourceFile(${this} Arcadia/Engine/Demo/Main.c)

  OnSourceFile(${this} Arcadia/Engine/Demo/Audials.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/Audials.h)

  OnSourceFile(${this} Arcadia/Engine/Demo/Visuals.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/Visuals.h)

  OnSourceFile(${this} Arcadia/Engine/Demo/Configuration.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/Configuration.h)

  OnSourceFile(${this} Arcadia/Engine/Demo/Scene.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/Scene.h)

  OnSourceFile(${this} Arcadia/Engine/Demo/Scenes/ArcadiaLogoScene.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/Scenes/ArcadiaLogoScene.h)
  OnSourceFile(${this} Arcadia/Engine/Demo/Scenes/MainScene.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/Scenes/MainScene.h)
  OnSourceFile(${this} Arcadia/Engine/Demo/Scenes/MainMenuScene.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/Scenes/MainMenuScene.h)

  OnSourceFile(${this} Arcadia/Engine/Demo/SceneManager.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/SceneManager.h)

  OnSourceFile(${this} Arcadia/Engine/Demo/AssetUtilities.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/AssetUtilities.h)

  OnSourceFile(${this} Arcadia/Engine/Demo/Application.c)
  OnHeaderFile(${this} Arcadia/Engine/Demo/Application.h)

  OnAssetsDirectory(${this} ${CMAKE_CURRENT_SOURCE_DIR}/Assets)

  OnModuleDependency(${this} ${MyProjectName}.Engine.UI PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.Application PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.ADL PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.DDL PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.Engine.Audials.Implementation PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.Engine.Visuals.Implementation PRIVATE)

  EndProduct(${this})

  # Copy assets.
  if (${this}.Enabled)
    CopyProductAssets(${this} "" ${CMAKE_CURRENT_BINARY_DIR}/Assets)
  endif()

endif()
