#pragma once

#if defined(__linux) || defined(__APPLE__)
#include <stdint.h>
#endif


// exit codes used by ara componenets
enum class araexcode {
  DONE = 0,
  RERUN = 1,
  FAIL = 2
};


// structs to improve the clarity of parameters and output transmission
struct InputParameters {};
struct OutputParameters {};


// combines exit code and output
struct AraOutput {
  araexcode exitCode = araexcode::DONE;
  OutputParameters* output = nullptr;
};
