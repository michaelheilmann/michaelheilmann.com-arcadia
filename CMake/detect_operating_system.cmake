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

set(Arcadia_OperatingSystem_Unknown 0)

set(Arcadia_OperatingSystem_Cygwin 1)

set(Arcadia_OperatingSystem_IOS 2)

set(Arcadia_OperatingSystem_IOSSimulator 3)

set(Arcadia_OperatingSystem_Linux 4)

set(Arcadia_OperatingSystem_MacOS 5)

set(Arcadia_OperatingSystem_MinGW 6)

set(Arcadia_OperatingSystem_MSYS 7)

set(Arcadia_OperatingSystem_Windows 8)

set(Arcadia_OperatingSystem_Unix 9)

function(Arcadia_DetectOperatingSystem target)
  if (WIN32)
    set(${target} ${Arcadia_OperatingSystem_Windows} PARENT_SCOPE)
  elseif (CYGWIN)
    set(${target} ${Arcadia_OperatingSystem_Cygwin} PARENT_SCOPE)
  elseif (MSYS)
    set(${target} ${Arcadia_OperatingSystem_MSYS} PARENT_SCOPE)
  else()
    if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
      set(${target} ${Arcadia_OperatingSystem_Linux} PARENT_SCOPE)
    elseif ("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
      set(${target} ${Arcadia_OperatingSystem_MacOS} PARENT_SCOPE)
    else()
      set(${target} ${Arcadia_OperatingSystem_Unknown} PARENT_SCOPE)
    endif()
  endif()
endfunction()

# SUMMARY
# Define an enumeration of operating systems and detect the operating system.
#
# DETAIL
# Define an enumeration of operating systems and detect the operating system.
# The detailed steps are:
# a) Define an enumeration of operating systems.
#    The enumeration constants ${target}_OperatingSystem_(Unknown|Windows|Unix|Linux|Macos|Cygwin|Msys|Mingw|Ios|IosSimulator) are defined.
#    Each constant is a string of an unique name identifying an operating system.
# b) The constant ${target}_OperatingSystem is defined to the ${target}_OperatingSystem_* value denoting the detected operating system.
#
# PARAM target The target.
#
# REMARKS:
# - "MinGW" and "MSYS" is toolchains. The operating system is still "Windows".
# - We are not aware of a reliable procedure to detect what Apple operating system is used.
#   This configuration script detects "MacOS" even if the operating system is "iOS", "iOS Simulator", or "watchOS".
macro(DetectOperatingSystem target)
  set(${target}_OperatingSystem_Unknown ${Arcadia_OperatingSystem_Unknown})

  set(${target}_OperatingSystem_Cygwin ${Arcadia_OperatingSystem_Cygwin})

  set(${target}_OperatingSystem_IOS ${Arcadia_OperatingSystem_IOS})

  set(${target}_OperatingSystem_IOSSimulator ${Arcadia_OperatingSystem_IOSSimulator})

  set(${target}_OperatingSystem_Linux ${Arcadia_OperatingSystem_Linux})

  set(${target}_OperatingSystem_MacOS ${Arcadia_OperatingSystem_MacOS})

  set(${target}_OperatingSystem_MinGW ${Arcadia_OperatingSystem_MinGW})

  set(${target}_OperatingSystem_MSYS ${Arcadia_OperatingSystem_MSYS})

  set(${target}_OperatingSystem_Windows ${Arcadia_OperatingSystem_Windows})

  set(${target}_OperatingSystem_Unix ${Arcadia_OperatingSystem_Unix})

  if (NOT DEFINED ${target}_OperatingSystem)
    Arcadia_DetectOperatingSystem(${target}_OperatingSystem)
  endif()
  
  set(VERBOSE TRUE)
  
  if (VERBOSE)
    if (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_Unknown)
      message(STATUS " - ${target} operating system: unknown")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_Cygwin)
      message(STATUS " - ${target} operating system: Cygwin")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_IOS)
      message(STATUS " - ${target} operating system: iOS")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_IOSSimulator)
      message(STATUS " - ${target} operating system: iOS Simulator")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_Linux)
      message(STATUS " - ${target} operating system: Linux")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_MacOS)
      message(STATUS " - ${target} operating system: MacOS")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_MinGW)
      message(STATUS " - ${target} operating system: MinGW")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_MSYS)
      message(STATUS " - ${target} operating system: MSYS")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_Windows)
      message(STATUS " - ${target} operating system: Windows")
    elseif (${target}_OperatingSystem STREQUAL ${target}_OperatingSystem_Unix)
      message(STATUS " - ${target} operating system: Unix")
    else()
      message(FATAL_ERROR "<internal error>") 
    endif()
  endif()
endmacro()
