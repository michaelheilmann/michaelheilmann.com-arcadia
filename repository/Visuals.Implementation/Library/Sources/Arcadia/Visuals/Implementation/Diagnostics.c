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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Implementation/Diagnostics.h"

#include "Arcadia/Visuals/Implementation/Include.h"

static inline void
Arcadia_Visuals_Diagnostics_dumpDeviceBounds
  (
    Arcadia_Thread* thread,
    Arcadia_Log* log,
    Arcadia_Visuals_DisplayDevice* device
  )
{
  Arcadia_Integer32Value left, top, right, bottom;
  Arcadia_Visuals_DisplayDevice_getBounds(thread, device, &left, &top, &right, &bottom);
  
  Arcadia_StringBuffer* message = Arcadia_StringBuffer_create(thread);
  
  Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"    bounds:");
  
  Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"\n     left: ");
  Arcadia_StringBuffer_insertBackString(thread, message, Arcadia_String_createFromInteger32(thread, left));
  
  Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"\n     top: ");
  Arcadia_StringBuffer_insertBackString(thread, message, Arcadia_String_createFromInteger32(thread, top));
  
  Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"\n     right: ");
  Arcadia_StringBuffer_insertBackString(thread, message, Arcadia_String_createFromInteger32(thread, right));
  
  Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"\n     bottom: ");
  Arcadia_StringBuffer_insertBackString(thread, message, Arcadia_String_createFromInteger32(thread, bottom));
  
  Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"\n");
  Arcadia_Log_info(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(message)));
}

static inline void
Arcadia_Visuals_Diagnostics_dumpModes
  (
    Arcadia_Thread* thread,
    Arcadia_Log* log,
    Arcadia_Visuals_DisplayDevice* device
  )
{
  Arcadia_StringBuffer* message = Arcadia_StringBuffer_create(thread);
  Arcadia_String* a;
  
  Arcadia_List* modes = Arcadia_Visuals_DisplayDevice_getAvailableDisplayModes(thread, device);
  
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)modes); i < n; ++i) {
    Arcadia_Visuals_DisplayMode* mode =
      (Arcadia_Visuals_DisplayMode*)Arcadia_List_getObjectReferenceValueAt(thread, modes, i);
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"     ");
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"horizontal resolution: ");
    
    a = Arcadia_String_createFromInteger32(thread, Arcadia_Visuals_DisplayMode_getHorizontalResolution(thread, mode));
    Arcadia_StringBuffer_insertBackString(thread, message, a);
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"vertical resolution: ");
    
    a = Arcadia_String_createFromInteger32(thread, Arcadia_Visuals_DisplayMode_getVerticalResolution(thread, mode));
    Arcadia_StringBuffer_insertBackString(thread, message, a);
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8", color depth: ");
    
    a = Arcadia_String_createFromInteger32(thread, Arcadia_Visuals_DisplayMode_getColorDepth(thread, mode));
    Arcadia_StringBuffer_insertBackString(thread, message, a);
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8", frequency: ");
    
    a = Arcadia_String_createFromInteger32(thread, Arcadia_Visuals_DisplayMode_getFrequency(thread, mode));
    Arcadia_StringBuffer_insertBackString(thread, message, a);
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"\n");
  }
  Arcadia_Log_info(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(message)));
}

void
Arcadia_Visuals_Diagnostics_dumpDevices
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_StringBuffer* message = Arcadia_StringBuffer_create(thread);
  Arcadia_Log* log = Arcadia_Log_create(thread);
  
#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  Arcadia_Visuals_Application* application = (Arcadia_Visuals_Application*)Arcadia_Visuals_Windows_Application_getOrCreate(thread);
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  Arcadia_Visuals_Application* application = (Arcadia_Visuals_Application*)Arcadia_Visuals_Linux_Application_getOrCreate(thread);
#else
  #error("environment system not (yet) supported")
#endif
  Arcadia_List* displayDevices = Arcadia_Visuals_Application_getDisplayDevices(thread, application);
  
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)displayDevices); i < n; ++i) {   
    Arcadia_Visuals_DisplayDevice* displayDevice =
      (Arcadia_Visuals_DisplayDevice*)Arcadia_List_getObjectReferenceValueAt(thread, displayDevices, i);
    
    Arcadia_String* a;

    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"  ");
    
    a = Arcadia_String_createFromSize(thread, i);
    Arcadia_StringBuffer_insertBackString(thread, message, a);
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8") id: ");

    a = Arcadia_Visuals_DisplayDevice_getId(thread, displayDevice);
    Arcadia_StringBuffer_insertBackString(thread, message, a);
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8", name: ");
    
    a = Arcadia_Visuals_DisplayDevice_getName(thread, displayDevice);
    Arcadia_StringBuffer_insertBackString(thread, message, a);
    
    Arcadia_StringBuffer_insertBackCxxString(thread, message, u8"\n");
    
    Arcadia_Log_info(thread, log, Arcadia_String_create(thread, Arcadia_Value_makeObjectReferenceValue(message)));
    Arcadia_StringBuffer_clear(thread, message);

    Arcadia_Visuals_Diagnostics_dumpModes(thread, log, displayDevice);
    Arcadia_Visuals_Diagnostics_dumpDeviceBounds(thread, log, displayDevice);
  }
}
