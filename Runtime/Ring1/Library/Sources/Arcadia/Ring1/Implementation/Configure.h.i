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

#if !defined(ARCADIA_RING1_IMPLEMENTATION_CONFIGURE_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_CONFIGURE_H_INCLUDED



#define Arcadia_Configuration_InstructionSetArchitecture_Unknown @Arcadia.Ring1_InstructionSetArchitecture_Unknown@
#define Arcadia_Configuration_InstructionSetArchitecture_X86 @Arcadia.Ring1_InstructionSetArchitecture_X86@
#define Arcadia_Configuration_InstructionSetArchitecture_X64 @Arcadia.Ring1_InstructionSetArchitecture_X64@

#define Arcadia_Configuration_InstructionSetArchitecture @Arcadia.Ring1_InstructionSetArchitecture@



#define Arcadia_Configuration_OperatingSystem_Unknown @Arcadia.Ring1_OperatingSystem_Unknown@
#define Arcadia_Configuration_OperatingSystem_Cygwin @Arcadia.Ring1_OperatingSystem_Cygwin@
#define Arcadia_Configuration_OperatingSystem_Ios @Arcadia.Ring1_OperatingSystem_IOS@
#define Arcadia_Configuration_OperatingSystem_IosSimulator @Arcadia.Ring1_OperatingSystem_IOSSimulator@
#define Arcadia_Configuration_OperatingSystem_Linux @Arcadia.Ring1_OperatingSystem_Linux@
#define Arcadia_Configuration_OperatingSystem_Macos @Arcadia.Ring1_OperatingSystem_MacOS@
#define Arcadia_Configuration_OperatingSystem_Mingw @Arcadia.Ring1_OperatingSystem_MinGW@
#define Arcadia_Configuration_OperatingSystem_Msys @Arcadia.Ring1_OperatingSystem_MSYS@
#define Arcadia_Configuration_OperatingSystem_Unix @Arcadia.Ring1_OperatingSystem_Unix@
#define Arcadia_Configuration_OperatingSystem_Windows @Arcadia.Ring1_OperatingSystem_Windows@

#define Arcadia_Configuration_OperatingSystem @Arcadia.Ring1_OperatingSystem@



#define Arcadia_Configuration_CompilerC_Unknown @Arcadia.Ring1_Compiler_C_Unknown@
#define Arcadia_Configuration_CompilerC_Clang @Arcadia.Ring1_Compiler_C_Clang@
#define Arcadia_Configuration_CompilerC_Gcc @Arcadia.Ring1_Compiler_C_GCC@
#define Arcadia_Configuration_CompilerC_Msvc @Arcadia.Ring1_Compiler_C_MSVC@

#define Arcadia_Configuration_CompilerC @Arcadia.Ring1_Compiler_C@



#define Arcadia_Configuration_Version_Major 0
#define Arcadia_Configuration_Version_Minor 1



#define Arcadia_Configuration_ByteOrder_Unknown @Arcadia.Ring1_ByteOrder_Unknown@
#define Arcadia_Configuration_ByteOrder_BigEndian @Arcadia.Ring1_ByteOrder_BigEndian@
#define Arcadia_Configuration_ByteOrder_LittleEndian @Arcadia.Ring1_ByteOrder_LittleEndian@

#define Arcadia_Configuration_ByteOrder @Arcadia.Ring1_ByteOrder@



// If the C language supports binary literals.
#define Arcadia_Configuration_C_HasBinaryLiterals (1)



// The size, in Bytes, of a limp.
#define Arcadia_Configuration_BigInteger_LimpSize 4
// Least significand at lowest array index, most significand at highest array index.
#define Arcadia_Configuration_BigInteger_LimpOrder_LittleEndian (1)
// Most significand at lowest array index, least significand at highest array index.
#define Arcadia_Configuration_BigInteger_LimpOrder_BigEndian (2)

// The limp order used by the big integer implementation is little endian.
#define Arcadia_Configuration_BigInteger_LimpOrder Arcadia_Configuration_BigInteger_LimpOrder_LittleEndian



#endif // ARCADIA_RING1_IMPLEMENTATION_CONFIGURE_H_INCLUDED
