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

#if !defined(ARCADIA_ENGINE_DEMO_CONFIGURATIONUTILITIES_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_CONFIGURATIONUTILITIES_H_INCLUDED

#include "Arcadia/DataDefinitionLanguage/Include.h"

// { <name[0]> = { <name[1]> : { <name[2]> : ... { <name[n-1]> : <value>} } } }
// node must be a map node
void
Cfg2_setBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames,
    Arcadia_Integer32Value value
  );

// node must be a map node
// errors: not exists or conversion failed
Arcadia_BooleanValue
Cfg2_getBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames
  );

// { <name[0]> = { <name[1]> : { <name[2]> : ... { <name[n-1]> : <value>} } } }
// node must be a map node
void
Cfg2_setInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames,
    Arcadia_Integer32Value value
  );

// node must be a map node
// errors: not exists or conversion failed
Arcadia_Integer32Value
Cfg2_getInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames
  );

// { <name[0]> = { <name[1]> : { <name[2]> : ... { <name[n-1]> : <value>} } } }
// node must be a map node
void
Cfg2_setString
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames,
    Arcadia_String* value
  );

// node must be a map node
// errors: not exists or conversion failed
Arcadia_String*
Cfg2_getString
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames
  );

// { <name[0]> = { <name[1]> : { <name[2]> : ... { <name[n-1]> : { } } } } }
// node must be a map node
void
Cfg2_setSection
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    char const* names[],
    Arcadia_SizeValue numberOfNames
  );

void
Cfg_saveConfiguration
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Tree_Node* configuration
  );

Arcadia_DataDefinitionLanguage_Tree_MapNode*
Cfg_loadConfiguration
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_ENGINE_DEMO_CONFIGURATIONUTILITIES_H_INCLUDED
