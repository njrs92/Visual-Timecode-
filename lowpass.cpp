#include "lowpass.h"

void lowpass(std::vector<unsigned char> &input, int samplerate, int cutoff){
    std::vector<unsigned char> old = input;
    float alpha = 2 * 3.14159;
    alpha = alpha * (float) cutoff;
    alpha = alpha / (alpha + samplerate);

    for (int i = 1;i<input.size();i++){
        input[i]= input[i-1] + (alpha * (old[i]-input[i-1]));
    }


}
