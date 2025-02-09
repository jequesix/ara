#if defined (__AVR)
#include <Arduino.h>
#endif

#include <AraDebug.h>
#include <commander.hpp>


#if defined (__AVR)
void setup() {
  debug_init(1000000);
#elif defined(__linux) || defined(__APPLE__)
int main() {
#endif


  // commander initialization
  // this is where you put the number of modules
  AraCommander ara = AraCommander(0);

  // add modules here



  #if defined (__AVR)
  debug_freemem();
  #endif

  ara.run();

  #if defined(__linux) || defined(__APPLE__)
  return 0;
  #endif
}

#if defined (__AVR)
void loop() {}
#endif
