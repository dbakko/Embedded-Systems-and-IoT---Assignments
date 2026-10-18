#include "output.h"
#include "config.h"
#include <Arduino.h>

void initOutput(){
  // pinMode(POT_PIN, INPUT); va nell'input
  pinMode(LED_R1_PIN, OUTPUT);
  pinMode(LED_G1_PIN, OUTPUT);
  pinMode(LED_R2_PIN, OUTPUT);
  pinMode(LED_G2_PIN, OUTPUT);
}

void toggleLed(uint8_t pin){
  //TODO:
}
