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

project(maid)

set(SOURCES "")
list(APPEND SOURCES "maid-main.c")
list(APPEND SOURCES "maid-string.c" "maid-string.h")
list(APPEND SOURCES "maid-global-mutex.c" "maid-global-mutex.h")
list(APPEND SOURCES "maid-atexit.c" "maid-atexit.h")
list(APPEND SOURCES "maid-reference-counter.c" "maid-reference-counter.h")

add_executable(maid-win32-gdi WIN32 ${SOURCES})
