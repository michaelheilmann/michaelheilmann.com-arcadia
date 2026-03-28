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

set(MyLibraryName ${MyProjectName}.Engine)

if (NOT TARGET ${MyLibraryName})

  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Configure.h @ONLY)
  list(APPEND ${MyLibraryName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Engine.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Engine.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Event.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Event.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Backend.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Backend.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/BackendContext.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/BackendContext.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Node.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Node.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/NodeFactory.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/NodeFactory.h)

  # >>
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Backend.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Backend.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/BackendContext.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/BackendContext.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/CullMode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/CullMode.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/DepthCompareFunction.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/DepthCompareFunction.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/FillMode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/FillMode.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Include.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Node.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Node.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/NodeFactory.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/NodeFactory.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/CameraNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/CameraNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/EnterPassNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/EnterPassNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/FrameBufferNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/FrameBufferNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/MaterialNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/MaterialNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/MeshNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/MeshNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/ModelNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/ModelNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/PixelBufferNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/PixelBufferNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/RenderScene.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/RenderScene.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/TextureNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/TextureNode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/ViewportNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Nodes/ViewportNode.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/TextureAddressMode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/TextureAddressMode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/TextureFilter.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/TextureFilter.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexDescriptor.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexDescriptor.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexDescriptor.module.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexDescriptor.module.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexDescriptorBuilder.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexDescriptorBuilder.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexElementDescriptor.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexElementDescriptor.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexElementSemantics.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexElementSemantics.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexElementSyntactics.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/VertexElementSyntactics.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/WindingMode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/WindingMode.h)


  ###########
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/ApplicationEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/ApplicationEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/ApplicationQuitRequestedEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/ApplicationQuitRequestedEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/CanvasEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/CanvasEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/CanvasActivationStateChangedEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/CanvasActivationStateChangedEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/CanvasDPIChangedEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/CanvasDPIChangedEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/CanvasSizeChangedEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/CanvasSizeChangedEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/KeyboardKey.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/KeyboardKey.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/KeyboardKey.i)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/KeyboardKeyAction.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/KeyboardKeyAction.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/KeyboardKeyEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/KeyboardKeyEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/MouseButtonAction.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/MouseButtonAction.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/MouseButtonEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/MouseButtonEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/MousePointerAction.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/MousePointerAction.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/MousePointerEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/MousePointerEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/WindowClosedEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/WindowClosedEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/WindowPositionChangedEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/WindowPositionChangedEvent.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/WindowSizeChangedEvent.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Events/WindowSizeChangedEvent.h)



  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Diagnostics.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Diagnostics.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Icon.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Icon.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Window.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Window.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/WindowBackend.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/WindowBackend.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/Configuration.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/Configuration.h)

  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/DisplayMode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/DisplayMode.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Visuals/DisplayDevice.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Visuals/DisplayDevice.h)

  ###########

  # <<

  # >>
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Audials/Backend.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Audials/Backend.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Audials/BackendContext.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Audials/BackendContext.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Audials/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Audials/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Audials/Node.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Audials/Node.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Audials/NodeFactory.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Audials/NodeFactory.h)
  OnSourceFile(${MyLibraryName} Arcadia/Engine/Audials/Nodes/SoundSourceNode.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Engine/Audials/Nodes/SoundSourceNode.h)
  # <<

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.VPL ${MyProjectName}.Math ${MyProjectName}.Imaging)
  list(APPEND ${MyLibraryName}.PrivateLibraries ${MyProjectName}.Ring2 ${MyProjectName}.DDL)

  EndProduct(${MyLibraryName})

  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Engine")

endif()
