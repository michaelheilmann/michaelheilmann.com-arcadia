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
  option(${MyModule}.OpenGL4.Enabled "TRUE enables OpenGL support. FALSE disables OpenGL support. Default is FALSE" FALSE)

  BeginProduct(${MyModule} library)

  set(${MyModule}.Backend.None 0)
  set(${MyModule}.Backend.OpenGl 1)
  set(${MyModule}.Backend ${${MyModule}.Backend.None})

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

  # WGL/OpenGL under Windows.
  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows} AND ${${MyModule}.OpenGL4.Enabled})
    set(MyDependenciesDirectory "C:/arcadia-dependencies")
    find_package(OpenGL REQUIRED)
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.OpenGl.HeaderFilesDirectory ${MyDependenciesDirectory}/my-opengl-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.OpenGl.HeaderFilesDirectory ${MyDependenciesDirectory}/my-opengl-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    message(STATUS " - ${MyModule}.OpenGl.HeaderFilesDirectory = ${${MyModule}.OpenGl.HeaderFilesDirectory}")
    list(APPEND ${MyModule}.PrivateLibraries ${OPENGL_LIBRARIES})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.OpenGl.HeaderFilesDirectory})
    set(${MyModule}.Backend ${${MyModule}.Backend.OpenGl})
  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/Implementation/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Configure.h.i)
  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Visuals/Implementation/Configure.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Events/ApplicationEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Events/ApplicationEvent.h)
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Events/ApplicationQuitRequestedEvent.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Events/ApplicationQuitRequestedEvent.h)
  
  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Diagnostics.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Diagnostics.h) 

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Application.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Application.h)

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Include.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Include.h)

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/_edid.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/_edid.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Application.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Application.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/DisplayDevice.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/DisplayDevice.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/DisplayMode.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/DisplayMode.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Include.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Include.h)
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Icon.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Icon.h)
    if (${${MyModule}.OpenGL4.Enabled})
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/GlxDeviceInfo.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/GlxDeviceInfo.h)
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Window.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Linux/Window.h)
    endif()
  endif()



  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows})
    list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Application.c)
    list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Application.h)
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
    if (${${MyModule}.OpenGL4.Enabled})
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Window.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Window.h)
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Wgl/WglFactory.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Wgl/WglFactory.h)
      list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Wgl/WglFactoryWindow.c)
      list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Visuals/Implementation/Windows/Wgl/WglFactoryWindow.h)
    endif()
  endif()

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Visuals ${MyProjectName}.Imaging)
  list(APPEND ${MyModule}.PrivateLibraries ${MyProjectName}.Ring2 ${MyProjectName}.DataDefinitionLanguage ${MyProjectName}.Arms)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "Visuals")

endif()
