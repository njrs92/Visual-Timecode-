#ifndef manchester_h
#define manchester_h
#include "timecode.h"

bool* manchester(bool output_frame[], timecode_frame frame);

bool* manchester(bool output_frame[], timecode_frame frame)
{

	for (int i = 0; i <= 159; i++)
	{
		if (i == 0)
		{
			output_frame[i] = frame.getbit(i);
			continue;
		}

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
#endif // !manchester_h