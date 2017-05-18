#include <iostream>
#include <timecode.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    int sec_input;
    int min_input;
    int temp; // need because it was doing strange shit


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
    bool color_set;
    cout << "what do you want to set the color bit to 1 or 0" <<endl ;
    cin >> temp ;
    if(temp == 0){
        color_set  = false;
        frame1.set_colorFlag(color_set);
                }
        else {
        color_set  = true;
        frame1.set_colorFlag(color_set);
            }
    for (int i=0; i<=79; i++)
    {
    cout <<  "bit number" << i << "----" << frame1.getbit(i) << "\n";
    }

    return 0;
}

