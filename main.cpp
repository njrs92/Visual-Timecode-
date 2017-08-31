
#include <iostream>
#include "timecode.cpp"
#include "manchester.cpp"
#include <stdio.h>
#include <Windows.h>

//OpenAl Includes
#include <al.h>
#include <alc.h>


using namespace std;

int main()
{
	timecode_frame frame;
	int input;
	
	cout << "Enter Frame";
    cin >> input;
	frame.set_frameNumber(input);
	cin.clear();

	cout << "Enter Seconds";
	cin >> input;
	frame.set_seconds(input);
	cin.clear();
    
	cout << "enter Minuntes";
	cin >> input;
	frame.set_minutes(input);
	cin.clear();
		
	cout << "Enter Hours";
	cin >> input;
	frame.set_hours(input);
	cin.clear();
		
	cout << "Time Entered" << std::endl <<  frame.return_hour() << ":" << frame.return_min() << ":" << frame.return_sec() << ":" << frame.return_frameNum() ;
    cout << "\n" ;

    frame.set_colorFlag(true);
		system("pause");


unsigned char HIGH = 245;
unsigned char LOW = 10;

unsigned char fp1[1600] = { 0 };
unsigned char fp2[1600] = { 0 };
unsigned char fp3[1600] = { 0 };
unsigned char fp4[1600] = { 0 };

unsigned char *fp_combined[4] = { &fp1[0],&fp2[0],&fp3[0],&fp4[0] };

ALCdevice *device;
ALCcontext *context;
device = alcOpenDevice(NULL);
context = alcCreateContext(device, NULL);
alcMakeContextCurrent(context);

ALuint source;
ALuint buffer[4];
ALenum format = 0;

alGenBuffers(4, &buffer[0]);
alGenSources(1, &source);

format = AL_FORMAT_MONO8;
for (int i = 0; i < 4; i++)
{
	alBufferData(buffer[i], format, fp_combined[i], 1600, 40000);
	alSourceQueueBuffers(source, 1, &buffer[i]);
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
bool last_bit = FALSE;
bool frame_encoded[160];
unsigned char fp[1600] = { 0 };


Repeat:
iBuffersProcessed = 0;
alGetSourcei(source, AL_BUFFERS_PROCESSED, &iBuffersProcessed);

while (iBuffersProcessed)
{
	uiBuffer = 0;
	alSourceUnqueueBuffers(source, 1, &uiBuffer);
	frame.set_to_next_frame();
	manchester(frame_encoded, frame, last_bit);
		
	for (int i = 0; i < 1600; i++)
	{
		if (i % 10 == 0)
		{
			if (frame_encoded[i/10] == true)
			{
				fp[i] = HIGH;
				
			}
			else
			{
				fp[i] = LOW;
				
			}
		}
		else
		{
			fp[i] = fp[i-1];
		}
	}

	last_bit = frame_encoded[159];
	alBufferData(uiBuffer, format, fp, 1600, 40000);
	alSourceQueueBuffers(source, 1, &uiBuffer);
	iBuffersProcessed--;
	
}

alGetSourcei(source, AL_SOURCE_STATE, &iState);

if (iState != AL_PLAYING) {
	alSourcePlay(source);
}
Sleep(100);

goto Repeat;



return 0;
}
