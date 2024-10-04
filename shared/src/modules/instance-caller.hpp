#pragma once

#include "core/module.hpp"
#include "core/commander.hpp"
#include "core/timer.hpp"

class InstanceCaller : public Module {
  public:
    AraOutput araExecCmd(InputParameters* parameters) override {
      //if (!addTimer.reached()) return {araexcode::RERUN};

      debug_msg("Calling instance ")
      debug_msg(currentInstance)
      debug_msg_nl("...")

      ara()->addCmd(currentInstance++, 0);
      
      if (currentInstance <= instances) {
        return {araexcode::RERUN};
      }

      currentInstance = 1;
      return {araexcode::DONE};
    }

    void araExecRecurrent() override {
      //if (!callTimer.reached()) return;

      if (currentInstance == 1) {
        ara()->addCmd(0, 0);
      }
    }

  private:
    uint8_t instances = 20;
    volatile uint16_t currentInstance = 1;

    //Timer addTimer{5};
    //Timer callTimer{5};
};