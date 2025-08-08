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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_MODULE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_MODULE_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Annotations/NoReturn.h"

#if Arcadia_Configuration_CompilerC_Gcc == Arcadia_Configuration_CompilerC
#include <stddef.h>
#endif

#include "Arcadia/Ring1/Implementation/Process.h"

typedef struct Arcadia_JumpTarget Arcadia_JumpTarget; // Forward declaration.
typedef struct Arcadia_Thread Arcadia_Thread; // Forward declaration.
typedef struct Arcadia_Process Arcadia_Process; // Forward declaration.


typedef struct ModuleInfo {
  /// @brief Pointer to the name of the module. The name is a static constant C string.
  const char* name;
  /// @brief Visit the module.
  /// @warning Internal function.
  Arcadia_Process_VisitCallback* onVisit;
  /// @brief Startup the module.
  /// @warning Internal function.
  void (*onStartUp)(Arcadia_Thread* thread);
  /// @brief Shutdown the module.
  /// @warning Internal function.
  void (*onShutDown)(Arcadia_Thread* thread);
  /// @brief Must be invoked in the pre mark phase.
  /// @warning Internal function.
  Arcadia_Process_PreMarkCallback* onPreMark;
  /// @brief Must be invoked in the finalize phase.
  /// @warning Internal function.
  Arcadia_Process_FinalizeCallback* onFinalize;
} ModuleInfo;

#define Arcadia_DeclareModule(Name, cName) \
  const ModuleInfo* \
  cName##_getModule \
    ( \
    );

#define Arcadia_DefineModule(Name, cName) \
  static void \
  _##cName##_onStartUp \
    ( \
      Arcadia_Thread* thread \
    ); \
\
  static void \
  _##cName##_onShutDown \
    ( \
      Arcadia_Thread* thread \
    ); \
\
  static void \
  _##cName##_onPreMark \
    ( \
      Arcadia_Thread* thread, \
      bool purgeCache \
    ); \
\
  static void \
  _##cName##_onFinalize \
    ( \
      Arcadia_Thread* thread, \
      size_t* destroyed \
    ); \
\
  static void \
  _##cName##_onVisit \
    ( \
      Arcadia_Thread* thread \
    ); \
\
  static const ModuleInfo _##cName##_moduleInfo = { \
    .name = Name, \
    .onVisit = &_##cName##_onVisit, \
    .onStartUp = &_##cName##_onStartUp, \
    .onShutDown = &_##cName##_onShutDown, \
    .onPreMark = &_##cName##_onPreMark, \
    .onFinalize = &_##cName##_onFinalize, \
  }; \
\
  const ModuleInfo* \
  cName##_getModule \
    ( \
    ) \
  { return &_##cName##_moduleInfo; }

#endif // ARCADIA_RING1_IMPLEMENTATION_MODULE_H_INCLUDED
