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

#if !defined(ARCADIA_ARMS_NOTIFYDESTROY_H_INCLUDED)
#define ARCADIA_ARMS_NOTIFYDESTROY_H_INCLUDED

#include "Arcadia/ARMS/Configure.h"
#include "Arcadia/ARMS/StatusType.h"

#if defined(Arcadia_ARMS_Configuration_WithNotifyDestroy) && 1 ==  Arcadia_ARMS_Configuration_WithNotifyDestroy

typedef void (Arcadia_ARMS_NotifyDestroyCallback)(void* argument1, void* argument2);

Arcadia_ARMS_Status
Arcadia_ARMS_removeNotifyDestroyAll
  (
    void* observed
  );

Arcadia_ARMS_Status
Arcadia_ARMS_addNotifyDestroy
  (
    void* observed,
    void* argument1,
    void* argument2,
    Arcadia_ARMS_NotifyDestroyCallback* callback
  );

Arcadia_ARMS_Status
Arcadia_ARMS_removeNotifyDestroy
  (
    void* observed,
    void* argument1,
    void* argument2,
    Arcadia_ARMS_NotifyDestroyCallback* callback
  );

Arcadia_ARMS_Status
Arcadia_ARMS_removeNotifyDestroyAll
  (
    void* observed
  );

#endif // Arcadia_ARMS_Configuration_WithNotifyDestroy

#endif // ARCADIA_ARMS_NOTIFYDESTROY_H_INCLUDED
