// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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
  )
{
  HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  hr = XAudio2Create(&g_xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
  if (FAILED(hr)) {
    CoUninitialize();
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  hr = IXAudio2_CreateMasteringVoice(g_xaudio2, &g_xaudio2MasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL, AudioCategory_Other);
  if (FAILED(hr)) {
    IXAudio2_Release(g_xaudio2);
    g_xaudio2 = NULL;
    CoUninitialize();
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  R_JumpTarget jumpTarget;

  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    g_sourceVoiceBuffer = R_ByteBuffer_create();
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    IXAudio2_Release(g_xaudio2);
    g_xaudio2 = NULL;
    CoUninitialize();
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }

  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_Object_lock(g_sourceVoiceBuffer);
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    IXAudio2_Release(g_xaudio2);
    g_xaudio2 = NULL;
    CoUninitialize();
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
}

static void
Audials_XAudio2_shutdown
  (
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
  R_Object_unlock(g_sourceVoiceBuffer);
  g_sourceVoiceBuffer = NULL;
}

static const WORD BITSPERSAMPLE = 16;
static const DWORD SAMPLESPERSEC = 44100;
static const double CYCLESPERSEC = 220.0;
static const double VOLUME = 0.5;
static const WORD AUDIOBUFFERSIZEINCYCLES = 10;
static const double PI = 3.14159265358979323846;

#include <math.h>

Rex_declareObjectType("Audials.Xaudio2.Source", Source, "R.Object");

struct Source {
  R_Object _parent;
  struct Source* next;
  /// The backing source voice.
  IXAudio2SourceVoice* xAudio2SourceVoice;
};

static void
Source_destruct
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

static void
Source_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &Source_constructImpl,
  .destruct = &Source_destruct,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("Audials.Xaudio2.Source", Source, "R.Object", R_Object, &_typeOperations)

// bytes : ByteBuffer
static void
Source_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  Source* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _Source_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  if (!R_Value_isObjectReferenceValue(&argumentValues[0])) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object* objectValue = R_Value_getObjectReferenceValue(&argumentValues[0]);
  if (!R_Type_isSubType(R_Object_getType(objectValue), _R_ByteBuffer_getType())) {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  //R_ByteBuffer* byteBufferValue = (R_ByteBuffer*)objectValue;
  _self->xAudio2SourceVoice = NULL;
  R_Object_setType((R_Object*)_self, _type);
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
    R_ByteBuffer* bytes
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)bytes } };
  Source* self = R_allocateObject(_Source_getType(), 1, &argumentValues[0]);
  R_Value selfValue = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)self };
  Source_constructImpl(&selfValue, 1, &argumentValues[0]);
  return self;
}

void
Audials_playSine1
  (
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
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  double phase = 0.0;
  uint32_t bufferIndex = 0;
  while (bufferIndex < AUDIOBUFFERSIZEINBYTES) {
    phase += (2 * PI) / SAMPLESPERCYCLE;
    int16_t sample = (int16_t)(sin(phase) * INT16_MAX * VOLUME);
    uint8_t bytes[2] = { (uint8_t)(sample >> 0), (uint8_t)(sample >> 8) };
    R_ByteBuffer_append_pn(g_sourceVoiceBuffer, bytes, 2);
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
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  hr = IXAudio2SourceVoice_Start(g_xaudio2SourceVoice, UINT32_C(0), UINT32_C(0));
  if (FAILED(hr)) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
}

void
Audials_playSine
  (
  )
{
  Audials_playSine1();
}

void
Audials_startup
  (
  )
{
  Audials_XAudio2_startup();
}

void
Audials_shutdown
  (
  )
{
  Audials_XAudio2_shutdown();
}
