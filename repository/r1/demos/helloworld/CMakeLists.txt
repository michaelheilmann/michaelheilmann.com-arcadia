# Copyright (c) 2024 Michael Heilmann. All rights reserved.
cmake_minimum_required(VERSION 3.20)

set(MyProjectName "Arcadia")

include(FetchContent)

set(Arms1-Source-Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../arms1/sources" CACHE STRING "path to the ARMS1 source directory")
get_filename_component(Arms1-Source-Dir "${Arms1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "fetching ${Arms1-Source-Dir}")
FetchContent_Declare(arms1 SOURCE_DIR ${Arms1-Source-Dir})
FetchContent_MakeAvailable("arms1")

set(R1-Source-Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../r1/sources" CACHE STRING "path to the R1 source directory")
get_filename_component(R1-Source-Dir "${R1-Source-Dir}"
                       REALPATH BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
FetchContent_Declare(r1 SOURCE_DIR ${R1-Source-Dir})
FetchContent_MakeAvailable("r1") 

project(${MyProjectName} LANGUAGES C)

# Create configuration file.
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/configure.h @ONLY)

# Create executable.
set(MySources "")

list(APPEND MySources ${CMAKE_CURRENT_BINARY_DIR}/configure.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/main.c)
                                                                            
add_executable(${MyProjectName}.R.HelloWorldDemo ${MySources})
target_include_directories(${MyProjectName}.R.HelloWorldDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${MyProjectName}.R.HelloWorldDemo PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${MyProjectName}.R.HelloWorldDemo Arcadia.R Arcadia.Arms)
