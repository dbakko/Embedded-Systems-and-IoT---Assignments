#include "config.h"
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
  //initInput(); TODO:
  changeState(INTRO_STATE);
  // pinMode(7, INPUT);
  // enableInterrupt(7, prova
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
