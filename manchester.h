#pragma once
#include "timecode.h"

void manchester(bool(&output_frame)[160], timecode_frame, bool = false);