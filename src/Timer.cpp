//
// Created by sauvau_m on 4/3/17.
//

#include "Timer.h"

Timer::~Timer() {

}

Timer::Timer() {

}

void Timer::start() {
    epoch = std::chrono::steady_clock::now();
}

std::chrono::steady_clock::duration Timer::timeElapsed() const {
    return std::chrono::steady_clock::now() - epoch;
}

bool Timer::isTimeOverMilliseconds(double milliseconds) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed()).count() >= milliseconds;
}

bool Timer::isTimeOverSeconds(double seconds) {
    return std::chrono::duration_cast<std::chrono::seconds>(timeElapsed()).count() >= seconds;
}

long Timer::timeElapsedSeconds() const {
    return std::chrono::duration_cast<std::chrono::seconds>(timeElapsed()).count();
}

long Timer::timeElapsedMilliseconds() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(timeElapsed()).count();
}
