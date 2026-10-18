#include "Config.h"
#include "core.h"
#include "kernel.h"
#include "Display.h"

#define POTENZIOMETER_PIN A0

void setup() {
  initCore();
  changeState(INTRO_STATE);
  // pinMode(POTENZIOMETER_PIN, INPUT);
}

void loop() {
  updateStateTime();
  switch(getCurrentState()) {
    case INTRO_STATE:
      intro();
      break;
    //aggiungi altri casi qua
  }
  // int value = analogRead(POTENZIOMETER_PIN);
  // Serial.println(value);
}

