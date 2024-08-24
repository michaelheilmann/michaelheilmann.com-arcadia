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

cmake_minimum_required(VERSION 3.29)

set(MyProjectName "Arcadia")

include(FetchContent)

FetchContent_Declare(
  "arms1"
  URL ${CMAKE_CURRENT_SOURCE_DIR}/../../arms1/arms1.zip
  )
FetchContent_MakeAvailable("arms1")
                                                                          

project(${MyProjectName} LANGUAGES C)

# Create executable.
set(MySources "")

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/boolean.h)

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/integer16.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/integer32.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/integer64.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/integer8.h)

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/jumptarget.c)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/jumptarget.h)

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/r1.c)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/r1.h)

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/maximum.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/minimum.h)

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/natural16.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/natural32.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/natural64.h)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/natural8.h)

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/size.h)

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/status.c)
list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/status.h)

list(APPEND MySources ${CMAKE_CURRENT_SOURCE_DIR}/arcadia/void.h)

add_library(${MyProjectName}.R ${MySources})
target_include_directories(${MyProjectName}.R PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${MyProjectName}.R Arcadia.Arms)
