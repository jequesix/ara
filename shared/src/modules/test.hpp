#pragma once

#include "core/module.hpp"
#include "modules/test.hpp"
#include <AraDebug.h>


class MgrTest : public Module {
  public:
    struct TestParameters : InputParameters {
      uint32_t numberToDisplay;
    };

    struct TestOutput : OutputParameters {
      uint32_t numberDisplayed;
    } output;
    
  private:
    AraOutput araExecCmd(InputParameters* _params) override;
    void araExecRecurrent() override;

    volatile uint32_t number = 0;
};
