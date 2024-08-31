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

# Last modified: 2024-08-31

cmake_minimum_required(VERSION 3.29)

set(MyProjectName "Arcadia")

set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../repository)
get_filename_component(REPOSITORY_SOURCE_DIR "${REPOSITORY_SOURCE_DIR}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "repository source dir : ${REPOSITORY_SOURCE_DIR}")
include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
                                                                          
project(${MyProjectName} LANGUAGES C)

include(FetchContent)

set(Arms1-Source-Dir "${REPOSITORY_SOURCE_DIR}/Arms1/Sources" CACHE STRING "path to the ARMS1 source directory")
get_filename_component(Arms1-Source-Dir "${Arms1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "fetching ${Arms1-Source-Dir}")
FetchContent_Declare(Arms1 SOURCE_DIR ${Arms1-Source-Dir})
FetchContent_MakeAvailable(Arms1)

set(R1-Source-Dir "${REPOSITORY_SOURCE_DIR}/R1/Sources" CACHE STRING "path to the R1 source directory")
get_filename_component(R1-Source-Dir "${R1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
FetchContent_Declare(R1 SOURCE_DIR ${R1-Source-Dir})
FetchContent_MakeAvailable(R1) 

set(Tools.Concatenate-Source-Dir "${REPOSITORY_SOURCE_DIR}/Tools.Concatenate/Tool/Sources" CACHE STRING "path to the Tools.Concatenate source directory")
get_filename_component(Tools.Concatenate-Source-Dir "${Tools.Concatenate-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
FetchContent_Declare(Tools.Concatenate SOURCE_DIR ${Tools.Concatenate-Source-Dir})
FetchContent_MakeAvailable(Tools.Concatenate) 

# Build "index.html".
set(DOCUMENTATION_SOURCE_FILES "")
list(APPEND DOCUMENTATION_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/index.i)

set(DOCUMENT_TARGET_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../index.html")
add_custom_command(OUTPUT ${DOCUMENT_TARGET_FILE}
                   COMMAND $<TARGET_FILE:Tools.Concatenate> ${DOCUMENTATION_SOURCE_FILES} ${DOCUMENT_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "concatenating files"
                   DEPENDS Tools.Concatenate ${DOCUMENTATION_SOURCE_FILES})

add_custom_target(BuildIndexDocument ALL DEPENDS ${DOCUMENT_TARGET_FILE})

# Build "error.html".
set(DOCUMENTATION_SOURCE_FILES "")
list(APPEND DOCUMENTATION_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/error.i)

set(DOCUMENT_TARGET_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../error.html")
add_custom_command(OUTPUT ${DOCUMENT_TARGET_FILE}
                   COMMAND $<TARGET_FILE:Tools.Concatenate> ${DOCUMENTATION_SOURCE_FILES} ${DOCUMENT_TARGET_FILE}
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                   COMMENT "concatenating files"
                   DEPENDS Tools.Concatenate ${DOCUMENTATION_SOURCE_FILES})

add_custom_target(BuildErrorDocument ALL DEPENDS ${DOCUMENT_TARGET_FILE})
