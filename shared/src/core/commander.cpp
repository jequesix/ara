#include "commander.hpp"
#include <AraDebug.h>


AraCommander::AraCommander(uint8_t _numModules) : 
  numModules(_numModules), moduleNodes(new ModuleNode[_numModules]), routinesTimer(5), cmdQueue(32) {}


AraCommander::~AraCommander() {
  delete[] moduleNodes;
}


bool AraCommander::addModule(Module* module, bool isRecurrent) {
  debug_msg_f("Adding module ");
  debug_msg((int)currentModuleCount);
  debug_msg_nl_f("...");

  if (currentModuleCount >= numModules || module == nullptr) {
    debug_msg_nl_f("Invalid action! Skipping...");
    return false;
  }

  // ensures recurrent modules are at the beginning of the module list
  if (recurrentMdlsEntered && isRecurrent) {
    debug_msg_nl_f("Recurrent module misplaced! Skipping...");
    return false;
  } else if (!recurrentMdlsEntered) {
    if (!isRecurrent) {
      numRecurrentModules = currentModuleCount;
      recurrentMdlsEntered = true;
    } else if (currentModuleCount == numModules - 1) {
      numRecurrentModules = numModules;
      recurrentMdlsEntered = true;
    }
  }

  moduleNodes[currentModuleCount].module = module;
  currentModuleCount++;
  return true;
}


bool AraCommander::run() {
  if (currentModuleCount != numModules) {
    debug_msg_nl_f("Integrity check failed. Aborting...")
    return false;
  }

  debug_msg_nl_f("Initializing modules...");
  initModules();

  debug_msg_nl_f("Calling mainLoop...");
  mainLoop();

  return true;
}


void AraCommander::initModules() {
  for (uint8_t i=0; i<numModules; i++) {
    moduleNodes[i].module->_ara = this;
    moduleNodes[i].module->araInit();
  }
}


void AraCommander::mainLoop() {
  while (true) {
    #ifdef DISPLAY_ACPS
      indicator.displayAcps();
    #else
      #if defined(__AVR)
      indicator.ledFlash();
      #endif
    #endif

    if (routinesTimerReset) {
      routinesTimer.reset();
      routinesTimerReset = false;
    }

    execCmd();

    if (!cmdQueue.next() || routinesTimer.reached()) {
      routinesTimerReset = true;
      execRoutines();
    }
  }
}


void AraCommander::execRoutines() {
  for (uint8_t i=0; i<numRecurrentModules; i++) {
    moduleNodes[i].module->araExecRecurrent();
  }
}


void AraCommander::execCmd() {
  AraCmd* cmd = cmdQueue.get();
  if (cmd == nullptr) return;

  ModuleNode& currentModuleNode = moduleNodes[cmd->calleeId];

  if (!currentModuleNode.isBuzy) {
    switch (cmd->status) {
      case AraCmd::WAITING:
        currentModuleNode.isBuzy = true;
        cmd->status = AraCmd::BUZY;
        break;
      
      default:
        cmdQueue.remove();
        return;
    }
  }

  if (currentModuleNode.isBuzy) {
    switch (cmd->status) {
      case AraCmd::WAITING:
        return;
      
      case AraCmd::BUZY: {
        // module execution
        AraOutput moduleExec = currentModuleNode.module->araExecCmd(cmd->parameters);

        switch (moduleExec.exitCode) {
          case araexcode::RERUN:
            return;
          default:
            if (moduleExec.output != nullptr) {
              // give output to caller
              moduleNodes[cmd->callerId].module->araGiveCalleeOutput(
                cmd->calleeId, moduleExec.output
              );
            }

            cmdQueue.remove();
            currentModuleNode.isBuzy = false;
            return;
        }
      }

      default:
        cmdQueue.remove();
        return;
    }
  } 
}


bool AraCommander::addCmd(uint8_t calleeId, uint8_t callerId, InputParameters* parameters) {
  if ((calleeId >= numModules) || (callerId >= numModules)) return false;

  AraCmd cmd = {calleeId, callerId, parameters};
  return cmdQueue.add(cmd);
}
