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



// Define to 1 to enable locks.
#define Arcadia_Arms_Configuration_WithLocks (1)



#define Arcadia_Arms_Configuration_InstructionSetArchitecture_Unknown @Arcadia.Arms.InstructionSetArchitecture.Unknown@
#define Arcadia_Arms_Configuration_InstructionSetArchitecture_X86 @Arcadia.Arms.InstructionSetArchitecture.X86@
#define Arcadia_Arms_Configuration_InstructionSetArchitecture_X64 @Arcadia.Arms.InstructionSetArchitecture.X64@

#define Arcadia_Arms_Configuration_InstructionSetArchitecture @Arcadia.Arms.InstructionSetArchitecture@



#define Arcadia_Arms_Configuration_OperatingSystem_Unknown @Arcadia.Arms.OperatingSystem.Unknown@
#define Arcadia_Arms_Configuration_OperatingSystem_Cygwin @Arcadia.Arms.OperatingSystem.Cygwin@
#define Arcadia_Arms_Configuration_OperatingSystem_Ios @Arcadia.Arms.OperatingSystem.Ios@
#define Arcadia_Arms_Configuration_OperatingSystem_IosSimulator @Arcadia.Arms.OperatingSystem.IosSimulator@
#define Arcadia_Arms_Configuration_OperatingSystem_Linux @Arcadia.Arms.OperatingSystem.Linux@
#define Arcadia_Arms_Configuration_OperatingSystem_Macos @Arcadia.Arms.OperatingSystem.Macos@
#define Arcadia_Arms_Configuration_OperatingSystem_Mingw @Arcadia.Arms.OperatingSystem.Mingw@
#define Arcadia_Arms_Configuration_OperatingSystem_Msys @Arcadia.Arms.OperatingSystem.Msys@
#define Arcadia_Arms_Configuration_OperatingSystem_Unix @Arcadia.Arms.OperatingSystem.Unix@
#define Arcadia_Arms_Configuration_OperatingSystem_Windows @Arcadia.Arms.OperatingSystem.Windows@

#define Arcadia_Arms_Configuration_OperatingSystem @Arcadia.Arms.OperatingSystem@



#define Arms_Configuration_CompilerC_Unknown @Arcadia.Arms.Compiler.C.Unknown@
#define Arms_Configuration_CompilerC_Clang @Arcadia.Arms.Compiler.C.Clang@
#define Arms_Configuration_CompilerC_Gcc @Arcadia.Arms.Compiler.C.Gcc@
#define Arms_Configuration_CompilerC_Msvc @Arcadia.Arms.Compiler.C.Msvc@

#define Arms_Configuration_CompilerC @Arcadia.Arms.Compiler.C@



#define Arcadia_Configuration_ByteOrder_Unknown @Arcadia.Arms.ByteOrder.Unknown@
#define Arcadia_Configuration_ByteOrder_BigEndian @Arcadia.Arms.ByteOrder.BigEndian@
#define Arcadia_Configuration_ByteOrder_LittleEndian @Arcadia.Arms.ByteOrder.LittleEndian@

#define Arcadia_Configuration_ByteOrder @Arcadia.Arms.ByteOrder@



#endif // ARCADIA_ARMS_CONFIGURE_H_INCLUDED
