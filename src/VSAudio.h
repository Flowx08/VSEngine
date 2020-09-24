//=======================================================================================
//								VIRUAL SHOCK ENGINE
//=======================================================================================
//
//     Copyright (c) 2013-2015 Carlo Meroni < meronicarlo98@gmail.com >
//
//     This software is provided 'as-is', without any express or implied warranty.
//     In no event will the authors be held liable for any damages arising from
//     the use of this software.
//
//     Permission is granted to anyone to use this software for any purpose,
//     including commercial applications, and to alter it and redistribute it freely,
//     subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented;
//        you must not claim that you wrote the original software.
//        If you use this software in a product, an acknowledgment
//        in the product documentation would be appreciated but is
//        not required.
//
//     2. Altered source versions must be plainly marked as such,
//        and must not be misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//        distribution.
//=======================================================================================

////////////////////////////////////////////////////////////
///	HEADER
////////////////////////////////////////////////////////////
#ifndef VS_AUDIO_H
#define VS_AUDIO_H

#ifdef __cplusplus
extern "C" {
#endif

// ================================
// ====>> OS
// ================================ 

// Identify the operating system
#if defined(_WIN32)
    //Windows
    #define VS_SYS_WINDOWS
#elif defined(__APPLE__)
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
        #define VS_SYS_IOS
    #elif TARGET_OS_IPHONE
        // iOS device
        #define VS_SYS_IOS
    #elif TARGET_OS_MAC
        //Mac
        #define VS_SYS_MAC
    #else
        //Error
        #error This operating system is not supported!
    #endif
    
#elif defined(__linux__)
    //Linux
    #define VS_SYS_LINUX
#else
    //Other systems
    #error This operating system is not supported!
#endif

//Define import / export macros
#if defined(VS_SYS_WINDOWS)

    #if defined(VSAUDIO_EXPORTS)
        #define VSAUDIO_API __declspec(dllexport)
    #else
        #define VSAUDIO_API __declspec(dllimport)
    #endif

#else

    #define VSAUDIO_API

#endif





// ================================
// ====>> MODULE MANAGER
// ================================

/*
 
 Modules:
	AUDIO
	LISTENER
	SOUNDBUFFER
	SOUND
 
 By default all moudules are exported.
 To export only one specific module, you should
 define VS_ONLY_$MODULE before including this file.
 
 Example:
    #define VS_ONLY_AUDIO
    #include "VSAudio.h"
 
 You can pick also multiple specific modules.
 
 Example:
    #define VS_ONLY_SOUNDBUFFER
    #define VS_ONLY_SOUND
    #include "VSAudio.h"
 
 If you want just the OS defines you should
 define VS_NO_EXPORT before including this file
 
 */
    
#if defined(VS_ONLY_AUDIO) || defined(VS_ONLY_LISTENER) || defined(VS_ONLY_SOUNDBUFFER)||\
    defined(VS_ONLY_SOUND)
    
#ifdef VS_ONLY_AUDIO
    #define VS_EXPORT_AUDIO
#endif
    
#ifdef VS_ONLY_LISTENER
    #define VS_EXPORT_LISTENER
#endif
    
#ifdef VS_ONLY_SOUNDBUFFER
    #define VS_EXPORT_SOUNDBUFFER
#endif
    
#ifdef VS_ONLY_SOUND
    #define VS_EXPORT_SOUND
#endif
    
#else
    
    //Define all modules
    #define VS_EXPORT_AUDIO
    #define VS_EXPORT_LISTENER
    #define VS_EXPORT_SOUNDBUFFER
    #define VS_EXPORT_SOUND
    
#endif
    
#if defined(VS_NO_EXPORT)
    
    //Undefine all modules
    #undef VS_EXPORT_AUDIO
    #undef VS_EXPORT_LISTENER
    #undef VS_EXPORT_SOUNDBUFFER
    #undef VS_EXPORT_SOUND
    
#endif

#if defined(VS_AUDIO_IMPLEMENTATION)
    
    //Undefine all modules
    #undef VS_EXPORT_AUDIO
    #undef VS_EXPORT_LISTENER
    #undef VS_EXPORT_SOUNDBUFFER
    #undef VS_EXPORT_SOUND
    
#endif



// ================================
// ====>> CONSTANTS
// ================================ 

#define VSA_STOPPED     0
#define VSA_PAUSED      1
#define VSA_PLAYING     2




#ifdef VS_EXPORT_AUDIO

// ================================
// ====>> AUDIO
// ================================

////////////////////////////////////////////////////////////
/// \brief Initialize
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsAudioInit();

////////////////////////////////////////////////////////////
/// \brief Destroy
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsAudioDestroy();

#endif // VS_EXPORT_AUDIO




#ifdef VS_EXPORT_LISTENER

// ================================
// ====>> LISTENER
// ================================

////////////////////////////////////////////////////////////
/// \brief Set the global volume that effect all the sounds.
/// The volume is a value between 0 and 1.
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsListenerSetGlobalVolume(const float volume);

////////////////////////////////////////////////////////////
/// \brief Set the position of the listener
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsListenerSetPosition(const float x, const float y, const float z);

////////////////////////////////////////////////////////////
/// \brief Set the listener direction
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsListenerSetDirection(const float x, const float y, const float z);

////////////////////////////////////////////////////////////
/// \brief Get the global volume
///
////////////////////////////////////////////////////////////
VSAUDIO_API float vsListenerGetGlobalVolume();

////////////////////////////////////////////////////////////
/// \brief Get the position of the listener
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsListenerGetPosition(float *x, float *y, float *z);

////////////////////////////////////////////////////////////
/// \brief Get the listener direction
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsListenerGetDirection(float *x, float *y, float *z);

#endif // VS_EXPORT_LISTENER




#ifdef VS_EXPORT_SOUNDBUFFER

// ================================
// ====>> SOUNDBUFFER
// ================================

typedef struct vsSoundbuffer vsSoundbuffer;
    
////////////////////////////////////////////////////////////
/// \brief Initialize soundbuffer
///
////////////////////////////////////////////////////////////
VSAUDIO_API vsSoundbuffer* vsSoundBufInit();
    
////////////////////////////////////////////////////////////
/// \brief Initialize soundbuffer
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundBufDestroy(vsSoundbuffer* sndbuf);
    
////////////////////////////////////////////////////////////
/// \brief Load sound from file
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundBufLoad(vsSoundbuffer* sndbuf, const char* filepath);
    
////////////////////////////////////////////////////////////
/// \brief Unload sound
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundBufUnload(vsSoundbuffer* sndbuf);

#endif // VS_EXPORT_SOUNDBUFFER




#ifdef VS_EXPORT_SOUND

// ================================
// ====>> SOUND
// ================================
    
typedef struct vsSound vsSound;
    
////////////////////////////////////////////////////////////
/// \brief Initialize soundbuffer
///
////////////////////////////////////////////////////////////
VSAUDIO_API vsSound* vsSoundInit();
    
////////////////////////////////////////////////////////////
/// \brief Initialize soundbuffer
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundDestroy(vsSound* snd);
    
////////////////////////////////////////////////////////////
/// \brief Bind soundbuffer to sound
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundBind(vsSound* snd, vsSoundbuffer* sndbuf);

////////////////////////////////////////////////////////////
/// \brief Play the sound
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundPlay(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Pause the sound
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundPause(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Pause the sound
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundStop(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Set the sound volume using a value between 0
/// and 1
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundSetVolume(vsSound* snd, const float volume);

////////////////////////////////////////////////////////////
/// \brief Get the sound volume
///
////////////////////////////////////////////////////////////
VSAUDIO_API float vsSoundGetVolume(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Set the sound position in space
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundSetPosition(vsSound* snd, const float x, const float y, const float z);

////////////////////////////////////////////////////////////
/// \brief Get the sound position in space
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundGetPosition(vsSound* snd, float *x, float *y, float *z);

////////////////////////////////////////////////////////////
/// \brief Set if the sound should loop or not
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundSetLoop(vsSound* snd, const int loop);

////////////////////////////////////////////////////////////
/// \brief Get if the sound should loop or not
///
////////////////////////////////////////////////////////////
VSAUDIO_API int vsSoundGetLoop(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Set the sound pitch
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundSetPitch(vsSound* snd, float pitch);

////////////////////////////////////////////////////////////
/// \brief Get the sound pitch
///
////////////////////////////////////////////////////////////
VSAUDIO_API float vsSoundGetPitch(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Set if the sound is relative to the listener
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundSetRelativeToListener(vsSound* snd, const int relative);

////////////////////////////////////////////////////////////
/// \brief Get if the sound is relative to the listener
///
////////////////////////////////////////////////////////////
VSAUDIO_API int vsSoundGetRelativeToListener(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Set minimum distance
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundSetMinDistance(vsSound* snd, const float distance);

////////////////////////////////////////////////////////////
/// \brief Get minimum distance
///
////////////////////////////////////////////////////////////
VSAUDIO_API float vsSoundGetMinDistance(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Set the sound attenuation
///
////////////////////////////////////////////////////////////
VSAUDIO_API void vsSoundSetAttenuation(vsSound* snd, const float attenuation);

////////////////////////////////////////////////////////////
/// \brief Get the sound attenuation
///
////////////////////////////////////////////////////////////
VSAUDIO_API float vsSoundGetAttenuation(vsSound* snd);

////////////////////////////////////////////////////////////
/// \brief Get the status of the soundbuffer
///
////////////////////////////////////////////////////////////
VSAUDIO_API int vsSoundGetStatus(vsSound* snd);

#endif // VS_EXPORT_SOUND

#ifdef __cplusplus
} //EXTERN C
#endif

#endif // VS_AUDIO_H



////////////////////////////////////////////////////////////
///	IMPLEMENTATION
////////////////////////////////////////////////////////////
#ifdef VS_AUDIO_IMPLEMENTATION



////////////////////////////////////////////////////////////
///	INCLUDES
////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if defined(VS_SYS_MAC) || defined(VS_SYS_IOS)
    #include <OpenAL/al.h>
    #include <OpenAL/alc.h>
#elif defined(VS_SYS_LINUX)
	#include <AL/al.h>
	#include <AL/alc.h>
#endif



////////////////////////////////////////////////////////////
///	CONSTANTS
////////////////////////////////////////////////////////////
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) 
#define ERROR(msg) printf("[ERROR] in %s l%d: %s\n", __FILENAME__, __LINE__, msg)



////////////////////////////////////////////////////////////
///	STRUCTURES
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
typedef struct vsListener
{
    float Volume;
    float PosX, PosY, PosZ;
    float DirX, DirY, DirZ;
} vsListener;

////////////////////////////////////////////////////////////
typedef struct vsSoundbuffer
{
    unsigned int alBuffer;
} vsSoundbuffer;

////////////////////////////////////////////////////////////
typedef struct vsSound
{
    unsigned int alSource;
} vsSound;

static vsListener listener;



// ================================
// ====>> WAVE FILE STRUCTURE
// ================================

////////////////////////////////////////////////////////////
/// \brief The chunk descriptor
///
////////////////////////////////////////////////////////////
typedef struct Wav_riff
{
    char ChunkID[4];
    unsigned int ChunkSize;
    char Format[4];
} Wav_riff;

////////////////////////////////////////////////////////////
/// \brief Descrives the format of the sound information in
/// the data sub-chunk
///
////////////////////////////////////////////////////////////
typedef struct Wav_fmt
{
    char Subchunk1ID[4];
    unsigned int Subchunk1Size;
    unsigned short AudioFormat;
    unsigned short NumChannels;
    unsigned int SampleRate;
    unsigned int ByteRate;
    unsigned short BlockAlign;
    unsigned short BitsPerSample;
} Wav_fmt;

////////////////////////////////////////////////////////////
/// \brief Indicates the size of the sound information and
/// contains the raw sound data
///
////////////////////////////////////////////////////////////
typedef struct Wav_data
{
    unsigned int Subchunk2ID;
    unsigned int Subchunk2Size;
    char* data;
} Wav_data;




// ================================
// ====>> AUDIO
// ================================

ALCdevice *dev;
ALCcontext *ctx;

////////////////////////////////////////////////////////////
void vsAudioInit()
{
    dev = alcOpenDevice(NULL);
    if(!dev) {
        ERROR("can't open the device");
        return;
    }
    ctx = alcCreateContext(dev, NULL);
    alcMakeContextCurrent(ctx);
    if(!ctx) {
        ERROR("can't create the openal context");
        return;
    }
}

////////////////////////////////////////////////////////////
void vsAudioDestroy()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(ctx);
    alcCloseDevice(dev);
}




// ================================
// ====>> LISTENER
// ================================

////////////////////////////////////////////////////////////
void vsListenerSetGlobalVolume(const float volume)
{
    listener.Volume = volume;
    alListenerf(AL_GAIN, volume);
}

////////////////////////////////////////////////////////////
float vsListenerGetGlobalVolume()
{
    return listener.Volume;
}

////////////////////////////////////////////////////////////
void vsListenerSetPosition(const float x, const float y, const float z)
{
    listener.PosX = x;
    listener.PosY = y;
    listener.PosZ = z;
    alListener3f(AL_POSITION, x, y, z);
}

////////////////////////////////////////////////////////////
void vsListenerGetPosition(float *x, float *y, float *z)
{
    *x = listener.PosX;
    *y = listener.PosY;
    *z = listener.PosZ;
}

////////////////////////////////////////////////////////////
void vsListenerSetDirection(const float x, const float y, const float z)
{
    listener.DirX = x;
    listener.DirY = y;
    listener.DirZ = z;
    alListener3f(AL_DIRECTION, x, y, z);
}

////////////////////////////////////////////////////////////
void vsListenerGetDirection(float *x, float *y, float *z)
{
    *x = listener.DirX;
    *y = listener.DirY;
    *z = listener.DirZ;
}




// ================================
// ====>> SOUNDBUFFER
// ================================

////////////////////////////////////////////////////////////
vsSoundbuffer* vsSoundBufInit()
{
    return (vsSoundbuffer*)malloc(sizeof(vsSoundbuffer));
}

////////////////////////////////////////////////////////////
void vsSoundBufUnload(vsSoundbuffer* sndbuf)
{
    if (sndbuf->alBuffer) {
        alDeleteBuffers(1, &sndbuf->alBuffer);
        sndbuf->alBuffer = -1;
    }
}

////////////////////////////////////////////////////////////
void vsSoundBufDestroy(vsSoundbuffer* sndbuf)
{
    vsSoundBufUnload(sndbuf);
    if (sndbuf != NULL) {
        free(sndbuf);
        sndbuf = NULL;
    }
}

////////////////////////////////////////////////////////////
void vsSoundBufLoad(vsSoundbuffer* sndbuf, const char* filepath)
{
    //Unload
    vsSoundBufUnload(sndbuf);
    
    //Open file
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        ERROR("can't open the file");
        fclose(file);
        return;
    }
    
    //WAVE chunks
    Wav_riff Wriff;
    Wav_fmt Wfmt;
    Wav_data Wdata;
    
    //Read RIFF chunk
    fread(&Wriff, sizeof(Wav_riff), 1, file);
    
    //Check for errors
    if (strncmp(Wriff.ChunkID, "RIFF", 4) &&
        strncmp(Wriff.Format, "WAVE", 4)) {
        ERROR("file format not recognized");
        fclose(file);
        return;
    }
    
    //Read FMT chunk
    fread(&Wfmt, sizeof(Wav_fmt), 1, file);
    
    //Check for errors
    if (strncmp(Wfmt.Subchunk1ID, "fmt", 3) &&
        Wfmt.AudioFormat != 1) {
        ERROR("file format not recognized");
        fclose(file);
        return;
    }
    
    //Check AL Format
    int ALFormat;
    if (Wfmt.NumChannels == 1 && Wfmt.BitsPerSample == 8)
        ALFormat = AL_FORMAT_MONO8;
    else if (Wfmt.NumChannels == 1 && Wfmt.BitsPerSample == 16)
        ALFormat = AL_FORMAT_MONO16;
    else if (Wfmt.NumChannels == 2 && Wfmt.BitsPerSample == 8)
        ALFormat = AL_FORMAT_STEREO8;
    else if (Wfmt.NumChannels == 2 && Wfmt.BitsPerSample == 16)
        ALFormat = AL_FORMAT_STEREO16;
    else {
        ERROR("file is not correctly formatted");
        fclose(file);
        return;
    }
    
    //Read last chunk
    fread(&Wdata.Subchunk2ID, sizeof(int), 1, file);
    fread(&Wdata.Subchunk2Size, sizeof(int), 1, file);
    
    //Allocate and read raw data
    Wdata.data = (char*)malloc(sizeof(char) * Wdata.Subchunk2Size);
    fread(Wdata.data, sizeof(unsigned char), Wdata.Subchunk2Size, file);
    
    //Create sound
    alGenBuffers(1, &sndbuf->alBuffer);
    alBufferData(sndbuf->alBuffer, ALFormat, Wdata.data, Wdata.Subchunk2Size, Wfmt.SampleRate);
    
    //Deallocate data
    free(Wdata.data);
    
    //Close file
    fclose(file);
}




// ================================
// ====>> SOUND
// ================================

////////////////////////////////////////////////////////////
vsSound* vsSoundInit()
{
    vsSound* snd;
    snd = (vsSound*)malloc(sizeof(vsSound));
    snd->alSource = -1;
    alGenSources(1, &snd->alSource);
    return snd;
}

////////////////////////////////////////////////////////////
void vsSoundDestroy(vsSound* snd)
{
    if (snd->alSource) {
        alDeleteSources(1, &snd->alSource);
        snd->alSource = -1;
        free(snd);
    }
}

////////////////////////////////////////////////////////////
void vsSoundBind(vsSound* snd, vsSoundbuffer* sndbuf)
{
    if (snd->alSource) alSourcei(snd->alSource, AL_BUFFER, sndbuf->alBuffer);
}

////////////////////////////////////////////////////////////
void vsSoundPlay(vsSound* snd)
{
    if (snd->alSource) alSourcePlay(snd->alSource);
}

////////////////////////////////////////////////////////////
void vsSoundPause(vsSound* snd)
{
    if (snd->alSource) alSourcePause(snd->alSource);
}

////////////////////////////////////////////////////////////
void vsSoundStop(vsSound* snd)
{
    if (snd->alSource) alSourceStop(snd->alSource);
}

////////////////////////////////////////////////////////////
void vsSoundSetVolume(vsSound* snd, const float volume)
{
    if (snd->alSource) alSourcef(snd->alSource, AL_GAIN, volume);
}

////////////////////////////////////////////////////////////
float vsSoundGetVolume(vsSound* snd)
{
    ALfloat volume;
    alGetSourcef(snd->alSource, AL_GAIN, &volume);
    return volume;
}

////////////////////////////////////////////////////////////
void vsSoundSetPosition(vsSound* snd, const float x, const float y, const float z)
{
    alSource3f(snd->alSource, AL_POSITION, x, y, z);
}

////////////////////////////////////////////////////////////
void vsSoundGetPosition(vsSound* snd, float *x, float *y, float *z)
{
    alGetSource3f(snd->alSource, AL_POSITION, x, y, z);
}

////////////////////////////////////////////////////////////
void vsSoundSetLoop(vsSound* snd, const int loop)
{
    if (snd->alSource) alSourcei(snd->alSource, AL_LOOPING, loop);
}

////////////////////////////////////////////////////////////
int vsSoundGetLoop(vsSound* snd)
{
    ALint loop;
    alGetSourcei(snd->alSource, AL_LOOPING, &loop);
    return loop != 0;
}

////////////////////////////////////////////////////////////
void vsSoundSetPitch(vsSound* snd, float pitch)
{
    alSourcef(snd->alSource, AL_PITCH, pitch);
}

////////////////////////////////////////////////////////////
float vsSoundGetPitch(vsSound* snd)
{
    ALfloat pitch;
    alGetSourcef(snd->alSource, AL_PITCH, &pitch);
    return pitch;
}

////////////////////////////////////////////////////////////
void vsSoundSetRelativeToListener(vsSound* snd, const int relative)
{
    alSourcei(snd->alSource, AL_SOURCE_RELATIVE, relative);
}

////////////////////////////////////////////////////////////
int vsSoundGetRelativeToListener(vsSound* snd)
{
    ALint relative;
    alGetSourcei(snd->alSource, AL_SOURCE_RELATIVE, &relative);
    return relative != 0;
}

////////////////////////////////////////////////////////////
void vsSoundSetMinDistance(vsSound* snd, const float distance)
{
    alSourcef(snd->alSource, AL_REFERENCE_DISTANCE, distance);
}

////////////////////////////////////////////////////////////
float vsSoundGetMinDistance(vsSound* snd)
{
    ALfloat distance;
    alGetSourcef(snd->alSource, AL_REFERENCE_DISTANCE, &distance);
    return distance;
}

////////////////////////////////////////////////////////////
void vsSoundSetAttenuation(vsSound* snd, const float attenuation)
{
    alSourcef(snd->alSource, AL_ROLLOFF_FACTOR, attenuation);
}

////////////////////////////////////////////////////////////
float vsSoundGetAttenuation(vsSound* snd)
{
    ALfloat attenuation;
    alGetSourcef(snd->alSource, AL_ROLLOFF_FACTOR, &attenuation);
    return attenuation;
}

////////////////////////////////////////////////////////////
int vsSoundGetStatus(vsSound* snd)
{
    ALint state;
    alGetSourcei(snd->alSource, AL_SOURCE_STATE, &state);
    switch (state) {
        case AL_INITIAL:
        case AL_STOPPED: return 0;
        case AL_PAUSED:  return 1;
        case AL_PLAYING: return 2;
    }
    
    return 0;
}

#endif
