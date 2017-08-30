
#include <iostream>
#include "timecode.h"
#include "manchester.cpp"
#include <stdio.h>
#include <math.h>
#include <Windows.h>

#include <al.h>
#include <alc.h>

#include <vector>
#include <limits>

using namespace std;

int endWithError(char* msg, int error = 0)
{
	cout << msg << "\n";
	system("PAUSE");
	return error;
}

int main()
{
    int sec_input;
    int min_input;
    int temp; // needed because it was doing strange shit

	cout << "enter frame" ;
    cin >> temp;
    const int frame_input = temp;

    cout << "enter seconds" ;
    cin >> sec_input;

    cout << "enter minutes" ;
    cin >> min_input;

    cout << "enter hours" ;
    cin >> temp;
    const int hour_input = temp;
    cout << "time entered" << std::endl <<  hour_input << ":" << min_input << ":" << sec_input << ":" << frame_input ;
    cout << "\n" ;

    timecode_frame frame1;
    frame1.set_frameNumber(frame_input);
    frame1.set_seconds(sec_input);
    frame1.set_hours(hour_input);
    frame1.set_minutes(min_input);
	frame1.set_colorFlag(true);
	
	system("pause");

	timecode_frame  frame2 = frame1;
	frame2.set_to_next_frame();
	
	timecode_frame  frame3 = frame3;
	frame3.set_to_next_frame();

	timecode_frame  frame4 = frame3;
	frame4.set_to_next_frame();
	
	bool frame1_encoded[160];
	manchester(frame1_encoded,frame1);
	
	bool frame2_encoded[160];
	manchester(frame2_encoded, frame2);

	bool frame3_encoded[160];
	manchester(frame2_encoded, frame2);

	bool frame4_encoded[160];
	manchester(frame2_encoded, frame2);

unsigned char HIGH = 245;
unsigned char LOW = 10;

unsigned char fp1[1600];
for (int i = 0;  i < 1600;  i++)
{
	if (i % 10 == 0)
	{
		if (frame1_encoded[i / 10] == true)
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

unsigned char fp2[1600];
for (int i = 0; i < 1600; i++)
{
	if (i % 10 == 0)
	{
		if (frame2_encoded[i / 10] == true)
		{
			fp2[i] = HIGH;
		}
		else
		{
			fp2[i] = LOW;
		}
	}
	else
	{
		fp2[i] = fp2[i - 1];
	}
}

unsigned char fp3[1600];
for (int i = 0; i < 1600; i++)
{
	if (i % 10 == 0)
	{
		if (frame3_encoded[i / 10] == true)
		{
			fp3[i] = HIGH;
		}
		else
		{
			fp3[i] = LOW;
		}
	}
	else
	{
		fp3[i] = fp3[i - 1];
	}
}

unsigned char fp4[1600];
for (int i = 0; i < 1600; i++)
{
	if (i % 10 == 0)
	{
		if (frame4_encoded[i / 10] == true)
		{
			fp4[i] = HIGH;
		}
		else
		{
			fp4[i] = LOW;
		}
	}
	else
	{
		fp4[i] = fp4[i - 1];
	}
}

timecode_frame *frame_combined[4] = { &frame1 ,&frame2 ,&frame3 ,&frame4 };
bool frame_encoded_combined[4] = { &frame1_encoded[0] ,&frame2_encoded[0] ,&frame3_encoded[0] ,&frame4_encoded[0]};
unsigned char *fp_combined[4] = { &fp1[0], &fp2[0], &fp3[0], &fp4[0] };


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

//alSourcei(source, AL_BUFFER, buffer[0]);
alSourcef(source, AL_PITCH, 1.0f);
alSourcef(source, AL_GAIN, 1.0f);
alSourcefv(source, AL_POSITION, SourcePos);
alSourcefv(source, AL_VELOCITY, SourceVel);
//alSourcei(source, AL_LOOPING, AL_TRUE);

ALint iBuffersProcessed = 0;
ALuint	uiBuffer;
ALint	iState;


bool last_bit = frame4_encoded[159];
bool frame_encoded[160];
unsigned char fp[1600] = { 0 };
timecode_frame frame ;
frame.set_to_next_frame();

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
	cout << "Stoped";
	alSourcePlay(source);
}
Sleep(10);
goto Repeat;



return 0;
}
