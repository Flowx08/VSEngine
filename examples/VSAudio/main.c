#define VS_AUDIO_IMPLEMENTATION
#include "../src/VSAudio.h"
#include <unistd.h>

int main(int argc, const char * argv[]) {
    
    //Initialize vsaudio
    vsAudioInit();

    //Create soundbuffer and sound
	vsSoundbuffer* buf = vsSoundBufInit();
	vsSound* snd = vsSoundInit();
    
    //Load wav file into the soundbuffer
    vsSoundBufLoad(buf, "blip.wav");
    
    //Bind the soundbuffer to the sound
    vsSoundBind(snd, buf);
    
    //Play the sound
    vsSoundPlay(snd);
    
    sleep(10);
    
    //Destroy soundbuffer and sound
    vsSoundBufDestroy(buf);
    vsSoundDestroy(snd);
    
    //Destroy vsaudio
    vsAudioDestroy();
    
    return 0;
}
