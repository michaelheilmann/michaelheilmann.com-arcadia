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
# Define an enumeration of Byte orders and detect the Byte order.
#
# DETAIL
# Define an enumeration of Byte orders and detect the Byte order.
# The detailed steps are:
# a) The numeration constants ${target}.ByteOrder.(LittleEndian|BigEndian|Unknown) are defined.
#    Each constant identifies a Byte order.
# b) The constant ${target}.ByteOrder is set to the {target}.ByteOrder.* values denoting the detected Byte order.
# PARAM target The target.
macro(DetectByteOrder target)
   # An unknown Byte order.
  set(${target}.ByteOrder.Unknown 0)
  set(${${target}.ByteOrder.Unknown}.Help "<unknown Byte order>")

  # Big endian Byte order.
  set(${target}.ByteOrder.BigEndian 1)
  set(${${target}.ByteOrder.BigEndian}.Help "big endian")

  # Little endian Byte order.
  set(${target}.ByteOrder.LittleEndian 2)
  set(${${target}.ByteOrder.LittleEndian}.Help "little endian")

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}.ByteOrder)
    set(${target}.ByteOrder ${${target}.ByteOrder.Unknown})
    if (CMAKE_C_BYTE_ORDER STREQUAL "BIG_ENDIAN")
      set(${target}.ByteOrder ${${target}.ByteOrder.BigEndian})
    elseif (CMAKE_C_BYTE_ORDER STREQUAL "LITTLE_ENDIAN")
      set(${target}.ByteOrder ${${target}.ByteOrder.LittleEndian})
    endif()
  endif()
  message( STATUS " - ${target} Byte order: ${${${target}.ByteOrder}.Help}")
endmacro()
