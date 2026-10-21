#include "config.h"
#include "core.h"
#include "kernel.h"
#include "display.h"
#include "input.h"
#include "output.h"
#include <Arduino.h>

void initCore(){
  Serial.begin(9600);
  SetupDisplay();
  initOutput();
  toggleLed(LED_R1_PIN); //prova led
}

void intro(){
  if (isJustEnteredInState()){
    Serial.println("Intro...");
  }

  // prova bottoni
  if (isButtonPressed(0)){
    Serial.println("BOTTONE SINISTRO PREMUTO");
    resetInput();
  }
  if (isButtonPressed(1)){
    Serial.println("BOTTONE DESTRO PREMUTO");
    resetInput();
  }

  static size_t index = 0; //viene allocata solo alla prima chiamata
  const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";

  displayScrollingMessage(welcomeMessage, index++);
  if(index > sizeof(welcomeMessage) - 1) index = 0;
}

