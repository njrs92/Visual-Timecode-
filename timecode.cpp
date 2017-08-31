#ifndef TIMECODE_CPP
#define TIMECODE_CPP



enum frameRate
    {
    F24 = 24,
    F25 = 25,
    F29 = 29,
    F30 = 30
    };

constexpr  bool syncWord[16] = {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1};
	constexpr  bool bitArray0[4] = {0,0,0,0}; //lok up table for BDC
	constexpr  bool bitArray1[4] = {1,0,0,0}; //least significant bit first
	constexpr  bool bitArray2[4] = {0,1,0,0}; 
	constexpr  bool bitArray3[4] = {1,1,0,0};
	constexpr  bool bitArray4[4] = {0,0,1,0};
	constexpr  bool bitArray5[4] = {1,0,1,0};
	constexpr  bool bitArray6[4] = {0,1,1,0};
	constexpr  bool bitArray7[4] = {1,1,1,0};
	constexpr  bool bitArray8[4] = {0,0,0,1};
	constexpr  bool bitArray9[4] = {1,0,0,1};


class timecode_frame
{
    public:
        timecode_frame(void);
		timecode_frame(timecode_frame &obj); //makes copy of a frame
		void set_to_next_frame(void);
        void set_frameNumber(int f);
        void set_colorFlag(bool c); 
        void set_seconds(int sec);  
        void set_minutes(int min);  
        void set_hours(int hor);    
        void set_frameRate(frameRate f); 
        void set_clockFlag(bool c);
		void set_dropFlag(bool d);
        int current_frameRate(void);   
		int return_frameNum(void);
        int return_sec(void);
        int return_min(void);
        int return_hour(void);
		bool getbit(int el);
		     
    private:
		bool frame[80] = {false};
        frameRate Fr;
		int current_frame = 0 ;
		int current_sec = 0;
		int current_min = 0 ;
		int current_hour = 0;
		void set_parity(void); 
};

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

timecode_frame::timecode_frame(timecode_frame &obj)
{
	for (int i = 0; i < 80; i++)
	{
	frame[i] = obj.frame[i];
	}

	Fr = obj.Fr;
	current_frame = obj.current_frame;
	current_sec = obj.current_sec;
	current_min = obj.current_min;
	current_hour = obj.current_hour;
			
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

	void timecode_frame::set_frameNumber(int f)
	{
		if( (f >= 30) || (f<0)) { // ensuring that f is vaild
			f = 0;
		}

		current_frame = f;
	
		int j = 0;
		//first Number
		int temp = f % 10;
		switch (temp) {
		case 0 :
			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray0[j];
				j++;
			}; break;

		case 1 :
			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray1[j];
				j++;
			}; break;

		case 2 :
			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray2[j];
				j++;
			}; break;


		case 3 :

			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray3[j];
				j++;
			}; break;

		case 4 :
			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray4[j];
				j++;
			}; break;

		case 5 :

			for(int i=0; i<=3;i++)
			{
			 frame[i] = bitArray5[j];

				j++;
			}; break;


		case 6 :
			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray6[j];
				j++;
			}; break;


		case 7 :
			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray7[j];
				j++;
			}; break;

		case 8 :
			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray8[j];
				j++;
			}; break;

		case 9 :
			for(int i=0; i<=3;i++)
			{
				frame[i] = bitArray9[j];
				j++;
			}; break;
		}
		//2nd number
		temp = f - (f % 10);

		switch (temp) {
		case 00 :
			j = 0;
			for(int i=8; i<=9;i++)
			{
				frame[i] = bitArray0[j];
				j++;
			}; break;
		case 10 :
			j = 0;
			for(int i=8; i<=9;i++)
			{
				frame[i] = bitArray1[j];
				j++;
			}; break;
		case 20 :
			j = 0;
			for(int i=8; i<=9;i++)
			{
				frame[i] = bitArray2[j];
				j++;
			}; break;


	}
	this ->set_parity();
	}

