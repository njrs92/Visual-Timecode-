#include "opal_interface.h"

const unsigned char HIGH = 245;
const unsigned char LOW = 10;


void opal_interface(timecode_frame* curent_frame, int samplerate , int number_of_buffers, std::atomic_bool* keep_running, std::mutex* safe, std::atomic_bool* direction)
{
    safe->lock();
    int frame_rate = curent_frame->current_frameRate();

    if ((samplerate >= 1000000 ) || (samplerate < 14000)) {
        samplerate = 48000;
    }

    if ((number_of_buffers >= 100) || (number_of_buffers < 2)) {
        number_of_buffers = 4;
    }

    if (samplerate%number_of_buffers) {
        samplerate = 48000;
        number_of_buffers = 4;
    }

    if (samplerate % frame_rate) {
        samplerate = 48000;
        number_of_buffers = 4;

    }

    ALCdevice *device;
    ALCcontext *context;
    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    ALuint source;

    ALenum format = 0;
    format = AL_FORMAT_MONO8;

    std::vector<ALuint> buffermap(number_of_buffers);
    alGenSources(1, &source);

    std::vector<unsigned char> fp((samplerate / frame_rate)*number_of_buffers);

    for (int i = 0; i < number_of_buffers; i++)
    {
        alGenBuffers(1, &buffermap[i]);
        alBufferData(buffermap[i], format, &fp[(samplerate / frame_rate)*i], (samplerate/frame_rate), samplerate);
        alSourceQueueBuffers(source, 1, &buffermap[i]);
    }

    ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
    ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
    alListenerfv(AL_POSITION, ListenerPos);
    alListenerfv(AL_VELOCITY, ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcefv(source, AL_POSITION, SourcePos);
    alSourcefv(source, AL_VELOCITY, SourceVel);
    alSourcei(source, AL_LOOPING, AL_FALSE);

    ALint iBuffersProcessed = 0;
    ALuint	uiBuffer;
    ALint	iState;
    bool last_bit = false;
    bool frame_encoded[160];

    int data_to_buffer_rate = ((samplerate / frame_rate) / 160);
    std::vector<unsigned char> fp1(samplerate / frame_rate);
    safe->unlock();

    while(*keep_running){


        iBuffersProcessed = 0;
        alGetSourcei(source, AL_BUFFERS_PROCESSED, &iBuffersProcessed);

        while (iBuffersProcessed)
        {
            uiBuffer = 0;
            alSourceUnqueueBuffers(source, 1, &uiBuffer);
            safe->lock();
            if (*direction){
                curent_frame->set_to_next_frame();
           }
            else {
                curent_frame->set_to_previous_frame();
            }
            manchester(frame_encoded, *curent_frame, last_bit);
            safe->unlock();

//            if(*direction != true){
//                int i=0;
//                int j=159;
//                while(i<j){
//                    bool temp = frame_encoded[i];
//                    frame_encoded[i]=frame_encoded[j];
//                    frame_encoded[j]=temp;
//                    i++;
//                    j--;

//                }
//            }


            for (int i = 0; i < (samplerate / frame_rate); i++)
            {
                if ((i % data_to_buffer_rate) == 0)
                {
                    if ( frame_encoded[(i/data_to_buffer_rate)] == true)
                    {
                        fp1[i] = HIGH;
                    }
                    else
                    {
                        fp1[i] = LOW;
                    }
                }
                else
                {
                    fp1[i] = fp1[i - 1];
                }
            }


            last_bit = frame_encoded[159];
            lowpass(fp1,samplerate,14000);
            alBufferData(uiBuffer, format, &fp1[0], (samplerate / frame_rate), samplerate);
            alSourceQueueBuffers(source, 1, &uiBuffer);
            iBuffersProcessed--;

        }
        alGetSourcei(source, AL_SOURCE_STATE, &iState);

        if (iState != AL_PLAYING) {
            alSourcePlay(source);
        }
    Sleep(50);
    }
alDeleteSources(1,&source);

for (int i = 0; i < number_of_buffers; i++){
    alDeleteBuffers(1,&buffermap[i]);
}
device = alcGetContextsDevice(context);
alcMakeContextCurrent(NULL);
alcDestroyContext(context);
alcCloseDevice(device);
}



