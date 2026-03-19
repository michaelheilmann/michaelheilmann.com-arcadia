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

#if !defined(ARCADIA_VPL_SYMBOLS_VARIABLESCALAR_H_INCLUDED)
#define ARCADIA_VPL_SYMBOLS_VARIABLESCALAR_H_INCLUDED

#if !defined(ARCADIA_VPL_PRIVATE) || 1 != ARCADIA_VPL_PRIVATE
  #error("do not include directly, include `Arcadia/VPL/Include.h` instead")
#endif
#include "Arcadia/VPL/Symbols/Symbol.h"
typedef struct Arcadia_VPL_Symbols_Program Arcadia_VPL_Symbols_Program;

// The variable scalar is input to the vertex processing stage.
// @remarks For GLSL, it will be declared as "in" in the vertex shader.
#define Arcadia_VPL_Symbols_VariableScalarFlags_VertexProcessing (1 << 1)

// The variable scalar is input to the fragment processing stage (and output of the vertex processing stage).
// @remarks For GLSL, it will be declared as "out" in the vertex shader and as "in" in the fragment shader. The location is ignored.
#define Arcadia_VPL_Symbols_VariableScalarFlags_FragmentProcessing (1 << 2)

// The variable scalar is input to the pixel processing stage (and output of the fragment processing stage).
// @remarks For GLSL, it will be declared as "out" in the fragment shader. The location is ignored.
#define Arcadia_VPL_Symbols_VariableScalarFlags_PixelProcessing (1 << 3)

// There must exist exactly one variable with this flag and it must be of type vec4.
// This variable conveys information to the remnants of the fixed function pipeline.
// @remarks This type of variable maps to gl_Position and gl_FragCoord in GLSL.
// TODO: We must make sure that this variable is assigned, wich requires flow analyses.
#define Arcadia_VPL_Symbols_VariableScalarFlags_PositionSemantics (1 << 4)

/// @brief Representation of an pixel/fragment/vertex variable scalar.
/// ```
/// 'variable' 'scalar' <name> ':' <type> ('pixel'|'fragment'|'vertex')
/// ```
Arcadia_declareObjectType(u8"Arcadia.VPL.Symbols.VariableScalar", Arcadia_VPL_Symbols_VariableScalar,
                          u8"Arcadia.VPL.Symbols.Symbol");

struct Arcadia_VPL_Symbols_VariableScalarDispatch {
  Arcadia_VPL_Symbols_SymbolDispatch _parent;
};

struct Arcadia_VPL_Symbols_VariableScalar {
  Arcadia_VPL_Symbols_Symbol _parent;
  Arcadia_Integer32Value location;
  Arcadia_Natural8Value flags;
  Arcadia_String* name;
  Arcadia_VPL_Symbols_Symbol* type;
};

/// @brief Create a variable scalar.
/// @param thread A pointer to this thread.
/// @param location The location of the variable scalar.
/// @param name The name of the variable scalar.
/// @param type The type of the variable scalar.
Arcadia_VPL_Symbols_VariableScalar*
Arcadia_VPL_Symbols_VariableScalar_create
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value location,
    Arcadia_Natural8Value flags,
    Arcadia_String* name,
    Arcadia_VPL_Symbols_Symbol* type
  );

#endif // ARCADIA_VPL_SYMBOLS_VARIABLESCALAR_H_INCLUDED
