#include "Config.h"
#include "Display.h"

const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";
size_t index = 0;

void setup() {
  Serial.begin(9600);
  SetupDisplay();
}

void loop() {
  delay(300);
  displayScrollingMessage(welcomeMessage, index++);
  if(index > sizeof(welcomeMessage) - 1) index = 0;
}

