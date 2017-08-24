#ifndef manchester_cpp
#define manchester_cpp
#include "timecode.h"

bool* manchester(bool output_frame[], timecode_frame frame);

bool* manchester(bool output_frame[], timecode_frame frame, bool lastbit );


bool* manchester(bool output_frame[], timecode_frame frame)
{
	output_frame[0] = frame.getbit(0);
	for (int i = 1; i <= 159; i++)
	{
		if ((i % 2) == 1)
		{
			output_frame[i] = !output_frame[i - 1];
		}
		else
		{
			if (frame.getbit(i / 2) == true)
			{
				output_frame[i] = !output_frame[i - 1];
			}
			else
			{
				output_frame[i] = output_frame[i - 1];
			}
		}
	}
	return output_frame;
}

bool* manchester(bool output_frame[], timecode_frame frame, bool lastbit)
{
	output_frame[0] = !lastbit;

	for (int i = 1; i <= 159; i++)
	{
		if ((i % 2) == 1)
		{
			output_frame[i] = !output_frame[i - 1];
		}
		else
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
	}
	return output_frame;
}



#endif // !manchester_h