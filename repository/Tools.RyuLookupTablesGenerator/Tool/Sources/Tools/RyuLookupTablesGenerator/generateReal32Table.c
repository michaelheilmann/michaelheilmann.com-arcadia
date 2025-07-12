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

#include "Tools/RyuLookupTablesGenerator/generateReal32Table.h"

#include "Arcadia/Ring2/Include.h"
#include "Tools/RyuLookupTablesGenerator/Common.h"

#define POS_TABLE_SIZE 47
#define INV_TABLE_SIZE 55

#define POW5_BITCOUNT 61 /* max 63 */
#define POW5_INV_BITCOUNT 59 /* max 63 */

#include <stdio.h>

static Arcadia_BigInteger* ONE = NULL;
static Arcadia_BigInteger* MASK64 = NULL;
static Arcadia_BigInteger* TWO = NULL;

static void
onNotifyDestroy
  (
    void* argument1,
    void* argument2
  )
{
  Arcadia_BigInteger** variable = (Arcadia_BigInteger**)argument2;
  *variable = NULL;
}

void
Arcadia_Tools_RyuLookupTableGenerator_generateReal32Table
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* target
  )
{
  //
  Arcadia_BigInteger* a = NULL;
  // 1
  a = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, a, 1);
  if (Arms_addNotifyDestroy(a, NULL, &ONE, &onNotifyDestroy)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  ONE = a;
  a = NULL;

  // 2
  a = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, a, 2);
  if (Arms_addNotifyDestroy(a, NULL, &TWO, &onNotifyDestroy)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  TWO = a;
  a = NULL;

  Arcadia_BigInteger* pow5 = Arcadia_BigInteger_create(thread);
  //
  Arcadia_StringBuffer_append_pn(thread, target, u8"#define REAL32_POW5_INV_BITCOUNT ", sizeof(u8"#define REAL32_POW5_INV_BITCOUNT ") - 1);
  Arcadia_StringBuffer_insertBack(thread, target, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromInteger32(thread, POW5_INV_BITCOUNT)));
  Arcadia_StringBuffer_append_pn(thread, target, u8"\n", sizeof(u8"\n") - 1);
  //
  Arcadia_StringBuffer_append_pn(thread, target, u8"#define REAL32_POW5_BITCOUNT ", sizeof(u8"#define REAL32_POW5_BITCOUNT ") - 1);
  Arcadia_StringBuffer_insertBack(thread, target, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromInteger32(thread, POW5_BITCOUNT)));
  Arcadia_StringBuffer_append_pn(thread, target, u8"\n", sizeof(u8"\n") - 1);
  Arcadia_StringBuffer_append_pn(thread, target, u8"\n", sizeof(u8"\n") - 1);
  //
  Arcadia_StringBuffer_append_pn(thread, target, u8"static const Arcadia_Natural64Value REAL32_POW5_INV_SPLIT", sizeof(u8"static const Arcadia_Natural64Value REAL32_POW5_INV_SPLIT") - 1);
  Arcadia_StringBuffer_append_pn(thread, target, u8"[", sizeof(u8"[") - 1);
  Arcadia_StringBuffer_insertBack(thread, target, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromSize(thread, INV_TABLE_SIZE)));
  Arcadia_StringBuffer_append_pn(thread, target, u8"] = {\n", sizeof(u8"] = {\n") - 1);
  // This table basically contains the lower half1
  for (Arcadia_SizeValue i = 0; i < INV_TABLE_SIZE; ++i) {
    Arcadia_BigInteger_setPowerOfFiveNatural64(thread, pow5, i); // Should be: setPowerOfFiveSize.
    Arcadia_Integer64Value pow5Len = (Arcadia_Integer64Value)Arcadia_BigInteger_getBitLength(thread, pow5);
    Arcadia_Integer64Value j = pow5Len - 1 + POW5_INV_BITCOUNT;
    Arcadia_BigInteger* result = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_copy(thread, result, ONE);
    Arcadia_BigInteger_shiftLeftInteger64(thread, result, j);
    Arcadia_BigInteger_divide(thread, result, pow5);
    Arcadia_BigInteger_add(thread, result, ONE);
    Arcadia_Natural64Value v = Arcadia_BigInteger_toNatural64(thread, result);
    Arcadia_ImmutableUtf8String* vs = Arcadia_ImmutableUtf8String_createFromNatural64(thread, v);
    Arcadia_StringBuffer_append_pn(thread, target, u8"  ", sizeof(u8"  ") - 1);
    if (Arcadia_ImmutableUtf8String_getNumberOfCodePoints(thread, vs) < 19) {
      for (Arcadia_SizeValue j = 0, m = 19 - Arcadia_ImmutableUtf8String_getNumberOfCodePoints(thread, vs); j < m; ++j) {
        Arcadia_StringBuffer_append_pn(thread, target, u8" ", sizeof(u8" ") - 1);
      }
    }
    Arcadia_StringBuffer_insertBack(thread, target, Arcadia_Value_makeImmutableUtf8StringValue(vs));
    if (i < INV_TABLE_SIZE - 1) {
      Arcadia_StringBuffer_append_pn(thread, target, u8",", sizeof(u8",") - 1);
    }
    if (i % 4 == 3) {
      Arcadia_StringBuffer_append_pn(thread, target, u8"\n", sizeof(u8"\n") - 1);
    }
  }
  Arcadia_StringBuffer_append_pn(thread, target, u8"\n};\n", sizeof(u8"\n};\n") - 1);
  //
  Arcadia_StringBuffer_append_pn(thread, target, u8"static const Arcadia_Natural64Value REAL32_POW5_SPLIT", sizeof(u8"static const Arcadia_Natural64Value REAL32_POW5_SPLIT") - 1);
  Arcadia_StringBuffer_append_pn(thread, target, u8"[", sizeof(u8"[") - 1);
  Arcadia_StringBuffer_insertBack(thread, target, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromSize(thread, POS_TABLE_SIZE)));
  Arcadia_StringBuffer_append_pn(thread, target, u8"] = {\n", sizeof(u8"] = {\n") - 1);
  for (Arcadia_SizeValue i = 0; i < POS_TABLE_SIZE; ++i) {
    Arcadia_BigInteger_setPowerOfFiveNatural64(thread, pow5, i); // Should be: setPowerOfFiveSize.
    Arcadia_Integer64Value pow5Len = (Arcadia_Integer64Value)Arcadia_BigInteger_getBitLength(thread, pow5);
    Arcadia_Integer64Value j = pow5Len - POW5_BITCOUNT;
    Arcadia_BigInteger* result = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_copy(thread, result, pow5);
    Arcadia_BigInteger_shiftRightInteger64(thread, result, j);
    Arcadia_Natural64Value v =Arcadia_BigInteger_toNatural64(thread, result);
    Arcadia_ImmutableUtf8String* vs = Arcadia_ImmutableUtf8String_createFromNatural64(thread, v);
    Arcadia_StringBuffer_append_pn(thread, target, u8"  ", sizeof(u8"  ") - 1);
    if (Arcadia_ImmutableUtf8String_getNumberOfCodePoints(thread, vs) < 19) {
      for (Arcadia_SizeValue j = 0, m = 19 - Arcadia_ImmutableUtf8String_getNumberOfCodePoints(thread, vs); j < m; ++j) {
        Arcadia_StringBuffer_append_pn(thread, target, u8" ", sizeof(u8" ") - 1);
      }
    }
    Arcadia_StringBuffer_insertBack(thread, target, Arcadia_Value_makeImmutableUtf8StringValue(vs));
    if (i < POS_TABLE_SIZE - 1) {
      Arcadia_StringBuffer_append_pn(thread, target, u8",", sizeof(u8",") - 1);
    }
    if (i % 4 == 3) {
      Arcadia_StringBuffer_append_pn(thread, target, u8"\n", sizeof(u8"\n") - 1);
    }
  }
  Arcadia_StringBuffer_append_pn(thread, target, u8"\n};\n", sizeof(u8"\n};\n") - 1);
}
