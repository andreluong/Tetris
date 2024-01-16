#pragma once
#include <raylib.h>
#include "constants.h"

class Timer {
    public:
        Timer();
        bool triggerEvent(int score);
    private:
        double getInterval(int score);
        int getMultipler(int score);
        double lastUpdateTime;
};