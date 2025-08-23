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

#if !defined(ARCADIA_ENGINE_SYSTEM_H_INCLUDED)
#define ARCADIA_ENGINE_SYSTEM_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

/// @brief
/// The base of all systems.
/// 
/// @details
/// A system is either an "audials" or a "visuals" system.
/// The engine maintains pointers to the active system of the respective type.
/// 
/// The attempt to create a system of a type with an active of that type is an error.
/// Systems check that by inspecting the pointers to active systems maintained by the engine.
/// 
/// One can first create a system of a type, shut it down, and create a system of another type.
/// For example, one can create a OpenGL visuals system, shut it down, and create an Vulkan visuals system.
/// 
/// @details
/// @code
/// class Arcadia.Engine.System {
/// 
///   construct
///     (
///     )
///   
///   method
///   update
///     (
///     )
///     : Arcadia.Void
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Engine.System", Arcadia_Engine_System,
                          u8"Arcadia.Object")

struct Arcadia_Engine_System {
  Arcadia_Object _parent;

  void (*update)(Arcadia_Thread* thread, Arcadia_Engine_System* self);
};

/// @brief Update this system.
/// @param thread A pointer to this thread.
/// @param self A pointer to this system.
void
Arcadia_Engine_System_update
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_System* self
  );

#endif // ARCADIA_ENGINE_SYSTEM_H_INCLUDED
