#pragma once

#if defined (__AVR)
#include <Arduino.h>
#endif

#include <AraDebug.h>
#include "timer.hpp"

//#define DISPLAY_ACPS


class AraIndicator {
  public:
    #if defined(__AVR)

    AraIndicator(uint16_t _cyclesPerFlash);

    // turns on or off orange led every 'cyclesPerFlash' cycles
    void ledFlash();

    #endif

    #ifdef DISPLAY_ACPS
      // acps: ara cycles per second
      void displayAcps();
    #endif

  private:
    #if defined(__AVR)

    uint16_t cyclesPerFlash;
    uint16_t numCycles;

    bool ledState = false;

    #endif

    #ifdef DISPLAY_ACPS
      Timer acpsTimer{1000};
      uint32_t acps = 0;
    #endif
};
