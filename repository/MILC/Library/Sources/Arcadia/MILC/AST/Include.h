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

#if !defined(ARCADIA_MILC_AST_INCLUDE_H_INCLUDED)
#define ARCADIA_MILC_AST_INCLUDE_H_INCLUDED

#include "Arcadia/MILC/AST/DefinitionNode.h"
#include "Arcadia/MILC/AST/DefinitionStatementNode.h"
#include "Arcadia/MILC/AST/InstructionNode.h"
#include "Arcadia/MILC/AST/InstructionStatementNode.h"
#include "Arcadia/MILC/AST/ModuleNode.h"
#include "Arcadia/MILC/AST/Node.h"
#include "Arcadia/MILC/AST/OperandNode.h"
#include "Arcadia/MILC/AST/StatementNode.h"

#include "Arcadia/MILC/AST/CompilationUnitNode.h"

#include "Arcadia/MILC/AST/IdentifierNode.h"

#include "Arcadia/MILC/AST/Instructions/BinaryInstructionNode.h"
#include "Arcadia/MILC/AST/Instructions/InvokeInstructionNode.h"
#include "Arcadia/MILC/AST/Instructions/JumpInstructionNode.h"
#include "Arcadia/MILC/AST/Instructions/RaiseInstructionNode.h"
#include "Arcadia/MILC/AST/Instructions/ReturnInstructionNode.h"
#include "Arcadia/MILC/AST/Instructions/UnaryInstructionNode.h"

#include "Arcadia/MILC/AST/Literals/BooleanLiteralNode.h"
#include "Arcadia/MILC/AST/Literals/IntegerLiteralNode.h"
#include "Arcadia/MILC/AST/Literals/RealLiteralNode.h"
#include "Arcadia/MILC/AST/Literals/StringLiteralNode.h"
#include "Arcadia/MILC/AST/Literals/VoidLiteralNode.h"

#include "Arcadia/MILC/AST/Operands/LiteralOperandNode.h"
#include "Arcadia/MILC/AST/Operands/RegisterOperandNode.h"
#include "Arcadia/MILC/AST/Operands/VariableOperandNode.h"

#include "Arcadia/MILC/AST/Definitions/ClassDefinitionNode.h"
#include "Arcadia/MILC/AST/Definitions/ConstructorDefinitionNode.h"
#include "Arcadia/MILC/AST/Definitions/EnumerationConstantDefinitionNode.h"
#include "Arcadia/MILC/AST/Definitions/EnumerationDefinitionNode.h"
#include "Arcadia/MILC/AST/Definitions/FieldDefinitionNode.h"
#include "Arcadia/MILC/AST/Definitions/MethodDefinitionNode.h"
#include "Arcadia/MILC/AST/Definitions/ModuleDefinitionNode.h"
#include "Arcadia/MILC/AST/Definitions/ProcedureDefinitionNode.h"

#include "Arcadia/MILC/AST/DefinitionStatements/LabelDefinitionStatementNode.h"
#include "Arcadia/MILC/AST/DefinitionStatements/VariableDefinitionStatementNode.h"

#include "Arcadia/MILC/AST/DefinitionNode.h"
#include "Arcadia/MILC/AST/DefinitionStatementNode.h"
#include "Arcadia/MILC/AST/InstructionNode.h"
#include "Arcadia/MILC/AST/InstructionStatementNode.h"
#include "Arcadia/MILC/AST/ModuleNode.h"
#include "Arcadia/MILC/AST/Node.h"
#include "Arcadia/MILC/AST/OperandNode.h"
#include "Arcadia/MILC/AST/StatementNode.h"

#include "Arcadia/MILC/AST/Visitor.h"

#endif // ARCADIA_MILC_AST_INCLUDE_H_INCLUDED
