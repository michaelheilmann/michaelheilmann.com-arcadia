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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_SIGNALS_SIGNAL_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_SIGNALS_SIGNAL_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

typedef struct Arcadia_WeakReference Arcadia_WeakReference;
typedef struct Arcadia_Slot Arcadia_Slot;
#include "Arcadia/Ring1/Implementation/Object.h"
#include "Arcadia/Ring1/Implementation/ForeignProcedure.h"

Arcadia_declareObjectType(u8"Arcadia.Signal", Arcadia_Signal,
                          u8"Arcadia.Object");

struct Arcadia_SignalDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_Signal {
  Arcadia_Object _parent;
  void *pimpl;
};

Arcadia_Signal*
Arcadia_Signal_create
  (
    Arcadia_Thread* thread
  );
  
/// @brief Connect to this signal.
/// @param thread A pointer to this thread.
/// @param self A pointer to this signal.
/// @param receiver The receiver. A weak reference to the receiver is stored.
/// @param procedure The proceduren. The procedure is invoked with the receiver as its 1st arguments, the sender as its 2nd argument and the argument as its 3rd argument.
/// Its return value is ignored.
Arcadia_Slot*
Arcadia_Signal_connect
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self,
    Arcadia_Object* receiver,
    Arcadia_ForeignProcedure* procedure
  );

// [arguments] ++ [#numberOfArguments]
// `numberOfArguments` is a Natural8 value indicating the number of arguments passed to the function.
// `arguments` is a sequence of `numberOfArguments` values.
void
Arcadia_Signal_emit
  (
    Arcadia_Thread* thread,
    Arcadia_Signal* self,
    Arcadia_Object* sender
  );

#endif // ARCADIA_RING1_IMPLEMENTATION_SIGNALS_SIGNAL_H_INCLUDED
