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

// Last modified: 2025-02-19

#if !defined(ARCADIA_RING1_SUPPORT_TABLES_H_INCLUDED)
#define ARCADIA_RING1_SUPPORT_TABLES_H_INCLUDED


#include <stdint.h>

int
power_of_two_table_get_max_e_uint64
  (
    uint64_t* result
  );

int
power_of_two_table_get_uint64
  (
    uint64_t* result,
    uint64_t e
  );


int
power_of_five_table_get_max_e_uint64
  (
    uint64_t* result
  );

int
power_of_five_table_get_uint64
  (
    uint64_t* result,
    uint64_t e
  );


int
power_of_ten_table_get_max_e_uint64
  (
    uint64_t* result
  );

int
power_of_ten_table_get_uint64
  (
    uint64_t* result,
    uint64_t e
  );


#endif // ARCADIA_RING1_SUPPORT_TABLES_H_INCLUDED
