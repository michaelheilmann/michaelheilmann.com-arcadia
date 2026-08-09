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

#if !defined(ARCADIA_MILC_BACKEND_SYMBOLINFO_H_INCLUDED)
#define ARCADIA_MILC_BACKEND_SYMBOLINFO_H_INCLUDED

#include "Arcadia/MILC/Context.h"
#include "Arcadia/MILC/Symbols/Include.h"

/// @brief Additional information for a symbol.
/// Used by the C backend.
Arcadia_declareObjectType(u8"Arcadia.MILC.Backend.SymbolInfo", Arcadia_MILC_Backend_SymbolInfo,
                          u8"Arcadia.Object");

struct Arcadia_MILC_Backend_SymbolInfoDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_Backend_SymbolInfo {
  Arcadia_Object _parent;
  /// @brief The symbol.
  Arcadia_MILC_Symbol* symbol;
  Arcadia_FilePath* moduleDirectoryPath;
  /// @brief The module'd library source directory path.
  /// This is usually <module name>/Library/Sources.
  Arcadia_FilePath* cxxFilesPath;
  /// @brief The path to the Cxx source file.
  /// This is usually `<module name>/Library/Sources/(<name>/)+<name>.c`.
  Arcadia_FilePath* cxxSourceFilePath;
  /// @brief The path to the Cxx header file.
  /// This is usually `<module name>/Library/Sources/(<name>/)+<name>.h`.
  Arcadia_FilePath* cxxHeaderFilePath;
  /// @brief The fully-qualified C name.
  Arcadia_String* cxxName;
  /// @brief The fully-qualified C name in uppercase.
  Arcadia_String* cxxNameUpperCase;
};

Arcadia_MILC_Backend_SymbolInfo*
Arcadia_MILC_Backend_SymbolInfo_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  );

void
Arcadia_MILC_Backend_SymbolInfo_dump
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self,
    Arcadia_SizeValue indent,
    Arcadia_StringBuilder* target
  );

#endif // ARCADIA_MILC_BACKEND_SYMBOLINFO_H_INCLUDED
