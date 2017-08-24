#ifndef TIMECODE_H
#define TIMECODE_H


#include <iostream>  //remove after testing
using namespace std; //remove after testing

enum frameRate
    {
    F24,
    F25,
    F29,
    F30
    };

const bool syncWord[16] = {0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1};

const bool bitArray0[4] = {0,0,0,0}; //lok up table for BDC
const bool bitArray1[4] = {1,0,0,0}; //cbf doing bitwise shit
const bool bitArray2[4] = {0,1,0,0}; //least significant bit first
const bool bitArray3[4] = {1,1,0,0};
const bool bitArray4[4] = {0,0,1,0};
const bool bitArray5[4] = {1,0,1,0};
const bool bitArray6[4] = {0,1,1,0};
const bool bitArray7[4] = {1,1,1,0};
const bool bitArray8[4] = {0,0,0,1};
const bool bitArray9[4] = {1,0,0,1};


class timecode_frame
{
    public:
        timecode_frame(void);
		timecode_frame(const timecode_frame &obj); //makes copy of frame
		void set_to_next_frame(void);
        void set_frameNumber(int f);//done
        void set_colorFlag(bool c); //done
        void set_seconds(int sec);  //done
        void set_minutes(int min);  //done
        void set_hours(int hor);    //done
        void set_frameRate(frameRate f); //done
        void set_clockFlag(bool c); //done
        int return_frameNum(void);
        int return_sec(void);
        int return_min(void);
        int return_hours(void);
		bool getbit(int el);        //done
    private:
		bool frame[80] = {false};
        frameRate Fr;
		int current_frame = 0 ;
		int current_sec = 0;
		int current_min = 0 ;
		int current_hour = 0;
        void set_parity(void); //done
};


timecode_frame::timecode_frame(void)
{
    int j=0;   // puting the syncWord in the frame
    for(int i=64; i<=80;i++)
    {
        frame[i] = syncWord[j];
        j++;
    }
    frame[11] =  true ;//assuming Color
    Fr = F25; // the following is setting the frame as 25pfs
    this ->set_parity();

}

timecode_frame::timecode_frame(const timecode_frame &obj)
{
	for (int i = 0; i < 80; i++)
	{
	frame[i] = obj.frame[i];
	}
	
}

void set_to_next_frame(void) {


}

void timecode_frame::set_frameNumber(int f)
{
    if( (f >= 30) || (f<0)) { // ensuring that f is vaild
        f = 0;
    }

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
this ->set_parity();;
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
    return timecode_frame::frame[el];
}

void timecode_frame::set_colorFlag(bool c) {

        frame[11] =  c ;
        this ->set_parity();
}

void timecode_frame::set_clockFlag(bool c) {

        frame[58] =  c ;
        this ->set_parity();}

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
#endif // TIMECODE_H