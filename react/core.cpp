#include "config.h"
#include "core.h"
#include "kernel.h"
#include "display.h"
#include "input.h"
#include "output.h"
#include <Arduino.h>
int brightness = 0;
int fadeAmount = 5;

void ledFade(int led1, int led2);

void initCore(){
  Serial.begin(9600);
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

  const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";

  displayScrollingMessage(welcomeMessage, millis());
  ledFade(LED_R1_PIN, LED_R2_PIN);
}

void ledFade(int led1, int led2){
  analogWrite(led1, brightness);
  analogWrite(led2, 255 - brightness);
  brightness = brightness + fadeAmount;
  if ( brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);
}

