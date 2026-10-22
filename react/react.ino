#include "config.h"
#include "input.h"
#include "core.h"
#include "kernel.h"
#include "display.h"

// void prova(){
//   Serial.println("Button Pressed");
// }
//
// void (*prova_ptr)();

void setup() {
  initCore();
  initInput();
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
