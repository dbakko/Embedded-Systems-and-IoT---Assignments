#ifndef __DISPLAY__
#define __DISPLAY__

#include <Arduino.h>

namespace Display {
  void SetupDisplay();
  void displayScrollingMessage(const char *str, size_t startIndex);
}

#endif
