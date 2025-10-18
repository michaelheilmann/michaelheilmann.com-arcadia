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

#if !defined(ARCADIA_MIL_AST_BINARYINSTRUCTIONKIND_H_INCLUDED)
#define ARCADIA_MIL_AST_BINARYINSTRUCTIONKIND_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

Arcadia_declareEnumerationType(u8"Arcadia.MIL.AST.BinaryInstructionKind", Arcadia_MIL_AST_BinaryInstructionKind);

enum Arcadia_MIL_AST_BinaryInstructionKind {

  /// @code
  /// addInstruction : 'add' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_Add = 1,

  /// @code
  /// andInstruction : 'and' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_And = 2,

  /// @code
  /// concatenateInstruction : 'concatenate' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_Concatenate = 3,

  /// @code
  /// divideInstruction : 'divide' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_Divide = 4,

  /// @code
  /// multiplyInstruction : 'multiply' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_Multiply = 5,

  /// @code
  /// orInstruction : 'or' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_Or = 6,

  /// @code
  /// subtractInstruction : 'subtract' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_Subtract = 7,

  /// @code
  /// isEqualToInstruction : 'isEqualTo' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_IsEqualTo = 8,

  /// @code
  /// isEqualToInstruction : 'isNotEqualTo' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_IsNotEqualTo = 9,

  /// @code
  /// isLowerThanInstruction : 'isLowerThan' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_IsLowerThan = 10,

  /// @code
  /// isLowerThanOrEqualToInstruction : 'isLowerThanOrEqualTo' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_IsLowerThanOrEqualTo = 11,

  /// @code
  /// isGreaterThanInstruction : 'isGreaterThan' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_IsGreaterThan = 12,

  /// @code
  /// isGreaterThanOrEqualToInstruction : 'isGreaterThanOrEqualTo' target, firstOperand, secondOperand
  /// target : register
  /// firstOperand : register
  /// secondOperand : register
  /// @endcode
  Arcadia_MIL_AST_BinaryInstructionKind_IsGreaterThanOrEqualTo = 13,

};

#endif // ARCADIA_MIL_AST_BINARYINSTRUCTIONKIND_H_INCLUDED
