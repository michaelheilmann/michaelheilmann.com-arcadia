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
macro(BeginProduct target)
  set(${target}.SourceFiles "")
  set(${target}.HeaderFiles "")
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
