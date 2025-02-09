#include "timer.hpp"


#if defined (__AVR)

Timer::Timer(uint16_t _timeDelta) : timeDelta(_timeDelta), lastTime(millis()) {}


bool Timer::reached() {
  currentTime = millis();

  if ((currentTime - lastTime) >= timeDelta) {
    lastTime = currentTime;
    return true;
  }

  return false;
}

#elif defined (__linux)

Timer::Timer(uint16_t _timeDelta) : timeDelta(_timeDelta), lastTime(steady_clock::now()) {}


bool Timer::reached() {
  currentTime = steady_clock::now();

  if ((duration_cast<milliseconds>(currentTime - lastTime).count()) >= timeDelta) {
    lastTime = currentTime;
    return true;
  }

  return false;
}

#endif


void Timer::reset() {
  #if defined (__AVR)
  currentTime = millis();
  #elif defined (__linux)
  currentTime = steady_clock::now();
  #endif

  lastTime = currentTime;
}
