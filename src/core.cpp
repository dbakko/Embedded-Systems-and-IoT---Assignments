#include "config.h"
#include "core.h"
#include "kernel.h"
#include "display.h"
#include "output.h"
#include <Arduino.h>

size_t index = 0;

void initCore(){
  Serial.begin(9600);
  Display::SetupDisplay();
  initOutput();
  toggleLed(LED_R1_PIN); //prova led
}

void intro(){
  if (isJustEnteredInState()){
    Serial.println("Intro...");
  }
  const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";

  Display::displayScrollingMessage(welcomeMessage, index++);
  if(index > sizeof(welcomeMessage) - 1) index = 0;
}

