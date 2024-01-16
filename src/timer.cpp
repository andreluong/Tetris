#include "timer.h"

Timer::Timer() {
    lastUpdateTime = 0;
}

bool Timer::triggerEvent(int score) {
    double curTime = GetTime();
    if (curTime - lastUpdateTime >= getInterval(score)) {
        lastUpdateTime = curTime;
        return true;
    }
    return false;
}

double Timer::getInterval(int score) {
    return STARTING_INTERVAL - (score / SCORE_DIVISOR) * getMultipler(score);
}

int Timer::getMultipler(int score) {
    int multiplier;
    if (score >= FINAL_LEVEL) {
        multiplier = FINAL_MULTIPLIER;
    } else if (score >= SECOND_LEVEL) {
        multiplier = SECOND_MULTIPLIER;
    } else if (score >= FIRST_LEVEL) {
        multiplier = FIRST_MULTIPLIER;
    } else {
        multiplier = BASE_MULTIPLIER;
    }
    return multiplier;
}