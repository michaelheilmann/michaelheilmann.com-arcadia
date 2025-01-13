// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-11-13

#include "Module/Audials/Include.h"

#include <objbase.h>
#include <xaudio2.h>

static IXAudio2* g_xaudio2 = NULL;
static IXAudio2MasteringVoice* g_xaudio2MasteringVoice = NULL;

static R_ByteBuffer* g_sourceVoiceBuffer = NULL;
static IXAudio2SourceVoice* g_xaudio2SourceVoice = NULL;

static void
Audials_XAudio2_startup
  (
    Arcadia_Process* process
  )
{
  HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  hr = XAudio2Create(&g_xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
  if (FAILED(hr)) {
    CoUninitialize();
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  hr = IXAudio2_CreateMasteringVoice(g_xaudio2, &g_xaudio2MasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL, AudioCategory_Other);
  if (FAILED(hr)) {
    IXAudio2_Release(g_xaudio2);
    g_xaudio2 = NULL;
    CoUninitialize();
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  Arcadia_JumpTarget jumpTarget;

  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    g_sourceVoiceBuffer = R_ByteBuffer_create(process);
    Arcadia_Process_popJumpTarget(process);
  } else {
    Arcadia_Process_popJumpTarget(process);
    IXAudio2_Release(g_xaudio2);
    g_xaudio2 = NULL;
    CoUninitialize();
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }

  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_Object_lock(process, g_sourceVoiceBuffer);
    Arcadia_Process_popJumpTarget(process);
  } else {
    Arcadia_Process_popJumpTarget(process);
    IXAudio2_Release(g_xaudio2);
    g_xaudio2 = NULL;
    CoUninitialize();
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
}

static void
Audials_XAudio2_shutdown
  (
    Arcadia_Process* process
  )
{
  if (g_xaudio2SourceVoice) {
    g_xaudio2SourceVoice = NULL;
  }
  if (g_xaudio2MasteringVoice) {
    g_xaudio2MasteringVoice = NULL; 
  }
  IXAudio2_Release(g_xaudio2);
  g_xaudio2 = NULL;
  CoUninitialize();
  Arcadia_Object_unlock(process, g_sourceVoiceBuffer);
  g_sourceVoiceBuffer = NULL;
}

static const WORD BITSPERSAMPLE = 16;
static const DWORD SAMPLESPERSEC = 44100;
static const double CYCLESPERSEC = 220.0;
static const double VOLUME = 0.5;
static const WORD AUDIOBUFFERSIZEINCYCLES = 10;
static const double PI = 3.14159265358979323846;

#include <math.h>

Rex_declareObjectType(u8"Audials.Xaudio2.Source", Source, u8"Arcadia.Object");

struct Source {
  Arcadia_Object _parent;
  struct Source* next;
  /// The backing source voice.
  IXAudio2SourceVoice* xAudio2SourceVoice;
};

static void
Source_destruct
  (
    Arcadia_Process* process,
    Source* self
  )
{ 
  if (self->xAudio2SourceVoice) {
    // Stop the voice. Remove the voice from the XAudio2 graph.
    IXAudio2Voice_DestroyVoice(self->xAudio2SourceVoice);
    self->xAudio2SourceVoice = NULL;
  }
}

static void
Source_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Source_constructImpl,
  .destruct = &Source_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"Audials.Xaudio2.Source", Source, u8"Arcadia.Object", Arcadia_Object, &_typeOperations)

// bytes : ByteBuffer
static void
Source_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Source* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Source_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Value_isObjectReferenceValue(&argumentValues[0])) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Object* objectValue = Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
  if (!Arcadia_Type_isSubType(Arcadia_Object_getType(objectValue), _R_ByteBuffer_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  //R_ByteBuffer* byteBufferValue = (R_ByteBuffer*)objectValue;
  _self->xAudio2SourceVoice = NULL;
  Arcadia_Object_setType(process, _self, _type);
}

void
Source_notifyBackendShuttingDown
  (
    Source* self
  )
{
  if (self->xAudio2SourceVoice) {
    // Stop the voice. Remove the voice from the XAudio2 graph.
    IXAudio2Voice_DestroyVoice(self->xAudio2SourceVoice);
    self->xAudio2SourceVoice = NULL;
  }
}

Source*
Source_create
  (
    Arcadia_Process* process,
    R_ByteBuffer* bytes
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)bytes } };
  Source* self = R_allocateObject(process, _Source_getType(process), 1, &argumentValues[0]);
  return self;
}

