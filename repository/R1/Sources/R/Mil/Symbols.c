// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-12-08

#include "R/Mil/Symbols.h"

#include "R/ArmsIntegration.h"
#include "R/ArgumentsValidation.h"
#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/UnmanagedMemory.h"
#include "R/cstdlib.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_Symbol_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_Symbol_visit
  (
    R_Mil_Symbol* self
  );

static const R_ObjectType_Operations R_Mil_Symbol_objectTypeOperations = {
  .construct = &R_Mil_Symbol_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations R_Mil_Symbol_typeOperations = {
  .objectTypeOperations = &R_Mil_Symbol_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.Symbol", R_Mil_Symbol, "R.Object", R_Object, &R_Mil_Symbol_typeOperations)

static void
R_Mil_Symbol_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_Symbol* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_Symbol_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (4 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->name = R_Argument_getObjectReferenceValue(&argumentValues[0], _R_String_getType());
  _self->sibling = R_Argument_getObjectReferenceValueOrNull(&argumentValues[1], _R_Mil_Symbol_getType());
  _self->shadowed = R_Argument_getObjectReferenceValueOrNull(&argumentValues[2], _R_Mil_Symbol_getType());
  _self->scope = R_Argument_getObjectReferenceValue(&argumentValues[3], _R_Mil_Scope_getType());
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Mil_Symbol_visit
  (
    R_Mil_Symbol* self
  )
{
  R_Object_visit(self->name);
  R_Object_visit(self->sibling);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_SymbolTable_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_SymbolTable_destruct
  (
    R_Mil_SymbolTable* self
  );

static void
R_Mil_SymbolTable_doubleCapacity
  (
    R_Mil_SymbolTable* self
  );

static void
R_Mil_SymbolTable_visit
  (
    R_Mil_SymbolTable* self
  );

static const R_ObjectType_Operations R_Mil_SymbolTable_objectTypeOperations = {
  .construct = &R_Mil_SymbolTable_constructImpl,
  .destruct = &R_Mil_SymbolTable_destruct,
  .visit = &R_Mil_SymbolTable_visit,
};

static const R_Type_Operations R_Mil_SymbolTable_typeOperations = {
  .objectTypeOperations = &R_Mil_SymbolTable_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.SymbolTable", R_Mil_SymbolTable, "R.Object", R_Object, &R_Mil_SymbolTable_typeOperations)

static void
R_Mil_SymbolTable_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_SymbolTable* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_SymbolTable_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (!R_allocateUnmanaged_nojump((void**)&_self->elements, sizeof(R_Mil_Symbol*) * 8)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = 8; i < n; ++i) {
    _self->elements[i] = NULL;
  }
  _self->size = 0;
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Mil_SymbolTable_destruct
  (
    R_Mil_SymbolTable* self
  )
{
  R_deallocateUnmanaged_nojump(self->elements);
  self->elements = NULL;
}

static void
R_Mil_SymbolTable_doubleCapacity
  (
   R_Mil_SymbolTable* self
  )
{
  static const R_SizeValue maximalCapacity1 = R_SizeValue_Maximum / 3;
  static const R_SizeValue maximalCapacity2 = R_SizeValue_Maximum / sizeof(void*);
  R_SizeValue maximalCapacity = maximalCapacity1 < maximalCapacity2 ? maximalCapacity1 : maximalCapacity2;

  R_SizeValue oldCapacity = self->capacity;
  R_SizeValue newCapacity;
  if (c_safe_mul_sz(oldCapacity, 2, &newCapacity)) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  if (newCapacity > maximalCapacity) {
    R_setStatus(R_Status_AllocationFailed);
    R_jump();
  }
  if (!R_reallocateUnmanaged_nojump((void**)&self->elements, sizeof(void*) * newCapacity)) {
    R_jump();
  }
  for (R_SizeValue i = oldCapacity, n = newCapacity; i < n; ++i) {
    self->elements[i] = NULL;
  }
}

static void
R_Mil_SymbolTable_visit
  (
    R_Mil_SymbolTable* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    R_Object_visit(self->elements[i]);
  }
}

static const char g_dummy = 0;

R_SizeValue
R_Mil_SymbolTable_getIndex
  (
    R_Mil_SymbolTable* self,
    R_String* name
  )
{
  R_SizeValue hash = R_Object_hash((R_Object*)name);
  R_SizeValue index = hash % self->capacity;
  R_SizeValue tombstoneIndex = 0;
  R_BooleanValue tombstoneFound = R_BooleanValue_False;
  while (R_BooleanValue_True) {
    R_Mil_Symbol* entry = self->elements[index];
    R_Value nameValue = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = name };
    if (NULL == entry) {
      return tombstoneFound ? tombstoneIndex : index;
    } else if ((R_Mil_Symbol*)&g_dummy == entry) {
      if (!tombstoneFound) {
        tombstoneFound = R_BooleanValue_True;
        tombstoneIndex = index;
      }
    } else if (R_Object_equalTo((R_Object*)entry->name, &nameValue)) {
      return index;
    }
    index = (index + 1) % self->capacity;
  }
  return index;
}

R_Mil_SymbolTable*
R_Mil_SymbolTable_create
  (
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void },
  };
  R_Mil_SymbolTable* self = R_allocateObject(_R_Mil_SymbolTable_getType(), 0, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
R_Mil_Scope_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );
  
static void
R_Mil_Scope_destruct
  (
    R_Mil_Scope* self
  );

static void
R_Mil_Scope_visit
  (
    R_Mil_Scope* self
  );

static const R_ObjectType_Operations R_Mil_Scope_objectTypeOperations = {
  .construct = &R_Mil_Scope_constructImpl,
  .destruct = &R_Mil_Scope_destruct,
  .visit = &R_Mil_Scope_visit,
};

static const R_Type_Operations R_Mil_Scope_typeOperations = {
  .objectTypeOperations = &R_Mil_Scope_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.Scope", R_Mil_Scope, "R.Object", R_Object, &R_Mil_Scope_typeOperations)

static void
set
  (
    R_Mil_Scope* self,
    R_String* name
  )
{
  while (self->table->size * 3 >= self->table->capacity * 2) {
    // basically size * 1.5 >= capacity or size >= capacity * 0.6...
    R_Mil_SymbolTable_doubleCapacity(self->table);
  }
  R_SizeValue index = R_Mil_SymbolTable_getIndex(self->table, name);
  R_Mil_Symbol* shadowed = self->table->elements[index];
  R_Mil_Symbol* symbol = R_Mil_Symbol_create(name);
  if (NULL == shadowed) {
    shadowed = (void*)&g_dummy;
    self->table->size++;
  }
  // Add to table.
  self->table->elements[index] = symbol;
  self->table->size++;
  // Link with shadowed.
  symbol->shadowed = shadowed;
  // Link with siblings in the scope.
  symbol->sibling = self->entries;
  self->entries = symbol;
  // Link with the scope.
  symbol->scope = self;
}

static R_Mil_Symbol*
get
  (
    R_Mil_Scope* self,
    R_String* name
  )
{
  R_SizeValue index = R_Mil_SymbolTable_getIndex(self->table, name);
  if (self->table->elements[index] == NULL || self->table->elements[index] == (R_Mil_Symbol*)&g_dummy) {
    return NULL;
  }
  return self->table->elements[index];
}

static void
R_Mil_Scope_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_Scope* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_Scope_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->enclosing = NULL;
  _self->entries = NULL;
  _self->table = R_Mil_SymbolTable_create();
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Mil_Scope_destruct
  (
    R_Mil_Scope* self
  )
{/*Intentionally empty.*/}

static void
R_Mil_Scope_visit
  (
    R_Mil_Scope* self
  )
{
  R_Object_visit(self->enclosing);
  R_Mil_Symbol* symbol = self->entries;
  while (symbol) {
    R_Object_visit(symbol);
    symbol = symbol->sibling;
  }
}

R_Mil_Scope*
R_Mil_Scope_create
  (
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void },
  };
  R_Mil_Scope* self = R_allocateObject(_R_Mil_Scope_getType(), 0, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
