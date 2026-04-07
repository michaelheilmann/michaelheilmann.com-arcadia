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

set(MyModule ${MyProjectName}.SampleBufferIO)

if (NOT TARGET ${MyModule})
  BeginProduct(${MyModule} library)

  # libFLAC.
  if (${${MyModule}_OperatingSystem} STREQUAL ${${MyModule}_OperatingSystem_Windows})
    # Windows.   
    if (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X64})
      set(${MyModule}.libOGG.Libraries ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/ogg/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,ogg.lib,ogg.lib>)
      set(${MyModule}.libOGG.HeaderFilesDirectory ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/ogg/include)
    elseif (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X86})
      set(${MyModule}.libOGG.Libraries ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/ogg/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,ogg.lib,ogg.lib>)
      set(${MyModule}.libOGG.HeaderFilesDirectory ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/ogg/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.libOGG.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.libOGG.HeaderFilesDirectory})
    
    if (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X64})
      set(${MyModule}.libFLAC.Libraries ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/flac/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,FLAC.lib,FLAC.lib>)
      set(${MyModule}.libFLAC.HeaderFilesDirectory ${MyDependenciesDirectory}/x64/$<LOWER_CASE:$<CONFIG>>/flac/include)
    elseif (${${MyModule}_InstructionSetArchitecture} STREQUAL ${${MyModule}_InstructionSetArchitecture_X86})
      set(${MyModule}.libFLAC.Libraries ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/flac/lib/$<IF:$<STREQUAL:$<LOWER_CASE:$<CONFIG>>,debug>,FLAC.lib,FLAC.lib>)
      set(${MyModule}.libFLAC.HeaderFilesDirectory ${MyDependenciesDirectory}/x86/$<LOWER_CASE:$<CONFIG>>/flac/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.libFLAC.Libraries})
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.libFLAC.HeaderFilesDirectory})
  else()
    # Linux.
    find_package(FLAC REQUIRED)
    if (NOT TARGET FLAC::FLAC)
      message(FATAL_ERROR "libFLAC not found")
    endif()
    list(APPEND ${MyModule}.PrivateLibraries FLAC::FLAC)
  endif()

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/SampleBufferIO/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/SampleBufferIO/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/SampleBufferIO/Configure.h.i)
  OnConfigurationFile(${MyModule} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/SampleBufferIO/Configure.h)

  OnSourceFile(${MyModule} Arcadia/SampleBufferIO/Include.c)
  OnHeaderFile(${MyModule} Arcadia/SampleBufferIO/Include.h)

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Media ${MyProjectName}.ADL)

  EndProduct(${MyModule})

  set_target_properties(${MyModule} PROPERTIES FOLDER "SampleBufferIO")

endif()
