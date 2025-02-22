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

#include "Arcadia/Ring1/Support/tables.h"

// size_t
#include <stddef.h>
// malloc, free
#include <malloc.h>
// bool, true, false
#include <stdbool.h>
// atexit
#include <stdlib.h>
// uint64_t
#include <stdint.h>

static bool g_registered = false;

// The maximum value of uint64_t is 18446744073709551615.
// The greatest e such that 2^e <= 18446744073709551615 is floor(log5(18446744073709551615)) = 63.
static size_t g_powers_of_two_max_e = (size_t)63;
static uint64_t *g_powers_of_two = NULL;

// The maximum value of uint64_t is 18446744073709551615.
// The greatest e such that 5^e <= 18446744073709551615 is floor(log5(18446744073709551615)) = 27.
static size_t g_powers_of_five_max_e = (size_t)27; 
static uint64_t* g_powers_of_five = NULL;

// The maximum value of uint64_t is 18446744073709551615.
// The greatest e such that 10^e <= 18446744073709551615 is floor(log10(18446744073709551615)) = 19.
static size_t g_powers_of_ten_max_e = (size_t)19;
static uint64_t* g_powers_of_ten = NULL;

static void
destroy_tables_callback
  (
    void
  )
{
  if (g_powers_of_ten) {
    free(g_powers_of_ten);
    g_powers_of_ten = NULL;
  }
  if (g_powers_of_five) {
    free(g_powers_of_five);
    g_powers_of_five = NULL;
  }
  if (g_powers_of_two) {
    free(g_powers_of_two);
    g_powers_of_two = NULL;
  }
}

static int
create_tables
  (
  )
{
  if (!g_registered) {
    if (atexit(&destroy_tables_callback)) {
      return 1;
    }
  }
  if (!g_powers_of_two) {
    g_powers_of_two = malloc(sizeof(uint64_t) * (g_powers_of_two_max_e + 1));
    if (!g_powers_of_two) {
      return 1;
    }
    g_powers_of_two[0] = 1;
    g_powers_of_two[1] = 2;
    for (size_t i = 2; i < g_powers_of_two_max_e + 1; ++i) {
      g_powers_of_two[i] = UINT64_C(2) * g_powers_of_two[i-1];
    }
  }
  if (!g_powers_of_five) {
    g_powers_of_five = malloc(sizeof(uint64_t) * (g_powers_of_five_max_e + 1));
    if (!g_powers_of_five) {
      return 1;
    }
    g_powers_of_five[0] = 1;
    g_powers_of_five[1] = 5;
    for (size_t i = 2; i < g_powers_of_five_max_e + 1; ++i) {
      g_powers_of_five[i] = UINT64_C(5) * g_powers_of_five[i - 1];
    }
  }
  if (!g_powers_of_ten) {
    g_powers_of_ten = malloc(sizeof(uint64_t) * (g_powers_of_ten_max_e + 1));
    if (!g_powers_of_ten) {
      return 1;
    }
    g_powers_of_ten[0] = 1;
    g_powers_of_ten[1] = 10;
    for (size_t i = 2; i < g_powers_of_ten_max_e + 1; ++i) {
      g_powers_of_ten[i] = UINT64_C(10) * g_powers_of_ten[i - 1];
    }
  }
  return 0;  
}

int
power_of_two_table_get_max_e_uint64
  (
    uint64_t* result
  )
{
  if (!result || create_tables()) {
    return 1;
  }
  *result = g_powers_of_two_max_e;
  return 0;
}

int
power_of_two_table_get_uint64
  (
    uint64_t* result,
    uint64_t e
  )
{
  if (!result || create_tables()) {
    return 1;
  }
  if (e > g_powers_of_two_max_e) {
    return 1;
  }
  *result = g_powers_of_two[e];
  return 0;
}


int
power_of_five_table_get_max_e_uint64
  (
    uint64_t* result
  )
{
  if (!result || create_tables()) {
    return 1;
  }
  *result = g_powers_of_five_max_e;
  return 0;
}

int
power_of_five_table_get_uint64
  (
    uint64_t* result,
    uint64_t e
  )
{
  if (!result || create_tables()) {
    return 1;
  }
  if (e > g_powers_of_five_max_e) {
    return 1;
  }
  *result = g_powers_of_five[e];
  return 0;
}


int
power_of_ten_table_get_max_e_uint64
  (
    uint64_t* result
  )
{
  if (!result || create_tables()) {
    return 1;
  }
  *result = g_powers_of_ten_max_e;
  return 0;
}

int
power_of_ten_table_get_uint64
  (
    uint64_t* result,
    uint64_t e
  )
{
  if (!result || create_tables()) {
    return 1;
  }
  if (e > g_powers_of_ten_max_e) {
    return 1;
  }
  *result = g_powers_of_ten[e];
  return 0;
}
