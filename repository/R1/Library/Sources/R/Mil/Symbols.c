// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Mil_Symbol_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_Symbol_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_Symbol* self
  );

static const Arcadia_ObjectType_Operations Arcadia_Mil_Symbol_objectTypeOperations = {
  .construct = &Arcadia_Mil_Symbol_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_Symbol_visit,
};

static const Arcadia_Type_Operations Arcadia_Mil_Symbol_typeOperations = {
  .objectTypeOperations = &Arcadia_Mil_Symbol_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.Symbol", Arcadia_Mil_Symbol, u8"Arcadia.Object", Arcadia_Object, &Arcadia_Mil_Symbol_typeOperations)

static void
Arcadia_Mil_Symbol_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_Symbol* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_Symbol_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (4 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->name = R_Argument_getObjectReferenceValue(process, &argumentValues[0], _Arcadia_String_getType(process));
  _self->sibling = R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[1], _Arcadia_Mil_Symbol_getType(process));
  _self->shadowed = R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[2], _Arcadia_Mil_Symbol_getType(process));
  _self->scope = R_Argument_getObjectReferenceValue(process, &argumentValues[3], _Arcadia_Mil_Scope_getType(process));
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_Symbol_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_Symbol* self
  )
{
  Arcadia_Object_visit(process, self->name);
  Arcadia_Object_visit(process, self->sibling);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Mil_SymbolTable_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_SymbolTable_destruct
  (
    Arcadia_Process* process,
    Arcadia_Mil_SymbolTable* self
  );

static void
Arcadia_Mil_SymbolTable_doubleCapacity
  (
    Arcadia_Process* process,
    Arcadia_Mil_SymbolTable* self
  );

static void
Arcadia_Mil_SymbolTable_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_SymbolTable* self
  );

static const Arcadia_ObjectType_Operations Arcadia_Mil_SymbolTable_objectTypeOperations = {
  .construct = &Arcadia_Mil_SymbolTable_constructImpl,
  .destruct = &Arcadia_Mil_SymbolTable_destruct,
  .visit = &Arcadia_Mil_SymbolTable_visit,
};

static const Arcadia_Type_Operations Arcadia_Mil_SymbolTable_typeOperations = {
  .objectTypeOperations = &Arcadia_Mil_SymbolTable_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.SymbolTable", Arcadia_Mil_SymbolTable, u8"Arcadia.Object", Arcadia_Object, &Arcadia_Mil_SymbolTable_typeOperations)

static void
Arcadia_Mil_SymbolTable_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_SymbolTable* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_SymbolTable_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  Arcadia_Process_allocateUnmanaged(process, (void**)&_self->elements, sizeof(Arcadia_Mil_Symbol*) * 8);
  for (Arcadia_SizeValue i = 0, n = 8; i < n; ++i) {
    _self->elements[i] = NULL;
  }
  _self->size = 0;
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_SymbolTable_destruct
  (
    Arcadia_Process* process,
    Arcadia_Mil_SymbolTable* self
  )
{
  Arcadia_Process_deallocateUnmanaged(process, self->elements);
  self->elements = NULL;
}

static void
Arcadia_Mil_SymbolTable_doubleCapacity
  (
    Arcadia_Process* process,
    Arcadia_Mil_SymbolTable* self
  )
{
  static const Arcadia_SizeValue maximalCapacity1 = Arcadia_SizeValue_Maximum / 3;
  static const Arcadia_SizeValue maximalCapacity2 = Arcadia_SizeValue_Maximum / sizeof(void*);
  Arcadia_SizeValue maximalCapacity = maximalCapacity1 < maximalCapacity2 ? maximalCapacity1 : maximalCapacity2;

  Arcadia_SizeValue oldCapacity = self->capacity;
  Arcadia_SizeValue newCapacity, overflow;
  Arcadia_safeMultiply_sz(Arcadia_Process_getProcess1(process), oldCapacity, 2, &overflow, &newCapacity);
  if (overflow) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  if (newCapacity > maximalCapacity) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  Arcadia_Process_reallocateUnmanaged(process, (void**)&self->elements, sizeof(void*) * newCapacity);
  for (Arcadia_SizeValue i = oldCapacity, n = newCapacity; i < n; ++i) {
    self->elements[i] = NULL;
  }
}

static void
Arcadia_Mil_SymbolTable_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_SymbolTable* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Arcadia_Object_visit(process, self->elements[i]);
  }
}

