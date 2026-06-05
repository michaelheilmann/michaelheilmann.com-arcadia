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

set(this ${MyProjectName}.Engine)

if (NOT TARGET ${this})

  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Engine/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Engine/Configure.h.i)

  OnSourceFile(${this} Arcadia/Engine/Include.c)
  OnHeaderFile(${this} Arcadia/Engine/Include.h)

  OnSourceFile(${this} Arcadia/Engine/Engine.c)
  OnHeaderFile(${this} Arcadia/Engine/Engine.h)
  OnSourceFile(${this} Arcadia/Engine/Event.c)
  OnHeaderFile(${this} Arcadia/Engine/Event.h)

  OnSourceFile(${this} Arcadia/Engine/Backend.c)
  OnHeaderFile(${this} Arcadia/Engine/Backend.h)
  OnSourceFile(${this} Arcadia/Engine/BackendContext.c)
  OnHeaderFile(${this} Arcadia/Engine/BackendContext.h)

  OnSourceFile(${this} Arcadia/Engine/Node.c)
  OnHeaderFile(${this} Arcadia/Engine/Node.h)
  OnSourceFile(${this} Arcadia/Engine/NodeFactory.c)
  OnHeaderFile(${this} Arcadia/Engine/NodeFactory.h)

  # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>

  OnSourceFile(${this} Arcadia/Engine/Audials/Resource.c)
  OnHeaderFile(${this} Arcadia/Engine/Audials/Resource.h)
  OnSourceFile(${this} Arcadia/Engine/Audials/Resources/SoundSourceResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Audials/Resources/SoundSourceResource.h)

  OnSourceFile(${this} Arcadia/Engine/Audials/Backend.c)
  OnHeaderFile(${this} Arcadia/Engine/Audials/Backend.h)
  OnSourceFile(${this} Arcadia/Engine/Audials/BackendContext.c)
  OnHeaderFile(${this} Arcadia/Engine/Audials/BackendContext.h)
  OnSourceFile(${this} Arcadia/Engine/Audials/Include.c)
  OnHeaderFile(${this} Arcadia/Engine/Audials/Include.h)
  OnSourceFile(${this} Arcadia/Engine/Audials/Node.c)
  OnHeaderFile(${this} Arcadia/Engine/Audials/Node.h)
  OnSourceFile(${this} Arcadia/Engine/Audials/NodeFactory.c)
  OnHeaderFile(${this} Arcadia/Engine/Audials/NodeFactory.h)
  OnSourceFile(${this} Arcadia/Engine/Audials/Nodes/SoundSourceNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Audials/Nodes/SoundSourceNode.h)

  # <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  # ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>
  OnSourceFile(${this} Arcadia/Engine/Visuals/Backend.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Backend.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/BackendContext.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/BackendContext.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/CullMode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/CullMode.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/DepthCompareFunction.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/DepthCompareFunction.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/FillMode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/FillMode.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/Include.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Include.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/Node.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Node.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/NodeFactory.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/NodeFactory.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/CameraNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/CameraNode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/EnterPassNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/EnterPassNode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/FrameBufferNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/FrameBufferNode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/MaterialNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/MaterialNode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/MeshNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/MeshNode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/ModelNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/ModelNode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/PixelBufferNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/PixelBufferNode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/RenderScene.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/RenderScene.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/TextureNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/TextureNode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Nodes/ViewportNode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Nodes/ViewportNode.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/TextureAddressMode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/TextureAddressMode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/TextureFilter.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/TextureFilter.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/VertexDescriptor.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/VertexDescriptor.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/VertexDescriptor.module.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/VertexDescriptor.module.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/VertexDescriptorBuilder.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/VertexDescriptorBuilder.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/VertexElementDescriptor.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/VertexElementDescriptor.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/VertexElementSemantics.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/VertexElementSemantics.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/VertexElementSyntactics.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/VertexElementSyntactics.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/WindingMode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/WindingMode.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/ApplicationEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/ApplicationEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/ApplicationQuitRequestedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/ApplicationQuitRequestedEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/CanvasEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/CanvasEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/CanvasActivationStateChangedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/CanvasActivationStateChangedEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/CanvasDPIChangedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/CanvasDPIChangedEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/CanvasSizeChangedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/CanvasSizeChangedEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/KeyboardKey.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/KeyboardKey.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/KeyboardKey.i)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/KeyboardKeyAction.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/KeyboardKeyAction.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/KeyboardKeyEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/KeyboardKeyEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/MouseButtonAction.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/MouseButtonAction.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/MouseButtonEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/MouseButtonEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/MousePointerAction.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/MousePointerAction.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/MousePointerEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/MousePointerEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/WindowClosedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/WindowClosedEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/WindowPositionChangedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/WindowPositionChangedEvent.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Events/WindowSizeChangedEvent.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Events/WindowSizeChangedEvent.h)


  OnSourceFile(${this} Arcadia/Engine/Visuals/Diagnostics.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Diagnostics.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/Icon.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Icon.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Window.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Window.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/WindowBackend.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/WindowBackend.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Configuration.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Configuration.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/DisplayMode.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/DisplayMode.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/DisplayDevice.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/DisplayDevice.h)

  OnSourceFile(${this} Arcadia/Engine/Visuals/Resource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/ConstantBufferResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/ConstantBufferResource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/VertexBufferResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/VertexBufferResource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/ProgramResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/ProgramResource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/EnterPassResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/EnterPassResource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/MaterialResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/MaterialResource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/MeshResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/MeshResource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/ModelResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/ModelResource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/FrameBufferResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/FrameBufferResource.h)
  OnSourceFile(${this} Arcadia/Engine/Visuals/Resources/TextureResource.c)
  OnHeaderFile(${this} Arcadia/Engine/Visuals/Resources/TextureResource.h)

  # <~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  OnModuleDependency(${this} ${MyProjectName}.VPL)
  OnModuleDependency(${this} ${MyProjectName}.Math)
  OnModuleDependency(${this} ${MyProjectName}.PixelBufferIO)
  
  OnModuleDependency(${this} ${MyProjectName}.Ring2 PRIVATE)
  OnModuleDependency(${this} ${MyProjectName}.DDL PRIVATE)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Engine")

endif()
