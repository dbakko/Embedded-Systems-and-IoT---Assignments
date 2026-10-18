#include "config.h"
#include "core.h"
#include "kernel.h"
#include "display.h"

#define POTENZIOMETER_PIN A0

void setup() {
  initCore();
  changeState(INTRO_STATE);
  // pinMode(POTENZIOMETER_PIN, INPUT);
  // pinMode(2, OUTPUT);
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
  // digitalWrite(2, HIGH); //accende led collegato a D2
}

