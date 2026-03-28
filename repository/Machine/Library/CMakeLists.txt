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

# Create library.
set(MyLibraryName ${MyProjectName}.Machine)

if (NOT TARGET ${MyLibraryName})
  BeginProduct(${MyLibraryName} library)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Configure.h @ONLY)
  OnConfigurationTemplateFile(${MyLibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Configure.h.i)
  OnConfigurationFile(${MyLibraryName} ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Configure.h)

  OnSourceFile(${MyLibraryName} Arcadia/execute.c)
  OnHeaderFile(${MyLibraryName} Arcadia/execute.h)

  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Constructor.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Constructor.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Procedure.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Procedure.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Method.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Method.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Class.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Class.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Variable.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Variable.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Instruction.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Instruction.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Code.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Code.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Include.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/ThreadState.c)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/ThreadState.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/ThreadState.private.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/ProcessState.c)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/ProcessState.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/ProcessState.private.h)
  OnSourceFile(${MyLibraryName} Arcadia/Interpreter/Code/Constants.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Interpreter/Code/Constants.h)

  OnSourceFile(${MyLibraryName} Arcadia/Include.c)
  OnHeaderFile(${MyLibraryName} Arcadia/Include.h)

  list(APPEND ${MyLibraryName}.Libraries ${MyProjectName}.MIL.Frontend ${MyProjectName}.Ring2)

  if (${${MyLibraryName}_OperatingSystem} STREQUAL ${${MyLibraryName}_OperatingSystem_Linux})
    list(APPEND ${MyLibraryName}.Libraries m)
  endif()

  EndProduct(${MyLibraryName})
  set_target_properties(${MyLibraryName} PROPERTIES FOLDER "Machine")

endif()
