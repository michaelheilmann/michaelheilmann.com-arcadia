# Copyright (c) 2024 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

project(generate)

include(FetchContent)

set(Arms1-Source-Dir "${CMAKE_CURRENT_SOURCE_DIR}/../repository/arms1/sources" CACHE STRING "path to the ARMS1 source directory")
get_filename_component(Arms1-Source-Dir "${Arms1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "fetching ${Arms1-Source-Dir}")
FetchContent_Declare(arms1 SOURCE_DIR ${Arms1-Source-Dir})
FetchContent_MakeAvailable("arms1")

set(R1-Source-Dir "${CMAKE_CURRENT_SOURCE_DIR}/../repository/r1/sources" CACHE STRING "path to the R1 source directory")
get_filename_component(R1-Source-Dir "${R1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
FetchContent_Declare(r1 SOURCE_DIR ${R1-Source-Dir})
FetchContent_MakeAvailable("r1") 

# Create configuration file.
set(PROJECT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
configure_file(configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/configure.h @ONLY)

# Create executable.
set(MySources "")
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/file.c)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/file.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/stringbuffer.c)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/stringbuffer.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
list(APPEND MySources ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

add_executable(generate ${MySources})
target_sources(generate PRIVATE ${MySources})
target_include_directories(generate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(generate PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(generate Arcadia.R Arcadia.Arms)
