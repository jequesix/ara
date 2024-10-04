#pragma once

#include "core/module.hpp"
#include "core/commander.hpp"
#include "core/timer.hpp"

uint8_t instanceNum = 1;

class InstanceTest : public Module {
  public:
    InstanceTest() : instance(instanceNum++) {}

    AraOutput araExecCmd(InputParameters* parameters) override {
      debug_msg("Instance: ")
      debug_msg_nl(instance)
      debug_msg("Number of executions: ")
      debug_msg_nl(execNum);
      execNum++;
      debug_msg_nl("")

      return {araexcode::DONE};
    }

  private:
    uint8_t instance = 0;
    volatile uint16_t execNum = 0;
};