#include "output.h"
#include "config.h"
#include <Arduino.h>

int brightness = 0; 
int fadeAmount = 5;

void initOutput(){
  pinMode(LED_R1_PIN, OUTPUT);
  pinMode(LED_G1_PIN, OUTPUT);
  pinMode(LED_R2_PIN, OUTPUT);
  pinMode(LED_G2_PIN, OUTPUT);
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