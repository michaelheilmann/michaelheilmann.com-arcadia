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

# "Unknown" Byte order.
set(Arcadia_ByteOrder_Unknown 0)

# "Big Endian" Byte order.
set(Arcadia_ByteOrder_BigEndian 1)

# "Little Endian" Byte order.
set(Arcadia_ByteOrder_LittleEndian 2)

function(Arcadia_DetectByteOrder result)
  if (CMAKE_C_BYTE_ORDER STREQUAL "BIG_ENDIAN")
    set(${result} ${Arcadia_ByteOrder_BigEndian} PARENT_SCOPE) 
  elseif (CMAKE_C_BYTE_ORDER STREQUAL "LITTLE_ENDIAN")
    set(${result} ${Arcadia_ByteOrder_LittleEndian} PARENT_SCOPE)   
  else()
    set(${result} ${Arcadia_ByteOrder_Unknown} PARENT_SCOPE) 
  endif()
endfunction()

# SUMMARY
# Define an enumeration of Byte orders and detect the Byte order.
#
# DETAIL
# Define an enumeration of Byte orders and detect the Byte order.
# The detailed steps are:
# a) The numeration constants ${target}_ByteOrder_(LittleEndian|BigEndian|Unknown) are defined.
#    Each constant identifies a Byte order.
# b) The constant ${target}_ByteOrder is set to the {target}_ByteOrder_* values denoting the detected Byte order.
# PARAM target The target.
macro(DetectByteOrder target)
  set(${target}_ByteOrder_Unknown ${Arcadia_ByteOrder_Unknown})
  set(${target}_ByteOrder_BigEndian ${Arcadia_ByteOrder_BigEndian})
  set(${target}_ByteOrder_LittleEndian ${Arcadia_ByteOrder_LittleEndian})
  
  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}_ByteOrder)
    Arcadia_DetectByteOrder(${target}_ByteOrder)
  endif()
  
  set(VERBOSE TRUE)
  
  if (VERBOSE) 
    if (${target}_ByteOrder STREQUAL ${target}_ByteOrder_Unknown)
      message( STATUS " - ${target} Byte order: unknown")
    elseif (${target}_ByteOrder STREQUAL ${target}_ByteOrder_BigEndian)
      message( STATUS " - ${target} Byte order: big endian")
    elseif (${target}_ByteOrder STREQUAL ${target}_ByteOrder_LittleEndian)
      message( STATUS " - ${target} Byte order: little endian")
    else()
      message(FATAL_ERROR "<internal error>") 
    endif()
  endif()

endmacro()
