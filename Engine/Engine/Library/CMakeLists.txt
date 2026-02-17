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

set(MyModule ${MyProjectName}.Engine)

if (NOT TARGET ${MyModule})

  BeginProduct(${MyModule} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Configure.h.i)
  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Configure.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Include.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Engine.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Engine.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Event.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Event.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Backend.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Backend.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/BackendContext.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/BackendContext.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Node.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Node.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/NodeFactory.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/NodeFactory.h)

  # >>
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Backend.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Backend.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/BackendContext.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/BackendContext.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/CullMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/CullMode.h)
  
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/DepthCompareFunction.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/DepthCompareFunction.h)
  
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/FillMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/FillMode.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Include.h)
  
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Node.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Node.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/NodeFactory.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/NodeFactory.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/CameraNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/CameraNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/EnterPassNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/EnterPassNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/FrameBufferNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/FrameBufferNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/MaterialNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/MaterialNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/MeshNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/MeshNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/ModelNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/ModelNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/PixelBufferNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/PixelBufferNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/RenderScene.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/RenderScene.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/TextureNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/TextureNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/ViewportNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Nodes/ViewportNode.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/TextureAddressMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/TextureAddressMode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/TextureFilter.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/TextureFilter.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexDescriptor.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexDescriptor.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexDescriptor.module.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexDescriptor.module.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexDescriptorBuilder.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexDescriptorBuilder.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexElementDescriptor.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexElementDescriptor.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexElementSemantics.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexElementSemantics.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexElementSyntactics.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VertexElementSyntactics.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/ConstantBlock.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/ConstantBlock.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Field.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Field.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Program.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Program.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Scalar.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Scalar.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Tree/BinaryExprNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Tree/BinaryExprNode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Tree/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Tree/Include.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Tree/Node.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/VPL/Tree/Node.h)
  
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/WindingMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/WindingMode.h)


  ###########
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/ApplicationEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/ApplicationEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/ApplicationQuitRequestedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/ApplicationQuitRequestedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/CanvasEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/CanvasEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/CanvasActivationStateChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/CanvasActivationStateChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/CanvasDPIChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/CanvasDPIChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/CanvasSizeChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/CanvasSizeChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/KeyboardKey.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/KeyboardKey.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/KeyboardKey.i)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/KeyboardKeyAction.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/KeyboardKeyAction.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/KeyboardKeyEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/KeyboardKeyEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/MouseButtonAction.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/MouseButtonAction.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/MouseButtonEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/MouseButtonEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/MousePointerAction.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/MousePointerAction.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/MousePointerEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/MousePointerEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/WindowClosedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/WindowClosedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/WindowPositionChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/WindowPositionChangedEvent.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/WindowSizeChangedEvent.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Events/WindowSizeChangedEvent.h)



  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Diagnostics.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Diagnostics.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Icon.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Icon.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Window.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Window.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/WindowBackend.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/WindowBackend.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Configuration.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/Configuration.h)

  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/DisplayMode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/DisplayMode.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/DisplayDevice.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Visuals/DisplayDevice.h)

  ###########

  # <<

  # >>
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/Backend.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/Backend.h)  
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/BackendContext.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/BackendContext.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/Include.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/Include.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/Node.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/Node.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/NodeFactory.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/NodeFactory.h)
  OnSourceFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/Nodes/SoundSourceNode.c)
  OnHeaderFile(${MyModule} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Audials/Nodes/SoundSourceNode.h)
  # <<

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Math ${MyProjectName}.Imaging)
  list(APPEND ${MyModule}.PrivateLibraries ${MyProjectName}.Ring2 ${MyProjectName}.DDL)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Engine")

endif()
