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

#if !defined(ARCADIA_MIL_AST2_INCLUDE_H_INCLUDED)
#define ARCADIA_MIL_AST2_INCLUDE_H_INCLUDED

#include "Arcadia/MIL/AST/Literals/BooleanLiteralNode.h"
#include "Arcadia/MIL/AST/Literals/IntegerLiteralNode.h"
#include "Arcadia/MIL/AST/Literals/RealLiteralNode.h"
#include "Arcadia/MIL/AST/Literals/StringLiteralNode.h"
#include "Arcadia/MIL/AST/Literals/VoidLiteralNode.h"

#include "Arcadia/MIL/AST/Operands/LiteralOperandNode.h"
#include "Arcadia/MIL/AST/Operands/OperandNode.h"
#include "Arcadia/MIL/AST/Operands/RegisterOperandNode.h"
#include "Arcadia/MIL/AST/Operands/VariableOperandNode.h"

#include "Arcadia/MIL/AST/StatementNode.h"

#include "Arcadia/MIL/AST/InstructionNode.h"
#include "Arcadia/MIL/AST/BinaryInstructionNode.h"
#include "Arcadia/MIL/AST/InvokeInstructionNode.h"
#include "Arcadia/MIL/AST/UnaryInstructionNode.h"

#include "Arcadia/MIL/AST/Definitions/ClassDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/ConstructorDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/FieldDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/MethodDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/ProcedureDefinitionNode.h"

#include "Arcadia/MIL/AST/ExpressionStatementAst.h"
#include "Arcadia/MIL/AST/LoadExpressionAst.h"
#include "Arcadia/MIL/AST/ModuleAst.h"
#include "Arcadia/MIL/AST/RaiseStatementAst.h"
#include "Arcadia/MIL/AST/ReturnStatementAst.h"


#include "Arcadia/MIL/AST/VariableDefinitionStatementAst.h"

#include "Arcadia/MIL/AST/JumpStatementNode.h"
#include "Arcadia/MIL/AST/LabelStatementNode.h"

#endif // ARCADIA_MIL_AST2_INCLUDE_H_INCLUDED
