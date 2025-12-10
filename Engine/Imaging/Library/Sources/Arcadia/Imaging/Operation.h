// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_IMAGING_OPERATION_H_INCLUDED)
#define ARCADIA_IMAGING_OPERATION_H_INCLUDED

#include "Arcadia/Imaging/PixelBuffer.h"

Arcadia_declareObjectType(u8"Arcadia.Imaging.Operation", Arcadia_Imaging_Operation,
                          u8"Arcadia.Object");

struct Arcadia_Imaging_OperationDispatch {
  Arcadia_ObjectDispatch parent;

  void (*apply)(Arcadia_Thread*, Arcadia_Imaging_Operation*, Arcadia_Imaging_PixelBuffer*);
};

struct Arcadia_Imaging_Operation {
  Arcadia_Object parent;
};

void
Arcadia_Imaging_Operation_apply
  (
    Arcadia_Thread* thread,
    Arcadia_Imaging_Operation* self,
    Arcadia_Imaging_PixelBuffer* target
  );

#endif // ARCADIA_IMAGING_OPERATION_H_INCLUDED
