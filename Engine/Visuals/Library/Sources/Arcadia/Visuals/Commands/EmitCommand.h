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

#if !defined(ARCADIA_VISUALS_COMMAND_EMITCOMMAND_H_INCLUDED)
#define ARCADIA_VISUALS_COMMAND_EMITCOMMAND_H_INCLUDED

#include "Arcadia/Visuals/Commands/Command.h"

/// @code
/// class Arcadia.Visuals.EmitCommand extends Arcadia.Visuals.Command {
///   construct(timeStamp : Arcadia.Natural64, message : Arcadia.String)
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.EmitCommand", Arcadia_Visuals_EmitCommand,
                          u8"Arcadia.Visuals.Command");

struct Arcadia_Visuals_EmitCommand {
  Arcadia_Visuals_Command _parent;
  Arcadia_String* message;
};

#endif // ARCADIA_VISUALS_COMMAND_EMITCOMMAND_H_INCLUDED
