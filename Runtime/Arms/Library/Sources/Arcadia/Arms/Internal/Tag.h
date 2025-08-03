#if !defined(ARMS_TAG_H_INCLUDED)
#define ARMS_TAG_H_INCLUDED

#include "Arcadia/Arms/Internal/Common.h"
#include <stdbool.h> // bool, true, false
#include <inttypes.h> // uint8_t
typedef struct Arms_Type Arms_Type; // Forward declaration.

#define Arms_TagFlags_White (1)
#define Arms_TagFlags_Black (2)
#define Arms_TagFlags_Gray (Arms_TagFlags_White|Arms_TagFlags_Black)

typedef struct Arms_Tag Arms_Tag;

#if Arcadia_Arms_Configuration_InstructionSetArchitecture_X64 == Arcadia_Arms_Configuration_InstructionSetArchitecture

  // We must make sure that this thing is 64 bit aligned.
  #if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Msvc
    #pragma pack(push, 8)
  #endif

#elif Arcadia_Arms_Configuration_InstructionSetArchitecture_X32 == Arcadia_Arms_Configuration_InstructionSetArchitecture

  // We must make sure that this thing is 32 bit aligned.
  #if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Msvc
    #pragma pack(push, 4)
  #endif

#endif

struct Arms_Tag {
  uint8_t flags;
  Arms_Type* type;
  Arms_Tag* universeNext;
  Arms_Tag* grayNext;
}
#if Arcadia_Arms_Configuration_InstructionSetArchitecture_X64 == Arcadia_Arms_Configuration_InstructionSetArchitecture
  // We must make sure that this thing is 64 bit aligned.
  #if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Gcc
    __attribute__((aligned(16)))
  #endif
#elif Arcadia_Arms_Configuration_InstructionSetArchitecture_X32 == Arcadia_Arms_Configuration_InstructionSetArchitecture
  // We must make sure that this thing is 32 bit aligned.
  #if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Gcc
    __attribute__((aligned(16)))
  #endif
#endif
;

#if Arms_Configuration_CompilerC == Arms_Configuration_CompilerC_Msvc
  #pragma pack(pop)
#endif

#if Arcadia_Arms_Configuration_InstructionSetArchitecture_X64 == Arcadia_Arms_Configuration_InstructionSetArchitecture
  Cxx_staticAssert(sizeof(Arms_Tag) % 8 == 0, "Arms_Tag size not 8 Byte aligned");
#elif Arcadia_Arms_Configuration_InstructionSetArchitecture_X32 == Arcadia_Arms_Configuration_InstructionSetArchitecture
  Cxx_staticAssert(sizeof(Arms_Tag) % 4 == 0, "Arms_Tag size not 4 Byte aligned");
#endif

static inline bool
Arms_Tag_isWhite
  (
    Arms_Tag const* tag
  )
{ return Arms_TagFlags_White == (tag->flags & Arms_TagFlags_Gray); }

static inline void
Arms_Tag_setWhite
  (
    Arms_Tag* tag
  )
{ tag->flags = (tag->flags & ~Arms_TagFlags_Black) | Arms_TagFlags_White;  }

static inline bool
Arms_Tag_isGray
  (
    Arms_Tag const* tag
  )
{ return Arms_TagFlags_Gray == (tag->flags & Arms_TagFlags_Gray); }

static inline void
Arms_Tag_setGray
  (
    Arms_Tag* tag
  )
{ tag->flags |= Arms_TagFlags_Gray; }

static inline bool
Arms_Tag_isBlack
  (
    Arms_Tag const* tag
  )
{ return Arms_TagFlags_Black == (tag->flags & Arms_TagFlags_Gray); }

static inline void
Arms_Tag_setBlack
  (
    Arms_Tag* tag
  )
{ tag->flags = (tag->flags & ~Arms_TagFlags_White) | Arms_TagFlags_Black; }

#endif // ARMS_TAG_H_INCLUDED
