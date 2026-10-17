#include <cstddef>
#include <Arduino.h>

namespace Display {
  void SetupDisplay();
  void displayScrollingMessage(const char *str, size_t startIndex);
}

