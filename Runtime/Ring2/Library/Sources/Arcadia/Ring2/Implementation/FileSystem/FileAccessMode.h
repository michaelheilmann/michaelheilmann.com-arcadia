// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

#if !defined(ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_FILEACCESSMODE_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_FILEACCESSMODE_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring2/Implementation/Configure.h"
#include "Arcadia/Ring1/Include.h"

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_FileAccessMode
Arcadia_declareEnumerationType(u8"Arcadia.FileAccessMode",
                               Arcadia_FileAccessMode);

enum Arcadia_FileAccessMode {

  Arcadia_FileAccessMode_Read = 1,

  Arcadia_FileAccessMode_Write = 2,

  Arcadia_FileAccessMode_ReadWrite = Arcadia_FileAccessMode_Read | Arcadia_FileAccessMode_Write,

  Arcadia_FileAccessMode_WriteRead = Arcadia_FileAccessMode_Write | Arcadia_FileAccessMode_Read,

};

#endif // ARCADIA_RING2_IMPLEMENTATION_FILESYSTEM_FILEACCESSMODE_H_INCLUDED
