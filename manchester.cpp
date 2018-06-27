#ifndef manchester_cpp
#define manchester_cpp
#include "manchester.h"

void manchester(bool(&output_frame)[160], timecode_frame  frame, bool lastbit)
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