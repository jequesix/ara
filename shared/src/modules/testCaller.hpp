#pragma once

#include "core/module.hpp"
#include "core/commander.hpp"
#include "core/timer.hpp"
#include "modules/test.hpp"


class MgrTestCaller : public Module {
  private:
    void araExecRecurrent() override;
    void araGivePeasantOutput(uint8_t calleeId, OutputParameters* calleeOutput) override;

    Timer testClrTimer{3000};

    MgrTest::TestParameters testParams;
};
