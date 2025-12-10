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

#if !defined(ARCADIA_ARMS_CONFIGURE_H_INCLUDED)
#define ARCADIA_ARMS_CONFIGURE_H_INCLUDED



// Define to 1 to enable the "locks" module.
#define Arcadia_ARMS_Configuration_WithLocks (1)

// Define to 1 to enable the "barriers" module.
#define Arcadia_ARMS_Configuration_WithBarriers (1)

// Define to 1 to enable the "notify destroy" module.
#define Arcadia_ARMS_Configuration_WithNotifyDestroy (1)

// Define to 1 to enable the "names" module.
#define Arcadia_ARMS_Configuration_WithNames (1)



#define Arcadia_ARMS_Configuration_InstructionSetArchitecture_Unknown @Arcadia.ARMS.InstructionSetArchitecture.Unknown@
#define Arcadia_ARMS_Configuration_InstructionSetArchitecture_X86 @Arcadia.ARMS.InstructionSetArchitecture.X86@
#define Arcadia_ARMS_Configuration_InstructionSetArchitecture_X64 @Arcadia.ARMS.InstructionSetArchitecture.X64@

#define Arcadia_ARMS_Configuration_InstructionSetArchitecture @Arcadia.ARMS.InstructionSetArchitecture@



#define Arcadia_ARMS_Configuration_OperatingSystem_Unknown @Arcadia.ARMS.OperatingSystem.Unknown@
#define Arcadia_ARMS_Configuration_OperatingSystem_Cygwin @Arcadia.ARMS.OperatingSystem.Cygwin@
#define Arcadia_ARMS_Configuration_OperatingSystem_Ios @Arcadia.ARMS.OperatingSystem.Ios@
#define Arcadia_ARMS_Configuration_OperatingSystem_IosSimulator @Arcadia.ARMS.OperatingSystem.IosSimulator@
#define Arcadia_ARMS_Configuration_OperatingSystem_Linux @Arcadia.ARMS.OperatingSystem.Linux@
#define Arcadia_ARMS_Configuration_OperatingSystem_Macos @Arcadia.ARMS.OperatingSystem.Macos@
#define Arcadia_ARMS_Configuration_OperatingSystem_Mingw @Arcadia.ARMS.OperatingSystem.Mingw@
#define Arcadia_ARMS_Configuration_OperatingSystem_Msys @Arcadia.ARMS.OperatingSystem.Msys@
#define Arcadia_ARMS_Configuration_OperatingSystem_Unix @Arcadia.ARMS.OperatingSystem.Unix@
#define Arcadia_ARMS_Configuration_OperatingSystem_Windows @Arcadia.ARMS.OperatingSystem.Windows@

#define Arcadia_ARMS_Configuration_OperatingSystem @Arcadia.ARMS.OperatingSystem@



#define Arcadia_ARMS_Configuration_CompilerC_Unknown @Arcadia.ARMS.Compiler.C.Unknown@
#define Arcadia_ARMS_Configuration_CompilerC_Clang @Arcadia.ARMS.Compiler.C.Clang@
#define Arcadia_ARMS_Configuration_CompilerC_Gcc @Arcadia.ARMS.Compiler.C.Gcc@
#define Arcadia_ARMS_Configuration_CompilerC_Msvc @Arcadia.ARMS.Compiler.C.Msvc@

#define Arcadia_ARMS_Configuration_CompilerC @Arcadia.ARMS.Compiler.C@



#define Arcadia_ARMS_Configuration_ByteOrder_Unknown @Arcadia.ARMS.ByteOrder.Unknown@
#define Arcadia_ARMS_Configuration_ByteOrder_BigEndian @Arcadia.ARMS.ByteOrder.BigEndian@
#define Arcadia_ARMS_Configuration_ByteOrder_LittleEndian @Arcadia.ARMS.ByteOrder.LittleEndian@

#define Arcadia_ARMS_Configuration_ByteOrder @Arcadia.ARMS.ByteOrder@



#endif // ARCADIA_ARMS_CONFIGURE_H_INCLUDED
