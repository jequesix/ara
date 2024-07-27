// AraEngine Debugger
// (c) 2024 Jerome Lavoie

#pragma once

#ifdef DEBUG

#if defined (__AVR)
#include <Arduino.h>
#elif defined(__linux)
#include <iostream>
#endif

size_t freeMem();

#if defined (__AVR)

#define debug_init(baud_rt) {Serial.begin(baud_rt);}

#define debug_msg(str) {Serial.print(str);}
#define debug_msg_nl(str) {Serial.println(str);}
#define debug_msg_f(str) {Serial.print(F(str));}
#define debug_msg_nl_f(str) {Serial.println(F(str));}

#elif defined(__linux)

#define debug_msg(str) {std::cout << str;}
#define debug_msg_nl(str) {std::cout << str << std::endl;}
#define debug_msg_f(str) {debug_msg(str)}
#define debug_msg_nl_f(str) {debug_msg_nl(str)}

#endif

#define debug_freemem() {debug_msg("Free Memory: "); debug_msg_nl(freeMem());}

#define debug_assert(var, condition) {  \
    if (!condition) {                   \
        debug_msg_f("Assert failed: "); \
        debug_msg_f(#condition);        \
        debug_msg_f(" -> (");           \
        debug_msg_f(#var);              \
        debug_msg_f(" = ");             \
        debug_msg(var);                 \
        debug_msg_nl_f(")");            \
    }                                   \
}                                       \

#else

#if defined(__AVR)
#define debug_init(baud_rt)
#endif

#define debug_msg(str)
#define debug_msg_nl(str)
#define debug_msg_f(str)
#define debug_msg_nl_f(str)
#define debug_assert(var, condition)
#define debug_freemem()

#endif
