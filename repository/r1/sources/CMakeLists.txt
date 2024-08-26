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

cmake_minimum_required(VERSION 3.29)

set(MyProjectName "Arcadia")

set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)

include(FetchContent)

set(Arms1-Source-Dir "${REPOSITORY_SOURCE_DIR}/arms1/sources" CACHE STRING "path to the ARMS1 source directory")
get_filename_component(Arms1-Source-Dir "${Arms1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "fetching ${Arms1-Source-Dir}")
FetchContent_Declare(arms1 SOURCE_DIR ${Arms1-Source-Dir})
FetchContent_MakeAvailable("arms1")
                                                                          
project(${MyProjectName} LANGUAGES C)

# Create library.
add_library(${MyProjectName}.R)
BeginProduct(${MyProjectName}.R)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/r/configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/r/configure.h @ONLY)

list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_BINARY_DIR}/r/configure.h)

list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/boolean.h)

list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/bytebuffer.c)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/bytebuffer.h)

list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/integer16.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/integer32.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/integer64.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/integer8.h)

list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/jumptarget.c)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/jumptarget.h)

list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/r.c)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r.h)

list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/clamp.h)
list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/countleadingzeroes.c)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/countleadingzeroes.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/maximum.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/minimum.h)

list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/natural16.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/natural32.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/natural64.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/natural8.h)

list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/object.c)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/object.h)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/objectreference.h)

list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/size.h)

list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/status.c)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/status.h)

list(APPEND ${MyProjectName}.R.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/value.c)
list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/value.h)

list(APPEND ${MyProjectName}.R.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/r/void.h)

target_link_libraries(${MyProjectName}.R Arcadia.Arms)

EndProduct(${MyProjectName}.R library)
