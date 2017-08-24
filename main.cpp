
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
	
	
	bool frame1_encoded[160];
	*frame1_encoded = manchester(&frame1_encoded[0],frame1);
	



//for (int i = 0; i <= 159; i++)
//	{
//		cout << "bit number" << i << "pre encode bit number"<< i/2 << "----" << "pre encode bit" << frame1.getbit(i/2) << "---" << frame1_encoded[i] << "\n";
//	}
system("pause");

	timecode_frame  frame2 = frame1;
	frame2.set_frameNumber(frame_input + 1);
	
	bool frame2_encoded[160];
	*frame2_encoded = manchester(&frame2_encoded[0], frame2, frame1_encoded[159]);



//for (int i = 0; i < 80; i++)
//{
//	cout << "bit number" << "   " << i << "----" << "frame 2 bit" << frame2.getbit(i) << "   " << "frame 1 bit" << "   " << frame1.getbit(i) << "\n" ;
//}
//
//system("pause");


unsigned char HIGH = 255;
unsigned char LOW = 0;

unsigned char fp1[1920];
for (int i = 0;  i < 1920;  i++)
{
	if (i % 12 == 0)
	{
		if (frame1_encoded[i / 12] == true)
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

unsigned char fp2[1920];
for (int i = 0; i < 1920; i++)
{
	if (i % 12 == 0)
	{
		if (frame2_encoded[i / 12] == true)
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

unsigned char fp_big[3840];
for (int i = 0; i < 3840; i++)
{
	if (i < 1920)
		fp_big[i] = fp1[i];
	else
		fp_big[i] = fp2[i - 1920];
}



ALCdevice *device;
ALCcontext *context;
device = alcOpenDevice(NULL);
context = alcCreateContext(device, NULL);
alcMakeContextCurrent(context);

ALuint source;
ALuint buffer;
ALenum format = 0;

alGenBuffers(1, &buffer);
alGenSources(1, &source);

format = AL_FORMAT_MONO8;

alBufferData(buffer, format, &fp_big[0] , 3840, 48000);

ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

alListenerfv(AL_POSITION, ListenerPos);
alListenerfv(AL_VELOCITY, ListenerVel);
alListenerfv(AL_ORIENTATION, ListenerOri);

alSourcei(source, AL_BUFFER, buffer);
alSourcef(source, AL_PITCH, 1.0f);
alSourcef(source, AL_GAIN, 1.0f);
alSourcefv(source, AL_POSITION, SourcePos);
alSourcefv(source, AL_VELOCITY, SourceVel);
alSourcei(source, AL_LOOPING, AL_TRUE);

alSourcePlay(source);
system("pause");

return 0;
}
