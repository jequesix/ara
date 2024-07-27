#include "testCaller.hpp"


void MgrTestCaller::araExecRecurrent() {
  if (testClrTimer.reached()) {
    testParams.numberToDisplay = random();

    ara()->addCmd(0, 1, &testParams);
  }
}


void MgrTestCaller::araGivePeasantOutput(uint8_t calleeId, OutputParameters* calleeOutput) {
  debug_msg_f("Test Output: ");
  debug_msg_nl(((MgrTest::TestOutput*)calleeOutput)->numberDisplayed);
}
