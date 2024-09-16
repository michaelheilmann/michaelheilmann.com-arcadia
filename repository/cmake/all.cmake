# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

# Last modified: 2024-08-29

include(${CMAKE_CURRENT_LIST_DIR}/configure_warnings_and_errors.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_compiler.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_instruction_set_architecture.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_operating_system.cmake)

# Begin a library or an executable.
# The following variables are defined
# - ${target}.SourceFiles List of C/C++ source files
# - ${target}.HeaderFiles List of C/C++ header files
# - ${target}.AssetFiles  List of asset files
#   The files are all copied (without their folder) to the binary output directories.
macro(BeginProduct target)
  set(${target}.SourceFiles "")
  set(${target}.HeaderFiles "")
  set(${target}.AssetFiles "")
  DetectCompilerC(${target})
  DetectOperatingSystem(${target})
  DetectInstructionSetArchitecture(${target})
endmacro()

macro(EndProduct target type)
  ConfigureWarningsAndErrors(${target})
  target_sources(${target} PRIVATE ${${target}.SourceFiles} ${${target}.HeaderFiles})
  if (${type} STREQUAL library)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
  endif()
  if (${type} STREQUAL executable)
    target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
  endif()

endmacro()

macro(FetchProduct target directory help)
  if (NOT TARGET ${target})
      set(__${target}.SourceDir "${directory}" CACHE STRING ${help})
      get_filename_component(__${target}.SourceDir "${__${target}.SourceDir}"
                              REALPATH BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
      message(STATUS "fetching ${__${target}.SourceDir}")
      FetchContent_Declare(__${target} SOURCE_DIR ${__${target}.SourceDir})
      FetchContent_MakeAvailable(__${target})
  endif()
endmacro()
