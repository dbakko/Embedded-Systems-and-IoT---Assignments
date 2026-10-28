#include "config.h"
#include "core.h"
#include "kernel.h"
#include "display.h"
#include "input.h"
#include "output.h"
#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>

unsigned long initialTime = 0;

void ledFade(int led1, int led2);
void deepSleepState();

void initCore(){
  Serial.begin(9600);
  //toggleLed(LED_R1_PIN); //prova led
}

void intro(){
  if (isJustEnteredInState()){
    Serial.println("Intro...");
    initialTime= millis();
  }

  if (isButtonPressed(0) && isButtonPressed(1)){
    //da implementare con gli stati
  }

  // prova bottoni
 /* if (isButtonPressed(0)){
    Serial.println("BOTTONE SINISTRO PREMUTO");
    resetInput();
  }
  if (isButtonPressed(1)){
    Serial.println("BOTTONE DESTRO PREMUTO");
    resetInput();
  }
*/
  const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";

  displayScrollingMessage(welcomeMessage, millis());
  ledFade(LED_R1_PIN, LED_R2_PIN);
  if (millis() - initialTime >= MAX_TIME_IN_INTRO_STATE){
    deepSleepState();
  }
}

void game(){
};

void deepSleepState(){ //nuovo stato?
  Serial.println("Entro in Deep Sleep...");
  delay(1000);
  digitalWrite(LED_R1_PIN, LOW);
  digitalWrite(LED_R2_PIN, LOW);
  turnOffDisplay();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
  //Quando viene risvegliato, forse da spostare!
  initDisplay();
  Serial.println("Risvegliato! Ritorno all'intro.");
  initialTime = millis(); // Resetta il timer dei 10 secondi
  resetInput();           // Pulisce lo stato dei bottoni
}

