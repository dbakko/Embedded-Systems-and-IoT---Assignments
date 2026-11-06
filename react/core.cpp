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
unsigned long difficultyEntryTime = 0;
int selectedDifficulty = 1;

void checkPotentiometer();

void ledFade(int led1, int led2);
void deepSleep();
void setDifficulty();

void initCore(){
  Serial.begin(9600);
}

void intro(){
  if (isJustEnteredInState()){
    Serial.println("Intro...");
    initialTime= millis();
  }

  const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";

  displayScrollingMessage(welcomeMessage, millis());
  ledFade(LED_R1_PIN, LED_R2_PIN);
  if (millis() - initialTime >= MAX_TIME_IN_INTRO_STATE){
    changeState(DEEP_SLEEP_STATE);
    return;
  }

  if (isButtonPressed(0) && isButtonPressed(1)){
    digitalWrite(LED_R1_PIN, LOW);
    digitalWrite(LED_R2_PIN, LOW);
    resetInput();
    changeState(SET_DIFFICULTY_STATE); 
    return;
  }
}

void setDifficulty(){
  if (isJustEnteredInState()){
    Serial.println("Entrato in Selezione difficoltà...");
    difficultyEntryTime = millis();
    resetInput();
  }

  displayScrollingMessage("Choose difficulty: 1-easy 4-hard", millis());
  
  // Lettura potenziometro
  long potValue = analogRead(POT_PIN);
  if (potValue < 300) {
    selectedDifficulty = 1;
  } else if (potValue < 500) {
    selectedDifficulty = 2;
  } else if (potValue < 800) {
    selectedDifficulty = 3;
  } else {
    selectedDifficulty = 4;
  }
  // Mostra il livello attuale sulla seconda riga
  char buffer[16];
  sprintf(buffer, "Level: %d", selectedDifficulty);
  displayMessage(buffer, 0, 1);

  // Dopo 5 secondi, la difficoltà viene confermata e parte la partita
  if (millis() - difficultyEntryTime >= 10000) {
    Serial.print("Difficolta' confermata automaticamente: ");
    Serial.println(selectedDifficulty);
    
    // Passa allo stato di gioco vero e proprio
    changeState(GAME_STATE);
    return;
  }
}

void game(){
  if (isJustEnteredInState()) {
    Serial.println("Siamo nello stato di gioco farlocco!");
    clearDisplay();
    displayMessage("      Go!      ",0,0);
  }
}

void deepSleep(){ 
  if (isJustEnteredInState()) {
    Serial.println("Entro in Deep Sleep...");
    delay(100);
    // Disattiva led e display
    digitalWrite(LED_R1_PIN, LOW);
    digitalWrite(LED_R2_PIN, LOW);
    turnOffDisplay();

    // Entra nello stato di sleep, addormenta la CPU
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_cpu(); 

    // Risveglio
    sleep_disable();
    initDisplay();
    Serial.println("Risvegliato! Ritorno all'intro.");
    changeState(INTRO_STATE); 
    resetInput();           
  }
}




