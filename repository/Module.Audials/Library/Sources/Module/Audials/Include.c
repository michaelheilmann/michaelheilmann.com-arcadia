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
}

static const WORD BITSPERSAMPLE = 16;
static const DWORD SAMPLESPERSEC = 44100;
static const double CYCLESPERSEC = 220.0;
static const double VOLUME = 0.5;
static const WORD AUDIOBUFFERSIZEINCYCLES = 10;
static const double PI = 3.14159265358979323846;

#include <math.h>

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
  R_ByteBuffer* buffer = R_ByteBuffer_create();
  double phase = 0.0;
  uint32_t bufferIndex = 0;
  while (bufferIndex < AUDIOBUFFERSIZEINBYTES) {
    phase += (2 * PI) / SAMPLESPERCYCLE;
    int16_t sample = (int16_t)(sin(phase) * INT16_MAX * VOLUME);
    uint8_t bytes[2] = { (uint8_t)(sample >> 0), (uint8_t)(sample >> 8) };
    R_ByteBuffer_append_pn(buffer, bytes, 2);
    bufferIndex += 2;
  }

  XAUDIO2_BUFFER xAudio2Buffer;
  xAudio2Buffer.Flags = XAUDIO2_END_OF_STREAM;
  xAudio2Buffer.AudioBytes = AUDIOBUFFERSIZEINBYTES;
  xAudio2Buffer.pAudioData = R_ByteBuffer_getBytes(buffer);
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
