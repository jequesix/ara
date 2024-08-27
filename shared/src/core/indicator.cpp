#include "indicator.hpp"

#if defined (__AVR)

AraIndicator::AraIndicator(uint16_t _cyclesPerFlash) : cyclesPerFlash(_cyclesPerFlash) {
  pinMode(LED_BUILTIN, OUTPUT);
}


void AraIndicator::ledFlash() {
  if (++numCycles >= cyclesPerFlash) {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    numCycles = 0;
  }
}

#endif


#ifdef DISPLAY_ACPS
void AraIndicator::displayAcps() {
  acps++;
  if (acpsTimer.reached()) {
    debug_msg_f("ACPS: ");
    debug_msg_nl(acps);

    acps = 0;
  }
}


#endif
