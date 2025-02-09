#include "modules/test.hpp"

AraOutput MgrTest::araExecCmd(InputParameters* _params) {
  TestParameters* params = (TestParameters*)_params;
  debug_msg_nl(params->numberToDisplay);
  output.numberDisplayed = params->numberToDisplay;

  return {araexcode::DONE, &output};
}

void MgrTest::araExecRecurrent() {
  ++number;
}
