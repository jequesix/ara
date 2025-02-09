#if defined (__AVR)
#include <Arduino.h>
#endif

#include <AraDebug.h>
#include "core/commander.hpp"

#include "modules/instance-test.hpp"
#include "modules/instance-caller.hpp"


#if defined (__AVR)
void setup() {
  debug_init(1000000);
#elif defined(__linux) || defined(__APPLE__)
int main() {
#endif


  // commander initialization
  // this is where to put the number of modules
  AraCommander ara = AraCommander(21);

  ara.addModule(new InstanceCaller(), true);
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());
  ara.addModule(new InstanceTest());


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
