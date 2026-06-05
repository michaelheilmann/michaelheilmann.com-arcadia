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

#include "Arcadia.Ring1.Tests.SubStringTests/findFirstOccurrenceTests.h"

void
findFirstOccurrenceTests1
  (
    Arcadia_Thread* thread
  )
{
  {
    Arcadia_RuntimeUTF8String* string; 
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"", sizeof(u8"") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isVoidValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"b", sizeof(u8"b") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isVoidValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"bb", sizeof(u8"bb") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isVoidValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"bbb", sizeof(u8"bbb") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isVoidValue(&position));
  }
}

void
findFirstOccurrenceTests2
  (
    Arcadia_Thread* thread
  )
{
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"abbb", sizeof(u8"abbb") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isSizeValue(&position) && 0 == Arcadia_Value_getSizeValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"babb", sizeof(u8"babb") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isSizeValue(&position) && 1 == Arcadia_Value_getSizeValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"bbab", sizeof(u8"bbab") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isSizeValue(&position) && 2 == Arcadia_Value_getSizeValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"bbba", sizeof(u8"bbba") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isSizeValue(&position) && 3 == Arcadia_Value_getSizeValue(&position));
  }
}

void
findFirstOccurrenceTests3
  (
    Arcadia_Thread* thread
  )
{
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"ababb", sizeof(u8"ababb") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isSizeValue(&position) && 0 == Arcadia_Value_getSizeValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"babba", sizeof(u8"babba") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isSizeValue(&position) && 1 == Arcadia_Value_getSizeValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"bbaba", sizeof(u8"bbaba") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isSizeValue(&position) && 2 == Arcadia_Value_getSizeValue(&position));
  }
  {
    Arcadia_RuntimeUTF8String* string;
    Arcadia_Value position;
    string = Arcadia_RuntimeUTF8String_create(thread, u8"bbbaa", sizeof(u8"bbbaa") - 1);
    position = Arcadia_RuntimeUTF8String_findFirstOccurrence(thread, string, 'a');
    Arcadia_Tests_assertTrue(thread, Arcadia_Value_isSizeValue(&position) && 3 == Arcadia_Value_getSizeValue(&position));
  }
}
