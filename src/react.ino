#include "config.h"
#include "core.h"
#include "kernel.h"
#include "display.h"

void setup() {
  initCore();
  changeState(INTRO_STATE);
}

void loop() {
  updateStateTime();
  switch(getCurrentState()) {
    case INTRO_STATE:
      intro();
      break;
    //aggiungi altri casi qua
  }
}
