#pragma once

#if defined(__AVR)
#include <Arduino.h>
#elif defined(__linux)
#include <cstring>
#endif

#include <AraDebug.h>
#include "types.hpp"


template <typename T>
class FastQueue {
  public:
    // min: 1, max: INT16_MAX (2^15 - 1)
    FastQueue(uint16_t numElements) {
      #if defined(__AVR)
      constrain(numElements, (uint8_t)1, (uint16_t)INT16_MAX);
      #elif defined(__linux)
      if (numElements > INT16_MAX) numElements = INT16_MAX;
      else if (numElements < 1) numElements = 1;
      #endif

      elements = new T[numElements];
      maxElementIndex = numElements - 1;
    }


    // returns nullptr if queue is empty
    T* get() {
      if (head > -1) {
        return &elements[selectedElement];
      }

      return nullptr;
    }


    // goes back to the beginning of the queue if end of non-empty elements cluster is reached
    bool next() {
      if (++selectedElement > head) {
        selectedElement = 0;
        return false;
      }

      return true;
    }


    // returns false if queue is full, true otherwise
    bool add(T _element) {
      head++;

      if (head > maxElementIndex) {
        head = maxElementIndex;
        return false;
      }

      memcpy(&elements[head], &_element, sizeof(T));
      return true;
    }


    // remove selected element
    void remove() {
      if (head > -1) {
        memcpy(&elements[selectedElement], &elements[head--], sizeof(T));
        return;
      }
    }


  private:
    T *elements;
    int16_t maxElementIndex; 
    int16_t selectedElement = 0;
    int16_t head = -1;
};
