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

set(MyModule ${MyProjectName}.Visuals)

if (NOT TARGET ${MyModule})

  BeginProduct(${MyModule} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Configure.h.i)
  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/Configure.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/CameraNode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/CameraNode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/Node.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/Node.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/MeshNode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/MeshNode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/ViewportNode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/ViewportNode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/MeshContext.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Scene/MeshContext.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/ApplicationEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/ApplicationEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/ApplicationQuitRequestedEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/ApplicationQuitRequestedEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasActivationStateChangedEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasActivationStateChangedEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasDpiChangedEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasDpiChangedEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasSizeChangedEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/CanvasSizeChangedEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKey.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKey.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKey.i)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKeyAction.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKeyAction.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKeyEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/KeyboardKeyEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MouseButtonAction.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MouseButtonAction.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MouseButtonEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MouseButtonEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MousePointerAction.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MousePointerAction.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MousePointerEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/MousePointerEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowClosedEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowClosedEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowPositionChangedEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowPositionChangedEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowSizeChangedEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Events/WindowSizeChangedEvent.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Backend.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Backend.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/BackendContext.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/BackendContext.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/SceneNodeFactory.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/SceneNodeFactory.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Diagnostics.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Diagnostics.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Commands/Command.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Commands/Command.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Commands/EmitCommand.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Commands/EmitCommand.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Icon.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Icon.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Window.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Window.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/WindowBackend.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/WindowBackend.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Configuration.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Configuration.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/CullMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/CullMode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DepthCompareFunction.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DepthCompareFunction.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/FillMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/FillMode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/TextureAddressMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/TextureAddressMode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/TextureFilter.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/TextureFilter.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementSemantics.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementSemantics.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementSyntax.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/VertexElementSyntax.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/WindingMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/WindingMode.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Include.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Include.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DisplayMode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DisplayMode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DisplayDevice.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/DisplayDevice.h)

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Math ${MyProjectName}.Engine ${MyProjectName}.Imaging)
  list(APPEND ${MyModule}.PrivateLibraries ${MyProjectName}.Ring2 ${MyProjectName}.DDL ${MyProjectName}.ARMS)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Engine")

endif()
