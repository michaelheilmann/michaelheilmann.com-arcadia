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
set(this ${MyProjectName}.Machine)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/R/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Configure.h.i)

  OnSourceFile(${this} Arcadia/execute.c)
  OnHeaderFile(${this} Arcadia/execute.h)

  OnSourceFile(${this} Arcadia/Interpreter/Constructor.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Constructor.h)
  OnSourceFile(${this} Arcadia/Interpreter/Procedure.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Procedure.h)
  OnSourceFile(${this} Arcadia/Interpreter/Method.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Method.h)
  OnSourceFile(${this} Arcadia/Interpreter/Class.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Class.h)
  OnSourceFile(${this} Arcadia/Interpreter/Variable.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Variable.h)
  OnSourceFile(${this} Arcadia/Interpreter/Instruction.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Instruction.h)
  OnSourceFile(${this} Arcadia/Interpreter/Code.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Code.h)
  OnSourceFile(${this} Arcadia/Interpreter/Include.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Include.h)
  OnSourceFile(${this} Arcadia/Interpreter/ThreadState.c)
  OnSourceFile(${this} Arcadia/Interpreter/ThreadState.h)
  OnSourceFile(${this} Arcadia/Interpreter/ThreadState.private.h)
  OnSourceFile(${this} Arcadia/Interpreter/ProcessState.c)
  OnSourceFile(${this} Arcadia/Interpreter/ProcessState.h)
  OnSourceFile(${this} Arcadia/Interpreter/ProcessState.private.h)
  OnSourceFile(${this} Arcadia/Interpreter/Code/Constants.c)
  OnHeaderFile(${this} Arcadia/Interpreter/Code/Constants.h)

  OnSourceFile(${this} Arcadia/Include.c)
  OnHeaderFile(${this} Arcadia/Include.h)

  OnModuleDependency(${this} ${MyProjectName}.MIL.Frontend)
  OnModuleDependency(${this} ${MyProjectName}.Ring2)
  OnModuleDependency(${this} ${MyProjectName}.Print)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  EndProduct(${this})
  set_target_properties(${this} PROPERTIES FOLDER "Machine")

endif()
