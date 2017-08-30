#ifndef manchester_cpp
#define manchester_cpp
#include "timecode.h"

void manchester(bool(&output_frame)[160], timecode_frame & frame);

void manchester(bool(&output_frame)[160], timecode_frame & frame, bool lastbit);


void manchester(bool (&output_frame)[160], timecode_frame & frame)
{
	output_frame[0] = frame.getbit(0);
	for (int i = 1; i < 160; i++)
	{
		if ((i % 2) == 1)
		{
			if (frame.getbit(i / 2) == true)
			{
				output_frame[i] = !(output_frame[(i - 1)]);
			}
			else
			{
				output_frame[i] = output_frame[(i - 1)];
			}
		}
		else
		{
			output_frame[i] = !output_frame[i - 1];
		}
	}
	return ;
}

void manchester(bool(&output_frame)[160], timecode_frame & frame, bool lastbit)
{
	output_frame[0] = !lastbit;

	for (int i = 1; i < 160; i++)
	{
		if ((i % 2) == 1)
		{
			if (frame.getbit(i/2) == true)
			{
				output_frame[i] = !output_frame[i - 1];
			}
			else
			{
				output_frame[i] = output_frame[i - 1];
			}
		}
		else
		{
			output_frame[i] = !output_frame[i - 1];
		}
	}
	return ;
}



#endif // !manchester_h