void
Audials_playSine1
  (
    Arcadia_Process* process
  )
{
  const DWORD SAMPLESPERCYCLE = (DWORD)(SAMPLESPERSEC / CYCLESPERSEC);                // 200 samples per cycle.
  const DWORD  AUDIOBUFFERSIZEINSAMPLES = SAMPLESPERCYCLE * AUDIOBUFFERSIZEINCYCLES;  // 2,000 samples per buffer.
  const UINT32 AUDIOBUFFERSIZEINBYTES = AUDIOBUFFERSIZEINSAMPLES * BITSPERSAMPLE / 8; // 4,000 bytes per buffer.

  // Define a format.
  WAVEFORMATEX waveFormatEx;
  waveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
  waveFormatEx.nChannels = 1; // 1 channel
  waveFormatEx.nSamplesPerSec = SAMPLESPERSEC;
  waveFormatEx.nBlockAlign = waveFormatEx.nChannels * BITSPERSAMPLE / 8;
  waveFormatEx.nAvgBytesPerSec = waveFormatEx.nSamplesPerSec * waveFormatEx.nBlockAlign;
  waveFormatEx.wBitsPerSample = BITSPERSAMPLE;
  waveFormatEx.cbSize = 0;

  HRESULT hr = IXAudio2_CreateSourceVoice(g_xaudio2, &g_xaudio2SourceVoice, &waveFormatEx, 0, 1.0, NULL, NULL, NULL);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  double phase = 0.0;
  uint32_t bufferIndex = 0;
  while (bufferIndex < AUDIOBUFFERSIZEINBYTES) {
    phase += (2 * PI) / SAMPLESPERCYCLE;
    int16_t sample = (int16_t)(sin(phase) * INT16_MAX * VOLUME);
    uint8_t bytes[2] = { (uint8_t)(sample >> 0), (uint8_t)(sample >> 8) };
    R_ByteBuffer_append_pn(process, g_sourceVoiceBuffer, bytes, 2);
    bufferIndex += 2;
  }

  XAUDIO2_BUFFER xAudio2Buffer;
  xAudio2Buffer.Flags = XAUDIO2_END_OF_STREAM;
  xAudio2Buffer.AudioBytes = AUDIOBUFFERSIZEINBYTES;
  xAudio2Buffer.pAudioData = R_ByteBuffer_getBytes(g_sourceVoiceBuffer);
  xAudio2Buffer.PlayBegin = 0;
  xAudio2Buffer.PlayLength = 0;
  xAudio2Buffer.LoopBegin = 0;
  xAudio2Buffer.LoopLength = 0;
  xAudio2Buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

  hr = IXAudio2SourceVoice_SubmitSourceBuffer(g_xaudio2SourceVoice, &xAudio2Buffer, NULL);
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  hr = IXAudio2SourceVoice_Start(g_xaudio2SourceVoice, UINT32_C(0), UINT32_C(0));
  if (FAILED(hr)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
}

void
Audials_playSine
  (
    Arcadia_Process* process
  )
{
  Audials_playSine1(process);
}

void
Audials_startup
  (
    Arcadia_Process* process
  )
{
  Audials_XAudio2_startup(process);
}

void
Audials_shutdown
  (
    Arcadia_Process* process
  )
{
  Audials_XAudio2_shutdown(process);
}
