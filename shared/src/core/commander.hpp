#pragma once

#if defined (__AVR)
#include <Arduino.h>
#endif

#include "module.hpp"
#include "types.hpp"
#include "timer.hpp"
#include "queue.hpp"
#include "indicator.hpp"


class AraCommander {
  public:
    
    AraCommander(uint8_t _numModules);
    ~AraCommander();

    bool addModule(Module* module, bool isRecurrent = false);

    bool run();

    bool addCmd(uint8_t calleeId, uint8_t callerId, InputParameters* parameters = nullptr);

  private:
    void initModules();
    void mainLoop();

    // calls recurrent modules every time routinesTimer is reached
    void execRoutines();

    void execCmd();

    struct ModuleNode {
      Module* module;
      bool isBuzy = false;
    };

    uint8_t numModules;
    ModuleNode* moduleNodes;

    uint8_t currentModuleCount = 0;

    uint8_t numRecurrentModules = 0;
    bool recurrentMdlsEntered = false;

    Timer routinesTimer;
    bool routinesTimerReset = false;

    #if defined (__AVR)
    AraIndicator indicator{10000};
    #elif defined(__linux)
    AraIndicator indicator{};
    #endif
    

    // tells commander to execute a specific module
    struct AraCmd {
      uint8_t calleeId;
      uint8_t callerId;
      InputParameters* parameters;
      
      enum CmdStatus {
        WAITING = 0,
        BUZY = 1
      };
      uint8_t status = WAITING;
    };

    FastQueue<AraCmd> cmdQueue;
};
