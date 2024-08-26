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

cmake_minimum_required(VERSION 3.20)

project(Arcadia)

set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../repository/)
include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)

include(FetchContent)

set(Arms1-Source-Dir "${REPOSITORY_SOURCE_DIR}/arms1/sources" CACHE STRING "path to the ARMS1 source directory")
get_filename_component(Arms1-Source-Dir "${Arms1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "fetching ${Arms1-Source-Dir}")
FetchContent_Declare(arms1 SOURCE_DIR ${Arms1-Source-Dir})
FetchContent_MakeAvailable("arms1")

set(R1-Source-Dir "${REPOSITORY_SOURCE_DIR}/r1/sources" CACHE STRING "path to the R1 source directory")
get_filename_component(R1-Source-Dir "${R1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
FetchContent_Declare(r1 SOURCE_DIR ${R1-Source-Dir})
FetchContent_MakeAvailable("r1")

add_executable(generate)
BeginProduct(generate)

# Create configuration file.
set(PROJECT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
configure_file(configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/configure.h @ONLY)

list(APPEND generate.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/file.c)
list(APPEND generate.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/file.h)
list(APPEND generate.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/stringbuffer.c)
list(APPEND generate.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/stringbuffer.h)
list(APPEND generate.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
list(APPEND generate.HeaderFiles ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

target_link_libraries(generate Arcadia.R Arcadia.Arms)

EndProduct(generate executable)
