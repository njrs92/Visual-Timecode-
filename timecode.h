#ifndef TIMECODE_H
#define TIMECODE_H
 // !TIMECODE_H

class timecode_frame
{
enum frameRate
{
	F24 = 24,
	F25 = 25,
	F29 = 29,
	F30 = 30
};

public:
	timecode_frame(void);
	void set_to_next_frame(void);
	void set_frameNumber(int );
    void set_to_previous_frame(void);
	void set_colorFlag(bool );
	void set_seconds(int );
	void set_minutes(int );
	void set_hours(int );
	void set_frameRate(frameRate );
	void set_clockFlag(bool );
	void set_dropFlag(bool );
	int current_frameRate(void);
	int return_frameNum(void);
	int return_sec(void);
	int return_min(void);
	int return_hour(void);
    bool getbit(int);


private:
	bool frame[80] = { false };
	frameRate Fr = F25;
	int current_frame = 0;
	int current_sec = 0;
	int current_min = 0;
	int current_hour = 0;
	void set_parity(void);
	const bool syncWord[16] = { 0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1 };
};
#endif
