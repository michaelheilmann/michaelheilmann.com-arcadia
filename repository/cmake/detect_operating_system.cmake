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

# Last modified: 2024-08-27

# SUMMARY
# Define an enumeration of operating systems and detect the operating system.
#
# DETAIL
# Define an enumeration of operating systems and detect the operating system.
# The detailed steps are:
# a) Define an enumeration of operating systems.
#    The enumeration constants ${target}.OperatingSystem.(Unknown|Windows|Unix|Linux|Macos|Cygwin|Msys|Mingw|Ios|IosSimulator) are defined.
#    Each constant is a string of an unique name identifying an operating system.
# b) The constant ${target}.OperatingSystem is defined to the ${target}.OperatingSystem.* value denoting the detected operating system.
#
# PARAM target The target.
#
# REMARKS:
# - "MinGW" and "MSYS" is toolchains. The operating system is still "Windows".
# - We are not aware of a reliable procedure to detect what Apple operating system is used.
#   This configuration script detects "MacOS" even if the operating system is "iOS", "iOS Simulator", or "watchOS".
macro(DetectOperatingSystem target)

  set(${target}.OperatingSystem.Unknown 0)
  set(${${target}.OperatingSystem.Unknown}.Help "<unknown operating system>")

  set(${target}.OperatingSystem.Cygwin 1)
  set(${${target}.OperatingSystem.Cygwin}.Help "CYGWIN")
  
  set(${target}.OperatingSystem.Ios 2)
  set(${${target}.OperatingSystem.Ios}.Help "IOS")

  set(${target}.OperatingSystem.IosSimulator 3)
  set(${${target}.OperatingSystem.IosSimulator}.Help "IOS SIMULATOR")

  set(${target}.OperatingSystem.Linux 4)
  set(${${target}.OperatingSystem.Linux}.Help "LINUX")

  set(${target}.OperatingSystem.Macos 5)
  set(${${target}.OperatingSystem.Macos}.Help "MACOS")
  
  set(${target}.OperatingSystem.Mingw 6)
  set(${${target}.OperatingSystem.Mingw}.Help "MINGW")

  set(${target}.OperatingSystem.Msys 7)
  set(${${target}.OperatingSystem.Msys}.Help "MSYS")

  set(${target}.OperatingSystem.Windows 8)
  set(${${target}.OperatingSystem.Windows}.Help "WINDOWS")

  set(${target}.OperatingSystem.Unix 9)
  set(${${target}.OperatingSystem.Unix}.Help "UNIX")

  if (NOT DEFINED ${target}.OperatingSystem)  
    set(${target}.OperatingSystem ${${target}.OperatingSystem.Unknown})
    if (WIN32)
      set(${target}.OperatingSystem ${${target}.OperatingSystem.Windows})
      set(${target}.Configuration.OperatingSystem ${${target}.OperatingSystem.Windows})
    elseif (CYGWIN)
      set(${target}.OperatingSystem ${${target}.OperatingSystem.Cygwin})
      set(${target}.Configuration.OperatingSystem ${${target}.OperatingSystem.Cygwin})      
    elseif (MSYS)
      set(${target}.OperatingSystem ${${target}.OperatingSystem.Msys})
      set(${target}.Configuration.OperatingSystem ${${target}.OperatingSystem.Msys})
    endif()

    if (${${target}.OperatingSystem} STREQUAL ${${target}.OperatingSystem.Unknown})
      if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")
        set(${target}.OperatingSystem ${${target}.OperatingSystem.Linux})
        set(${target}.Configuration.OperatingSystem ${${target}.OperatingSystem.Linux})
      elseif ("${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
        set(${target}.OperatingSystem ${${target}.OperatingSystem.Macos})
        set(${target}.Configuration.OperatingSystem ${${target}.OperatingSystem.Macos})
      endif()
    endif()
  endif()
  #message(STATUS " - ${target} operating system: ${${${target}.OperatingSystem}.Help}")
endmacro()
