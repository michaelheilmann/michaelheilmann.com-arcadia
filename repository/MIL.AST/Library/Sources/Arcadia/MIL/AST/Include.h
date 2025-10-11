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

#if !defined(ARCADIA_MIL_AST_INCLUDE_H_INCLUDED)
#define ARCADIA_MIL_AST_INCLUDE_H_INCLUDED

#include "Arcadia/MIL/AST/DefinitionNode.h"
#include "Arcadia/MIL/AST/DefinitionStatementNode.h"
#include "Arcadia/MIL/AST/InstructionNode.h"
#include "Arcadia/MIL/AST/InstructionStatementNode.h"
#include "Arcadia/MIL/AST/ModuleNode.h"
#include "Arcadia/MIL/AST/Node.h"
#include "Arcadia/MIL/AST/OperandNode.h"
#include "Arcadia/MIL/AST/StatementNode.h"

#include "Arcadia/MIL/AST/Instructions/BinaryInstructionNode.h"
#include "Arcadia/MIL/AST/Instructions/InvokeInstructionNode.h"
#include "Arcadia/MIL/AST/Instructions/JumpInstructionNode.h"
#include "Arcadia/MIL/AST/Instructions/RaiseInstructionNode.h"
#include "Arcadia/MIL/AST/Instructions/ReturnInstructionNode.h"
#include "Arcadia/MIL/AST/Instructions/UnaryInstructionNode.h"

#include "Arcadia/MIL/AST/Literals/BooleanLiteralNode.h"
#include "Arcadia/MIL/AST/Literals/IntegerLiteralNode.h"
#include "Arcadia/MIL/AST/Literals/RealLiteralNode.h"
#include "Arcadia/MIL/AST/Literals/StringLiteralNode.h"
#include "Arcadia/MIL/AST/Literals/VoidLiteralNode.h"

#include "Arcadia/MIL/AST/Operands/LiteralOperandNode.h"
#include "Arcadia/MIL/AST/Operands/RegisterOperandNode.h"
#include "Arcadia/MIL/AST/Operands/VariableOperandNode.h"

#include "Arcadia/MIL/AST/Definitions/ClassDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/ConstructorDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/EnumerationConstantDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/EnumerationDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/FieldDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/MethodDefinitionNode.h"
#include "Arcadia/MIL/AST/Definitions/ProcedureDefinitionNode.h"

#include "Arcadia/MIL/AST/DefinitionStatements/LabelDefinitionStatementNode.h"
#include "Arcadia/MIL/AST/DefinitionStatements/VariableDefinitionStatementNode.h"

#include "Arcadia/MIL/AST/DefinitionNode.h"
#include "Arcadia/MIL/AST/DefinitionStatementNode.h"
#include "Arcadia/MIL/AST/InstructionNode.h"
#include "Arcadia/MIL/AST/InstructionStatementNode.h"
#include "Arcadia/MIL/AST/ModuleNode.h"
#include "Arcadia/MIL/AST/Node.h"
#include "Arcadia/MIL/AST/OperandNode.h"
#include "Arcadia/MIL/AST/StatementNode.h"

#endif // ARCADIA_MIL_AST_INCLUDE_H_INCLUDED
