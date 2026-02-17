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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPEKIND_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPEKIND_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

/// An enumeration of the type kinds.
typedef enum Arcadia_TypeKind {

  /// The "enumeration" type kind.
  Arcadia_TypeKind_Enumeration,

  /// The "interface" type kind.
  Arcadia_TypeKind_Interface,

  /// The "internal" type kind.
  /// Examples of this type kind are
  /// - <code>Arcadia.Atom</code>
  /// - <code>Arcadia.ImmutableByteArray</code>
  /// - <code>Arcadia.Memory</code>
  /// - <code>Arcadia.Type</code>
  Arcadia_TypeKind_Internal,

  /// The "object" type kind.
  Arcadia_TypeKind_Object,

  /// The "scalar" type kind.
  /// Examples of this type are:
  /// - <code>Arcadia.Boolean</code>
  /// - <code>Arcadia.ForeignProcedure</code>
  /// - <code>Arcadia.Integer(8|16|32|64)</code>
  /// - <code>Arcadia.Natural(8|16|32|64)</code>
  /// - <code>Arcadia.Real(32|64)</code>
  /// - <code>Arcadia.Size</code>
  /// - <code>Arcadia.Void</code>
  Arcadia_TypeKind_Scalar,

} Arcadia_TypeKind;

#endif // ARCADIA_RING1_IMPLEMENTATION_TYPESYSTEM_TYPEKIND_H_INCLUDED