static const char g_dummy = 0;

Arcadia_SizeValue
Arcadia_Mil_SymbolTable_getIndex
  (
    Arcadia_Process* process,
    Arcadia_Mil_SymbolTable* self,
    Arcadia_String* name
  )
{
  Arcadia_Value nameValue = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = name };
  Arcadia_SizeValue hash = Arcadia_Value_getHash(process, &nameValue);
  Arcadia_SizeValue index = hash % self->capacity;
  Arcadia_SizeValue tombstoneIndex = 0;
  Arcadia_BooleanValue tombstoneFound = Arcadia_BooleanValue_False;
  while (Arcadia_BooleanValue_True) {
    Arcadia_Mil_Symbol* entry = self->elements[index];
    Arcadia_Value entryNameValue = { .tag =Arcadia_ValueTag_ObjectReference, .objectReferenceValue = entry->name };
    if (NULL == entry) {
      return tombstoneFound ? tombstoneIndex : index;
    } else if ((Arcadia_Mil_Symbol*)&g_dummy == entry) {
      if (!tombstoneFound) {
        tombstoneFound = Arcadia_BooleanValue_True;
        tombstoneIndex = index;
      }
    } else if (Arcadia_Value_isEqualTo(process, &entryNameValue, &nameValue)) {
      return index;
    }
    index = (index + 1) % self->capacity;
  }
  return index;
}

Arcadia_Mil_SymbolTable*
Arcadia_Mil_SymbolTable_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = {
    {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
  };
  Arcadia_Mil_SymbolTable* self = R_allocateObject(process, _Arcadia_Mil_SymbolTable_getType(process), 0, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Arcadia_Mil_Scope_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );
  
static void
Arcadia_Mil_Scope_destruct
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scope* self
  );

static void
Arcadia_Mil_Scope_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scope* self
  );

static const Arcadia_ObjectType_Operations Arcadia_Mil_Scope_objectTypeOperations = {
  .construct = &Arcadia_Mil_Scope_constructImpl,
  .destruct = &Arcadia_Mil_Scope_destruct,
  .visit = &Arcadia_Mil_Scope_visit,
};

static const Arcadia_Type_Operations Arcadia_Mil_Scope_typeOperations = {
  .objectTypeOperations = &Arcadia_Mil_Scope_objectTypeOperations,
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

Rex_defineObjectType(u8"Arcadia.Mil.Scope", Arcadia_Mil_Scope, u8"Arcadia.Object", Arcadia_Object, &Arcadia_Mil_Scope_typeOperations)

static void
set
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scope* self,
    Arcadia_String* name
  )
{
  while (self->table->size * 3 >= self->table->capacity * 2) {
    // basically size * 1.5 >= capacity or size >= capacity * 0.6...
    Arcadia_Mil_SymbolTable_doubleCapacity(process, self->table);
  }
  Arcadia_SizeValue index = Arcadia_Mil_SymbolTable_getIndex(process, self->table, name);
  Arcadia_Mil_Symbol* shadowed = self->table->elements[index];
  Arcadia_Mil_Symbol* symbol = Arcadia_Mil_Symbol_create(name);
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

static Arcadia_Mil_Symbol*
get
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scope* self,
    Arcadia_String* name
  )
{
  Arcadia_SizeValue index = Arcadia_Mil_SymbolTable_getIndex(process, self->table, name);
  if (self->table->elements[index] == NULL || self->table->elements[index] == (Arcadia_Mil_Symbol*)&g_dummy) {
    return NULL;
  }
  return self->table->elements[index];
}

static void
Arcadia_Mil_Scope_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_Scope* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_Scope_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->enclosing = NULL;
  _self->entries = NULL;
  _self->table = Arcadia_Mil_SymbolTable_create(process);
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_Mil_Scope_destruct
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scope* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Mil_Scope_visit
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scope* self
  )
{
  Arcadia_Object_visit(process, self->enclosing);
  Arcadia_Mil_Symbol* symbol = self->entries;
  while (symbol) {
    Arcadia_Object_visit(process, symbol);
    symbol = symbol->sibling;
  }
}

Arcadia_Mil_Scope*
Arcadia_Mil_Scope_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = {
    {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
  };
  Arcadia_Mil_Scope* self = R_allocateObject(process, _Arcadia_Mil_Scope_getType(process), 0, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
