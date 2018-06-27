#ifndef TIMECODE_CPP
#define TIMECODE_CPP
#include "timecode.h"
#include <bitset>


timecode_frame::timecode_frame(void)
{

    for(int i=64; i<80;i++)
    {
        frame[i] = syncWord[i -64];
    }
    frame[11] =  true ;//assuming Color
    Fr = F25; // the following is setting the frame as 25pfs
    this ->set_parity();

}

void timecode_frame::set_to_next_frame(void)
{
	if (current_frame < (Fr - 1))
	{
		set_frameNumber(current_frame + 1);
	}
		
	else if (current_sec < 59)
	{
		set_frameNumber(0);
		set_seconds(current_sec + 1);
	}
	else if (current_min < 59)
	{
		set_frameNumber(0);
		set_seconds(0);
		set_minutes(current_min + 1);
	}
	else if (current_hour < 23)
	{
		set_frameNumber(0);
		set_seconds(0);
		set_minutes(0);
		set_hours(current_hour + 1);
	}
	else
	{
		set_frameNumber(0);
		set_seconds(0);
		set_minutes(0);
		set_hours(0);
	}
	return;
}

void timecode_frame::set_to_previous_frame(void)
{

    if (current_frame > 0)
    {
        set_frameNumber(current_frame - 1);
    }

    else if (current_sec > 0)
    {
        set_frameNumber((Fr-1));
        set_seconds(current_sec -1);
    }
    else if (current_min > 0)
    {
        set_frameNumber((Fr-1));
        set_seconds(59);
        set_minutes(current_min -1);
    }
    else if (current_hour > 1)
    {
        set_frameNumber((Fr-1));
        set_seconds(59);
        set_minutes(59);
        set_hours(current_hour - 1);
    }
    else
    {
        set_frameNumber((Fr-1));
        set_seconds(59);
        set_minutes(59);
        set_hours(23);
    }
    return;
}

void timecode_frame::set_frameNumber(int f)
{
	if ((f >= Fr) || (f < 0)) { // ensuring that f is vaild
		f = 0;
	}

	current_frame = f;

	int const digits[] = { f % 10, f / 10 };
	
	std::bitset<4> bitsUnit{ 0u + digits[0] };
	for (int i = 0; i < 4; i++) {
		frame[i] = bitsUnit[i];
		
	}
	
	std::bitset<2> bitsTens{ 0u + digits[1] };
	for (int i = 8; i < 10; i++) {
		frame[i] = bitsTens[i -8];
		}
	
	this->set_parity();

}

void timecode_frame::set_seconds(int sec)
{

    if ( (sec >= 60) || (sec<0)) { // ensuring that sec is vaild
        sec = 0;
    }
	current_sec = sec;
	int const digits[] = { sec % 10, sec / 10 };

	std::bitset<4> bitsUnit{ 0u + digits[0] };
	for (int i = 0; i < 4; i++) {
		frame[i+16] = bitsUnit[i];

	}

	std::bitset<3> bitsTens{ 0u + digits[1] };
	for (int i = 0; i < 3; i++) {
		frame[i+24] = bitsTens[i];
	}

    this ->set_parity();
}

void timecode_frame::set_minutes(int min)
{
    if ( (min >= 60) || (min<0)) { // ensuring that min is vaild
        min = 0;
    }

	current_min = min;
	int const digits[] = { min % 10, min / 10 };
	std::bitset<4> bitsUnit{ 0u + digits[0] };
	for (int i = 0; i < 4; i++) {
		frame[i + 32] = bitsUnit[i];

	}
	
	std::bitset<3> bitsTens{ 0u + digits[1] };
	
	for (int i = 0; i < 3; i++) {
		frame[i + 40] = bitsTens[i];
	}
	this->set_parity();

}

void timecode_frame::set_hours(int hor)
{
	if ( (hor >= 24) || (hor<0)) { // ensuring that hor is vaild
        hor = 0;
            }
    
	current_hour = hor;

	int const digits[] = { hor % 10, hor / 10 };
	std::bitset<4> bitsUnit{ 0u + digits[0] };
	for (int i = 0; i < 4; i++) {
		frame[i + 48] = bitsUnit[i];

	}

	std::bitset<2> bitsTens{ 0u + digits[1] };

	for (int i = 0; i < 2; i++) {
		frame[i + 56] = bitsTens[i];
	}
	this->set_parity();

}

bool timecode_frame::getbit(int el) {
	if ((el >= 80) || (el<0)) { //insuring that el is vaild
		el = 0;
	}

    return timecode_frame::frame[el];
}

void timecode_frame::set_colorFlag(bool c) {

        frame[11] =  c ;
        this ->set_parity();
}

void timecode_frame::set_clockFlag(bool c) {

        frame[58] =  c ;
        this ->set_parity();}

void timecode_frame::set_dropFlag(bool d) {
	
	frame[10] = d;
}
void timecode_frame::set_frameRate(frameRate f) {
    Fr = f;
    this ->set_parity();;
    }
void timecode_frame::set_parity(void) {
    int isodd = false ;
    int temp = 0;
    for (int i = 0; i < 80; i++)
    {
        temp = temp + frame[i];
    }
    isodd = temp % 2;
    if(Fr == F25)
    {
     frame[59] = isodd ;
    }
    else {
     frame[27] = isodd ;
    }

}
int timecode_frame::return_frameNum(void) {
	return timecode_frame::current_frame;
}
int timecode_frame::return_sec(void) {
	return timecode_frame::current_sec;
}
int timecode_frame::return_min(void) {
	return timecode_frame::current_min;
}
int timecode_frame::return_hour(void) {
	return timecode_frame::current_hour;
}
int timecode_frame::current_frameRate(void)
{
	return timecode_frame::Fr;
}

#endif // TIMECODE_CPP
