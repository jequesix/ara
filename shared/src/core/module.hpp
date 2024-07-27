#pragma once

#if defined (__AVR)
#include <Arduino.h>
#endif

#include "types.hpp"


// module: manages a specific physical or abstract entity in the robot
// methods prefixed with 'ara' are AraCommander hooks

class AraCommander;

class Module {
  protected:
    // initialize stuff that requires ara (e.g. adding a command) here
    virtual void araInit() {}

    // called when a command asks for it
    virtual AraOutput araExecCmd(InputParameters* parameters) {
      return {araexcode::DONE};
    }

    // called every ara cycle
    virtual void araExecRecurrent() {}

    // give callee output to caller
    virtual void araGivePeasantOutput(uint8_t calleeId, OutputParameters* calleeOutput) {}

    AraCommander* ara() const { return _ara; }
  
  private:
    AraCommander* _ara = nullptr;
    
    friend class AraCommander;
};


// useful for doing logic on multiple module outputs
class ChainModule : public Module {
  public:
    ChainModule(uint8_t _numCycles) : numCycles(_numCycles) {}

    AraOutput araExecCmd(InputParameters* parameters) {
      if (++currentCycle <= numCycles) {
        return main(parameters);
      }
      
      currentCycle = 0;
      return {araexcode::DONE};
    }

  protected:
    AraOutput main(InputParameters* parameters) { return {araexcode::DONE}; }

    OutputParameters* calleeOutput;
    uint8_t currentCycle = 0;
    uint8_t numCycles;
};
