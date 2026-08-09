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

set(this ${MyProjectName}.MILC.Tests.Test1)

# Create test executable.
BeginProduct(${this} test)

# Configuration files.
OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia.Compiler.Tests.Test1/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia.Compiler.Tests.Test1/Configure.h.i)

# Source and header files.
OnSourceFile(${this} Arcadia.Compiler.Tests.Test1/Main.c)

# Libraries.
OnModuleDependency(${this} ${MyProjectName}.MILC PRIVATE)
OnModuleDependency(${this} ${MyProjectName}.DDL PRIVATE)

EndProduct(${this})
# Copy assets.
CopyProductAssets(${this} "MILC" ${CMAKE_CURRENT_BINARY_DIR}/Assets)

# Adjust working directory.
set(${this}.WorkingDirectory $<TARGET_FILE_DIR:${this}>)
set_target_properties(${this} PROPERTIES FOLDER "MILC")
