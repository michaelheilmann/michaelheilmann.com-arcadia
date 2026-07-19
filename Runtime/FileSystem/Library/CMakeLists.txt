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
set(this ${MyProjectName}.FileSystem)

if (NOT TARGET ${this})
  BeginProduct(${this} library)

  OnConfigurationFile(${this} ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/FileSystem/Configure.h ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/FileSystem/Configure.h.i)

  OnSourceFile(${this} Arcadia/FileSystem/Include.c)
  OnHeaderFile(${this} Arcadia/FileSystem/Include.h)
  OnSourceFile(${this} Arcadia/FileSystem/DirectoryIterator.c)
  OnHeaderFile(${this} Arcadia/FileSystem/DirectoryIterator.h)
  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    OnSourceFile(${this} Arcadia/FileSystem/Linux/DirectoryIteratorLinux.c)
    OnHeaderFile(${this} Arcadia/FileSystem/Linux/DirectoryIteratorLinux.h)
    OnSourceFile(${this} Arcadia/FileSystem/Linux/getHomeFolder.c)
    OnHeaderFile(${this} Arcadia/FileSystem/Linux/getHomeFolder.h)
  endif()
  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Windows})
    OnSourceFile(${this} Arcadia/FileSystem/Windows/DirectoryIteratorWindows.c)
    OnHeaderFile(${this} Arcadia/FileSystem/Windows/DirectoryIteratorWindows.h)
    OnSourceFile(${this} Arcadia/FileSystem/Windows/getLocalFolder.c)
    OnHeaderFile(${this} Arcadia/FileSystem/Windows/getLocalFolder.h)
    OnSourceFile(${this} Arcadia/FileSystem/Windows/getRoamingFolder.c)
    OnHeaderFile(${this} Arcadia/FileSystem/Windows/getRoamingFolder.h)
  endif()
  OnSourceFile(${this} Arcadia/FileSystem/ExistingFilePolicy.c)
  OnHeaderFile(${this} Arcadia/FileSystem/ExistingFilePolicy.h)
  OnSourceFile(${this} Arcadia/FileSystem/FileAccessMode.c)
  OnHeaderFile(${this} Arcadia/FileSystem/FileAccessMode.h)
  OnSourceFile(${this} Arcadia/FileSystem/FileHandle.c)
  OnHeaderFile(${this} Arcadia/FileSystem/FileHandle.h)
  OnSourceFile(${this} Arcadia/FileSystem/FileHandleExtensions.c)
  OnHeaderFile(${this} Arcadia/FileSystem/FileHandleExtensions.h)
  OnSourceFile(${this} Arcadia/FileSystem/FilePath.c)
  OnHeaderFile(${this} Arcadia/FileSystem/FilePath.h)
  OnSourceFile(${this} Arcadia/FileSystem/FileSystem.c)
  OnHeaderFile(${this} Arcadia/FileSystem/FileSystem.h)
  OnSourceFile(${this} Arcadia/FileSystem/FileType.c)
  OnHeaderFile(${this} Arcadia/FileSystem/FileType.h)
  OnSourceFile(${this} Arcadia/FileSystem/NonExistingFilePolicy.c)
  OnHeaderFile(${this} Arcadia/FileSystem/NonExistingFilePolicy.h)
  OnSourceFile(${this} Arcadia/FileSystem/Implementation/DefaultFileSystem.c)
  OnHeaderFile(${this} Arcadia/FileSystem/Implementation/DefaultFileSystem.h)
  OnSourceFile(${this} Arcadia/FileSystem/Implementation/DefaultFileHandle.c)
  OnHeaderFile(${this} Arcadia/FileSystem/Implementation/DefaultFileHandle.h)
  OnSourceFile(${this} Arcadia/FileSystem/Implementation/getFileType.c)
  OnHeaderFile(${this} Arcadia/FileSystem/Implementation/getFileType.h)
  OnSourceFile(${this} Arcadia/FileSystem/Implementation/deleteRegularFile.c)
  OnHeaderFile(${this} Arcadia/FileSystem/Implementation/deleteRegularFile.h)
  OnSourceFile(${this} Arcadia/FileSystem/Implementation/deleteDirectoryFile.c)
  OnHeaderFile(${this} Arcadia/FileSystem/Implementation/deleteDirectoryFile.h)

  OnModuleDependency(${this} ${MyProjectName}.Collections)
  OnModuleDependency(${this} ${MyProjectName}.Ring2)

  if (${${this}_OperatingSystem} STREQUAL ${${this}_OperatingSystem_Linux})
    list(APPEND ${this}.Libraries m)
  endif()

  set(${this}.Install TRUE)

  EndProduct(${this})

  set_target_properties(${this} PROPERTIES FOLDER "Runtime/FileSystem")

endif()
