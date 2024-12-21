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

// Last modified: 2024-09-27

#if !defined(R_MAP_H_INCLUDED)
#define R_MAP_H_INCLUDED

#include "R/Object.h"
#include "R/List.h"
#include "R/Value.h"

Rex_declareObjectType("R.Map", R_Map, "R.Object");

R_Map*
R_Map_create
  (
  );

R_Map*
R_Map_clone
  (
    R_Map* self
  );

void
R_Map_clear
  (
    R_Map* self
  );

R_SizeValue
R_Map_getSize
  (
    R_Map const* self
  );

void
R_Map_set
  (
    R_Map* self,
    R_Value key,
    R_Value value
  );

R_Value
R_Map_get
  (
    R_Map const* self,
    R_Value key
  );

R_List*
R_Map_getValues
  (
    R_Map const* self
  );

R_List*
R_Map_getKeys
  (
    R_Map const* self
  );

#endif // R_MAP_H_INCLUDED