void timecode_frame::set_seconds(int sec)
{

    if ( (sec >= 60) || (sec<0)) { // ensuring that sec is vaild
        sec = 0;
    }
	current_sec = sec;
    int j = 0;
    //first Number
    int temp = sec % 10;


    switch (temp) {
    case 0 :
        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray0[j];
            j++;
        }; break;

    case 1 :
        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray1[j];
            j++;
        }; break;

    case 2 :
        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray2[j];
            j++;
        }; break;


    case 3 :

        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray3[j];
            j++;
        }; break;

    case 4 :
        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray4[j];
            j++;
        }; break;

    case 5 :

        for(int i=16; i<=19;i++)
        {
         frame[i] = bitArray5[j];

            j++;
        }; break;


    case 6 :
        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray6[j];
            j++;
        }; break;


    case 7 :
        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray7[j];
            j++;
        }; break;

    case 8 :
        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray8[j];
            j++;
        }; break;

    case 9 :
        for(int i=16; i<=19;i++)
        {
            frame[i] = bitArray9[j];
            j++;
        }; break;
    }
    //2nd number
    temp = sec - (sec % 10);

    switch (temp) {
    case 00 :
        j = 0;
        for(int i=24; i<=26;i++)
        {
            frame[i] = bitArray0[j];
            j++;
        }; break;
    case 10 :
        j = 0;
        for(int i=24; i<=26;i++)
        {
            frame[i] = bitArray1[j];
            j++;
        }; break;
    case 20 :
        j = 0;
        for(int i=24; i<=26;i++)
        {
            frame[i] = bitArray2[j];
            j++;
        }; break;
    case 30 :
        j = 0;
        for(int i=24; i<=26;i++)
        {
            frame[i] = bitArray3[j];
            j++;
        }; break;
    case 40 :
        j = 0;
        for(int i=24; i<=26;i++)
        {
            frame[i] = bitArray4[j];
            j++;
        }; break;
    case 50 :
        j = 0;
        for(int i=24; i<=26;i++)
        {
            frame[i] = bitArray5[j];
            j++;
        }; break;

}
    this ->set_parity();;
}

void timecode_frame::set_minutes(int min)
{
    if ( (min >= 60) || (min<0)) { // ensuring that mon is vaild
        min = 0;
    }

	current_min = min;

    int j = 0;
    //first Number
    int temp = min % 10;


    switch (temp) {
    case 0 :
        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray0[j];
            j++;
        }; break;

    case 1 :
        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray1[j];
            j++;
        }; break;

    case 2 :
        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray2[j];
            j++;
        }; break;


    case 3 :

        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray3[j];
            j++;
        }; break;

    case 4 :
        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray4[j];
            j++;
        }; break;

    case 5 :

        for(int i=32; i<=35;i++)
        {
         frame[i] = bitArray5[j];

            j++;
        }; break;


    case 6 :
        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray6[j];
            j++;
        }; break;


    case 7 :
        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray7[j];
            j++;
        }; break;

    case 8 :
        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray8[j];
            j++;
        }; break;

    case 9 :
        for(int i=32; i<=35;i++)
        {
            frame[i] = bitArray9[j];
            j++;
        }; break;
    }
    //2nd number
    temp = min - (min % 10);
    switch (temp) {
    case 00 :
        j = 0;
        for(int i=40; i<=42;i++)
        {
            frame[i] = bitArray0[j];
            j++;
        }; break;
    case 10 :
        j = 0;
        for(int i=40; i<=42;i++)
        {
            frame[i] = bitArray1[j];
            j++;
        }; break;
    case 20 :
        j = 0;
        for(int i=40; i<=42;i++)
        {
            frame[i] = bitArray2[j];
            j++;
        }; break;
    case 30 :
        j = 0;
        for(int i=40; i<=42;i++)
        {
            frame[i] = bitArray3[j];
            j++;
        }; break;
    case 40 :
        j = 0;
        for(int i=40; i<=42;i++)
        {
            frame[i] = bitArray4[j];
            j++;
        }; break;
    case 50 :
        j = 0;
        for(int i=40; i<=42;i++)
        {
            frame[i] = bitArray5[j];
            j++;
        }; break;

}
this ->set_parity();
}

void timecode_frame::set_hours(int hor)
{
	if ( (hor >= 24) || (hor<0)) { // ensuring that hor is vaild
        hor = 0;
            }
    int j = 0;
	current_hour = hor;

    //first Number

    int temp = (hor % 10);

    switch (temp) {
    case 0 :

        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray0[j];
            j++;
        }; break;

    case 1 :
        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray1[j];
            j++;
        }; break;

    case 2 :
        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray2[j];
            j++;
        }; break;


    case 3 :

        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray3[j];
            j++;
        }; break;

    case 4 :

        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray4[j];
            j++;
        }; break;

    case 5 :

        for(int i=48; i<=51;i++)
        {
         frame[i] = bitArray5[j];

            j++;
        }; break;


    case 6 :
        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray6[j];
            j++;
        }; break;


    case 7 :
        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray7[j];
            j++;
        }; break;

    case 8 :
        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray8[j];
            j++;
        }; break;

    case 9 :
        for(int i=48; i<=51;i++)
        {
            frame[i] = bitArray9[j];
            j++;
        }; break;
    }
    //2nd number
    temp = hor - (hor % 10);

    switch (temp) {
    case 00 :
        j = 0;
        for(int i=56; i<=57;i++)
        {
            frame[i] = bitArray0[j];
            j++;
        }; break;
    case 10 :
        j = 0;
        for(int i=56; i<=57;i++)
        {
            frame[i] = bitArray1[j];
            j++;
        }; break;
    case 20 :
        j = 0;
        for(int i=56; i<=57;i++)
        {
            frame[i] = bitArray2[j];
            j++;
        }; break;

}
this ->set_parity();
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