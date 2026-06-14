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

#if !defined(ARCADIA_TEMPLATEENGINE_SCANNER_SCANNER_H_INCLUDED)
#define ARCADIA_TEMPLATEENGINE_SCANNER_SCANNER_H_INCLUDED

#include "Arcadia/Languages/Include.h"
#include "Arcadia.Tools.TemplateEngine.Library/Scanner/WordType.h"

Arcadia_declareObjectType(u8"Arcadia.TemplateEngine.Scanner", Arcadia_TemplateEngine_Scanner,
                          u8"Arcadia.Languages.Scanner");

struct Arcadia_TemplateEngine_ScannerDispatch {
  Arcadia_Languages_ScannerDispatch _parent;
};

struct Arcadia_TemplateEngine_Scanner {
  Arcadia_Languages_Scanner _parent;

  /// @brief @a true the scanner is in text mode.
  /// @a false the scanner is in directive mode.
  bool textMode;

  /// @brief The diagnostics used by this scanner.
  Arcadia_Languages_Diagnostics* diagnostics;

  /// @brief The string table used by this scanner.
  Arcadia_Languages_StringTable* stringTable;

  // The file.
  Arcadia_String* file;
  // The line.
  Arcadia_Natural64Value line;
  // The reader.
  Arcadia_UnicodeCodePointReader* reader;

  Arcadia_TemplateEngine_WordType wordType;
  // Scanner: Writer to word text buffer.
  Arcadia_Unicode_Encoder* temporary;
  // Scanner: Word text buffer.
  Arcadia_ByteArrayBuilder* temporaryBuffer;
};

Arcadia_TemplateEngine_Scanner*
Arcadia_TemplateEngine_Scanner_create
  (
    Arcadia_Thread* thread,
	  Arcadia_String* file,
	  Arcadia_Natural64Value line,
    Arcadia_UnicodeCodePointReader* reader
  );

void
Arcadia_TemplateEngine_Scanner_setPosition
  (
    Arcadia_Thread* thread,
    Arcadia_TemplateEngine_Scanner* self,
    Arcadia_String* file,
    Arcadia_Natural64Value line
  );

#endif // ARCADIA_TEMPLATEENGINE_SCANNER_SCANNER_H_INCLUDED
