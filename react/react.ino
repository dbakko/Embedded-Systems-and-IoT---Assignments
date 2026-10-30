#include "config.h"
#include "input.h"
#include "core.h"
#include "kernel.h"
#include "output.h"
#include "display.h"

void setup() {
  initCore();
  initInput();
  initDisplay();
  initOutput();
  changeState(INTRO_STATE);
}

void loop() {
  checkPotentiometer();
  updateStateTime();
  switch(getCurrentState()) {
    case INTRO_STATE:
      intro();
      break;
    case GAME_STATE:
      game();
      break;
    //aggiungi altri casi qua
  }
}
