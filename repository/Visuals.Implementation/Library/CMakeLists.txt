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

cmake_minimum_required(VERSION 3.20)

set(MyModule ${MyProjectName}.Visuals.Implementation)

if (NOT TARGET ${MyModule})
  option(${MyModule}.Direct3D12.Enabled "TRUE enables Direct3D 12 support. FALSE disables Direct3D 12 support. Default is FALSE" FALSE)
  option(${MyModule}.OpenGL4.Enabled "TRUE enables OpenGL 4 support. FALSE disables OpenGL 4 support. Default is FALSE" FALSE)
  option(${MyModule}.Vulkan.Enabled "TRUE enables Vulkan support. FALSE disables Vulkan support. Default is FALSE" FALSE)

  BeginProduct(${MyModule} library)

  if (${MyModule}.Direct3D12.Enabled)
    set(${MyModule}.Configuration.Direct3D12.Enabled 1)
  else()
    set(${MyModule}.Configuration.Direct3D12.Enabled 0)
  endif()

  if (${MyModule}.OpenGL4.Enabled)
    set(${MyModule}.Configuration.OpenGL4.Enabled 1)
  else()
    set(${MyModule}.Configuration.OpenGL4.Enabled 0)
  endif()

  if (${MyModule}.Vulkan.Enabled)
    set(${MyModule}.Configuration.Vulkan.Enabled 1)
  else()
    set(${MyModule}.Configuration.Vulkan.Enabled 0)
  endif()

  # X11/OpenGL under Linux.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux} AND ${MyModule}.OpenGL4.Enabled)
    # Find X11.
    find_package(X11)
    if (NOT X11_FOUND)
      message(FATAL_ERROR " - X11 not found")
    else()
      message(STATUS " - X11 found - X11_LIBRARIES = ${X11_LIBRARIES}")
      list(APPEND ${MyModule}.PrivateLibraries ${X11_LIBRARIES})
    endif()
    if (NOT X11_Xrandr_FOUND)
      message(FATAL_ERROR " - X11 XRANDR not found")
    else()
      message(STATUS " - X11 XRANDR found - X11_Xrandr_LIB = ${X11_Xrandr_LIB}")
      list(APPEND ${MyModule}.PrivateLibraries ${X11_Xrandr_LIB})
    endif()
    # Find OpenGL.
    find_package(OpenGL)
    if (NOT OPENGL_FOUND)
      message(FATAL_ERROR " - OpenGL not found")
    else()
      #message(STATUS " - OpenGL found - OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")
      list(APPEND ${MyModule}.PrivateLibraries ${OPENGL_LIBRARIES})
    endif()
    set(${MyModule}.Backend ${${MyModule}.Backend.OpenGl})
  endif()

  # Always use libpng under Linux.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux})
    find_package(PNG)
    if (NOT TARGET PNG::PNG)
      message(FATAL_ERROR "libPNG not found")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries PNG::PNG)
  endif()

  # Always use Shcore.lib under Windows.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    list(APPEND ${MyModule}.PrivateLibraries Shcore.lib)
  endif()

  # Always use zlib, libpng and freetype under Windows.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    set(MyDependenciesDirectory "C:/arcadia-dependencies")

    # zlib.
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.zlib.Libraries ${MyDependenciesDirectory}/my-zlib-$<LOWER_CASE:$<CONFIG>>-x64/lib/zlib.lib)
      set(${MyModule}.zlib.HeaderFilesDirectory ${MyDependenciesDirectory}/my-zlib-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.zlib.Libraries ${MyDependenciesDirectory}/my-zlib-$<LOWER_CASE:$<CONFIG>>-x86/lib/zlib.lib)
      set(${MyModule}.zlib.HeaderFilesDirectory ${MyDependenciesDirectory}/my-zlib-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.zlib.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.zlib.HeaderFilesDirectory})

    # libpng.
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.LibPng.Libraries ${MyDependenciesDirectory}/my-libpng-$<LOWER_CASE:$<CONFIG>>-x64/lib/libpng.lib)
      set(${MyModule}.LibPng.HeaderFilesDirectory ${MyDependenciesDirectory}/my-libpng-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.LibPng.Libraries ${MyDependenciesDirectory}/my-libpng-$<LOWER_CASE:$<CONFIG>>-x86/lib/libpng.lib)
      set(${MyModule}.LibPng.HeaderFilesDirectory ${MyDependenciesDirectory}/my-libpng-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.LibPng.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.LibPng.HeaderFilesDirectory})

    # freetype.
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.FreeType.Libraries ${MyDependenciesDirectory}/my-freetype-$<LOWER_CASE:$<CONFIG>>-x64/lib/freetype.lib)
      set(${MyModule}.FreeType.HeaderFilesDirectory ${MyDependenciesDirectory}/my-freetype-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.FreeType.Libraries ${MyDependenciesDirectory}/my-freetype-$<LOWER_CASE:$<CONFIG>>-x86/lib/freetype.lib)
      set(${MyModule}.FreeType.HeaderFilesDirectory ${MyDependenciesDirectory}/my-freetype-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.FreeType.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.FreeType.HeaderFilesDirectory})

  endif()

  # Enable WGL/OpenGL 4 under Windows.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows} AND ${${MyModule}.OpenGL4.Enabled})
    set(MyDependenciesDirectory "C:/arcadia-dependencies")
    find_package(OpenGL REQUIRED)
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.OpenGL.HeaderFilesDirectory ${MyDependenciesDirectory}/my-opengl-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.OpenGL.HeaderFilesDirectory ${MyDependenciesDirectory}/my-opengl-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    message(STATUS " - ${MyModule}.OpenGl.HeaderFilesDirectory = ${${MyModule}.OpenGl.HeaderFilesDirectory}")
    list(APPEND ${MyModule}.PrivateLibraries ${OPENGL_LIBRARIES})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.OpenGL.HeaderFilesDirectory})
    set(${MyModule}.Backend ${${MyModule}.Backend.OpenGL})
  endif()

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Scene/CameraNode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Scene/CameraNode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Scene/MeshNode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Scene/MeshNode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Scene/ViewportNode.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Scene/ViewportNode.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Scene/MeshContext.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Scene/MeshContext.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/SceneNodeFactory.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/SceneNodeFactory.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/BackendContext.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/BackendContext.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resource.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/ConstantBufferResource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/ConstantBufferResource.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/VertexBufferResource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/VertexBufferResource.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/ViewportResource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/ViewportResource.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/VertexProgramResource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/VertexProgramResource.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/FragmentProgramResource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/FragmentProgramResource.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/ProgramResource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/ProgramResource.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/MeshContextResource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/MeshContextResource.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/MeshResource.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Resources/MeshResource.h)

  # Enable OpenGL 4.
  if (${${MyModule}.OpenGL4.Enabled})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/ConstantBufferResource.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/ConstantBufferResource.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexBufferResource.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/ViewportResource.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/ViewportResource.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexProgramResource.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/VertexProgramResource.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/FragmentProgramResource.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/FragmentProgramResource.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/ProgramResource.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/MeshResource.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/MeshResource.h)

    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/Utilities.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Resources/Utilities.h)

    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Shared/Functions.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Shared/Functions.h)
    list(APPEND ${MyModule}.InlayFiles  ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Shared/Functions.i)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Backend.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/Backend.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/BackendContext.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/BackendContext.h)
  endif()

  # Enable Direct3D 12 under Windows.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows} AND ${${MyModule}.Direct3D12.Enabled})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Direct3D12/Backend.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Direct3D12/Backend.h)
  endif()

  # Enable Vulkan under Windows.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows} AND ${${MyModule}.Vulkan.Enabled})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Vulkan/Backend.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Vulkan/Backend.h)
  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/Implementation/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Configure.h.i)
  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/Implementation/Configure.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Include.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Include.h)

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/_edid.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/_edid.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/DisplayDevice.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/DisplayDevice.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/DisplayMode.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/DisplayMode.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Include.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Include.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Icon.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Icon.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/ErrorHandler.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/ErrorHandler.h)
  endif()

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/DisplayDevice.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/DisplayDevice.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/DisplayMode.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/DisplayMode.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Bitmap.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Bitmap.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Icon.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Icon.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/TextureFont.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/TextureFont.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/_WindowText.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/_WindowText.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/_CharConv.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/_CharConv.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/_GetDisplayDevices.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/_GetDisplayDevices.h)
  endif()

  if (${${MyModule}.OpenGL4.Enabled} AND (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux}))
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/GLX/_Extensions.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/GLX/_Extensions.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/GLX/_Configurations.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/GLX/_Configurations.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/GLX/WindowBackend.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/GLX/WindowBackend.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/GLX/BackendContext.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/GLX/BackendContext.h)
  endif()

  if (${${MyModule}.OpenGL4.Enabled} AND (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows}))
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/SystemWindow.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/SystemWindow.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/FactoryContext.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/FactoryContext.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/FactoryWindow.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/FactoryWindow.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/BackendContext.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/BackendContext.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/WindowBackend.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/OpenGL4/WGL/WindowBackend.h)
  endif()

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Visuals ${MyProjectName}.Imaging)
  list(APPEND ${MyModule}.PrivateLibraries ${MyProjectName}.Visuals.VPL.Backends.GLSL ${MyProjectName}.Math ${MyProjectName}.Ring2 ${MyProjectName}.DataDefinitionLanguage ${MyProjectName}.ARMS)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Backends")

endif()
