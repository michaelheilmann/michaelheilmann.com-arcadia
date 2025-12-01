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

# SUMMARY
# Define an enumeration of instruction set architectures and detect the instruction set architecture.
#
# DETAIL
# Define an enumeration of instruction set architectures and detect the instruction set architecture.
# The detailed steps are:
# a) Define an enumeration of instruction set architectures.
#    The enumeration constants ${target}.InstructionSetArchitecture.(Unknown|X86|X64) are defined.
#    Each constant is a string of an unique name identifying an instruction set architecture.
# b) The constant ${target}.InstructionSetArchitecture is defined to the ${target}.InstructionSetArchitecture.* value denoting the detected instruction set architecture.
#
# PARAM target The target.
macro(DetectInstructionSetArchitecture target)
  # Unknown instruction set architecture.
  set(${target}.InstructionSetArchitecture.Unknown 0)
  set(${${target}.InstructionSetArchitecture.Unknown}.Help "<unknown instruction set architecture>")

  # x86.
  set(${target}.InstructionSetArchitecture.X86 1)
  set(${${target}.InstructionSetArchitecture.X86}.Help "x86")

  # x64.
  set(${target}.InstructionSetArchitecture.X64 2)
  set(${${target}.InstructionSetArchitecture.X64}.Help "x64")

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target_name}.InstructionSetArchitecture)
    set(${target}.InstructionSetArchitecture ${${target}.InstructionSetArchitecture.Unknown})
    set(${target}.Configuration.InstructionSetArchitecture ${${target}.InstructionSetArchitecture.Unknown})
  endif()
  if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(${target}.InstructionSetArchitecture ${${target}.InstructionSetArchitecture.X64})
    set(${target}.Configuration.InstructionSetArchitecture ${${target}.InstructionSetArchitecture.X64})
  elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(${target}.InstructionSetArchitecture ${${target}.InstructionSetArchitecture.X86})
    set(${target}.Configuration.InstructionSetArchitecture ${${target}.InstructionSetArchitecture.X86})
  endif()
  #message( STATUS " - ${target} instruction set architecture: ${${${target}.InstructionSetArchitecture}.Help}")
endmacro()
