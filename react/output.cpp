#include "output.h"
#include "config.h"
#include <Arduino.h>

int brightness = 0; //queste costanti dove possiamo metterle?
int fadeAmount = 5;

void initOutput(){
  pinMode(LED_R1_PIN, OUTPUT);
  pinMode(LED_G1_PIN, OUTPUT);
  pinMode(LED_R2_PIN, OUTPUT);
  pinMode(LED_G2_PIN, OUTPUT);
}

void ledFade(int led1, int led2){ //funzione accessoria, da mettere in un nuovo file/file diverso o teniamo qui?
  analogWrite(led1, brightness);
  analogWrite(led2, 255 - brightness);
  brightness = brightness + fadeAmount;
  if ( brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount;
  }
  delay(30);

}

void toggleLed(uint8_t pin){ //dovrei avere toggleLed oppure due funzioni (una per accendere e un altra per spegnere)?
  //TODO:
  digitalWrite(pin, HIGH);
}
