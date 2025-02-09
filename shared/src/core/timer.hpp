#pragma once

#if defined (__AVR)
#include <Arduino.h>
#elif defined(__linux) || defined(__APPLE__)
#include <chrono>
using namespace std::chrono;
#endif

#include "types.hpp"


class Timer {
  public:
    Timer(uint16_t _timeDelta);

    // returns true when timer has been running for at least timeDelta milliseconds
    bool reached();

    void reset();
  
  private:
    uint16_t timeDelta;

    #if defined (__AVR)
    uint16_t lastTime;
    uint16_t currentTime;
    #elif defined(__linux) || defined(__APPLE__)
    steady_clock::time_point lastTime;
    steady_clock::time_point currentTime;
    #endif
};
