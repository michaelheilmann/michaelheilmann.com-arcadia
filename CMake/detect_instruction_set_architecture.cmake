# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

# An unknown instruction set architecture.
set(Arcadia_InstructionSetArchitecture_Unknown 0)

# The x86 instruction set architecture.
set(Arcadia_InstructionSetArchitecture_X86 1)

# The x64 instruction set architecture.
set(Arcadia_InstructionSetArchitecture_X64 2)

# SUMMARY
# Detect the instruction set architecture.
#
# DETAIL
# Detect the instruction set architecture.
# The variable named by ${result} in the parent scope is assigned one of ${Arcadia_InstructionSetArchitecture_X86}, ${Arcadia_InstructionSetArchitecture_X64}, or ${Arcadia_InstructionSetArchitecture_Unknown}. 
#
# PARAM result The name of the variable to assign in the parent scope the instruction set architecture to.
function(Arcadia_DetectInstructionSetArchitecture result)
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(${result} ${Arcadia_InstructionSetArchitecture_X64} PARENT_SCOPE)
  elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(${result} ${Arcadia_InstructionSetArchitecture_X86} PARENT_SCOPE)
  else()
    set(${result} ${Arcadia_InstructionSetArchitecture_Unknown} PARENT_SCOPE)
  endif()
endfunction()

# SUMMARY
# Define an enumeration of instruction set architectures and detect the instruction set architecture.
#
# DETAIL
# Define an enumeration of instruction set architectures and detect the instruction set architecture.
# The detailed steps are:
# a) Define an enumeration of instruction set architectures.
#    The enumeration constants ${target}_InstructionSetArchitecture_(Unknown|X86|X64) are defined.
#    Each constant is a string of an unique name identifying an instruction set architecture.
# b) The constant ${target}_InstructionSetArchitecture is defined to the ${target}_InstructionSetArchitecture_* value denoting the detected instruction set architecture.
#
# PARAM target The target.
macro(DetectInstructionSetArchitecture target)
  set(${target}_InstructionSetArchitecture_Unknown ${Arcadia_InstructionSetArchitecture_Unknown})

  set(${target}_InstructionSetArchitecture_X86 ${Arcadia_InstructionSetArchitecture_X86})

  set(${target}_InstructionSetArchitecture_X64 ${Arcadia_InstructionSetArchitecture_X64})

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}_InstructionSetArchitecture)
    Arcadia_DetectInstructionSetArchitecture(${target}_InstructionSetArchitecture)
  endif()
  set(VERBOSE FALSE)
  if (VERBOSE)
    if (${target}_InstructionSetArchitecture STREQUAL ${target}_InstructionSetArchitecture_Unknown)
      message( STATUS " - ${target} instruction set architecture: unknown")
    elseif (${target}_InstructionSetArchitecture STREQUAL ${target}_InstructionSetArchitecture_X64)
      message( STATUS " - ${target} instruction set architecture: X64")
    elseif (${target}_InstructionSetArchitecture STREQUAL ${target}_InstructionSetArchitecture_X86)
      message( STATUS " - ${target} instruction set architecture: X64")
    else()
      message(FATAL_ERROR "<internal error>")
    endif()
  endif()
endmacro()
