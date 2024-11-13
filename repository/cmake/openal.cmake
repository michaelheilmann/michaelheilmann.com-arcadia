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

# Last modified: 2024-09-29

# Fetch content for OpenAl.
# Define variable "External.OpenAl.Available=1" and target "External.OpenAl.Target" on success.
# Define variable "External.OpenAl.Available=0" on failure.
macro(FetchOpenAl)
  if (NOT External.OpenAl.Available)
    set(External.OpenAl.Available 0)
    set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
    set(ALSOFT_UTILS OFF)
    set(ALSOFT_NO_CONFIG_UTIL OFF)
    set(ALSOFT_EXAMPLES OFF)
    set(ALSOFT_INSTALL OFF)
    set(ALSOFT_INSTALL_CONFIG OFF)
    set(ALSOFT_INSTALL_HRTF_DATA OFF)
    set(ALSOFT_INSTALL_AMBDEC_PRESETS OFF)
    set(ALSOFT_INSTALL_EXAMPLES OFF)
    set(ALSOFT_INSTALL_UTILS OFF)
    set(LIBTYPE STATIC)
    #set(LIBTYPE SHARED)
    FetchContent_Declare(OpenAl
                         GIT_REPOSITORY "https://github.com/kcat/openal-soft.git"
                         GIT_TAG 19c89d4fcfb6d336ad5d5ce3b374d197d7399613
                         SOURCE_DIR ${PROJECT_BINARY_DIR}/download-openal
                         BINARY_DIR ${PROJECT_BINARY_DIR}/build-openal)
    FetchContent_MakeAvailable(OpenAl)
    FetchContent_GetProperties(OpenAl POPULATED External.OpenAl.Available)
    if (${External.OpenAl.Available})
      set_target_properties("alcommon" PROPERTIES FOLDER "External.OpenAL")
      set_target_properties("al-excommon" PROPERTIES FOLDER "External.OpenAL")
      set_target_properties("build_version" PROPERTIES FOLDER "External.OpenAL")
      set_target_properties("OpenAL" PROPERTIES FOLDER "External.OpenAL")
      if (NOT TARGET External.OpenAl.Target)
        add_library(External.OpenAl.Target ALIAS OpenAL)
      endif()
    endif()
  endif()
endmacro()
