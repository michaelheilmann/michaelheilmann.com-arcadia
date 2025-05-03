#if !defined(ARCADIA_VISUALS_CONFIGURATION_H_INCLUDED)
#define ARCADIA_VISUALS_CONFIGURATION_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

/// @code
/// class Arcadia.Visuals.Configuration extends Arcadia.Object {
///   construct()
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Visuals.Configuration", Arcadia_Visuals_Configuration, u8"Arcadia.Object")

struct Arcadia_Visuals_Configuration {
  Arcadia_Object _parent;
  struct {
    
    struct {
      
      /// Must be non-negative integer.
      /// Default: 4.
      Arcadia_String* major;
      
      /// Must be non-negative integer.
      /// Default: 3.
      Arcadia_String* minor;
      
    } version;
    
  } opengl;

  struct {
    
    /// Must be non-negative integer.
    /// Default: 24.
    Arcadia_String* depthBits;
    
  } depthBuffer;

  struct {
    
    /// Must be non-negative.
    /// Default: 8.
    Arcadia_String* redBits;
    
    /// Must be non-negative.
    /// Default: 8.
    Arcadia_String* greenBits;
    
    /// Must be non-negative.
    /// Default: 8.
    Arcadia_String* blueBits;
  
    /// Must be non-negative.
    /// Default: 8.
    Arcadia_String*  alphaBits;
  
  } colorBuffer;

};

Arcadia_Visuals_Configuration*
Arcadia_Visuals_Configuration_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_CONFIGURATION_H_INCLUDED
