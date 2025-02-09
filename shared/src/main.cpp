#if defined (__AVR)
#include <Arduino.h>
#endif

#include <AraDebug.h>
#include "core/commander.hpp"

#include "modules/test.hpp"
#include "modules/testCaller.hpp"


static MgrTest mgrTest = MgrTest();
static MgrTestCaller mgrTestCaller = MgrTestCaller();


#if defined (__AVR)

void setup() {
  debug_init(1000000);

  AraCommander ara = AraCommander(2);

  ara.addModule(&mgrTest, true);
  ara.addModule(&mgrTestCaller, true);

  debug_freemem();
  ara.run();
}


void loop() {}

#elif defined (__linux)

int main() {
  AraCommander ara = AraCommander(2);

  ara.addModule(&mgrTest, true);
  ara.addModule(&mgrTestCaller, true);

  ara.run();

  return 0;
}

#endif
