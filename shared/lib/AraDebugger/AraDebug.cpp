#ifdef DEBUG
#include <AraDebug.h>

size_t freeMem() {
  size_t d = 1;
  void* allcPtr = malloc(d);
  void* lastAllcPtr = allcPtr;

  while (allcPtr != nullptr) {
    lastAllcPtr = allcPtr;
    allcPtr = realloc(allcPtr, ++d);
  }
  
  free(lastAllcPtr);
  return --d;
}

#endif
