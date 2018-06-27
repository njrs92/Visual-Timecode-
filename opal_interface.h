#pragma once
#include "manchester.h"
#include "al.h"
#include "alc.h"
#include <vector>
#include <Windows.h>
#include "timecode.h"


#include <iostream>
#include <stdio.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <functional>
#include <cstdlib>
#include <algorithm>
#include <lowpass.h>
#include <string>



void opal_interface(timecode_frame *, int , int , std::atomic_bool * , std::mutex*,std::atomic_bool * );

