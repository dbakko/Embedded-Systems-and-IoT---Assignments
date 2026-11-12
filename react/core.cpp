#include "config.h"
#include "core.h"
#include "kernel.h"
#include "display.h"
#include "input.h"
#include "output.h"
#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>

unsigned long introEntryTime = 0;
unsigned long difficultyEntryTime = 0;
unsigned long roundEntryTime = 0;
unsigned long roundRandomWaitTime = 0;
int selectedDifficulty = 1;
int p1score = 0;
int p2score = 0;
int p1clicks = 0;
int p2clicks = 0;
unsigned long p1winTime = 0;
unsigned long p2winTime = 0;
int randomNum = 0;

void checkPotentiometer();

void ledFade(int led1, int led2);
void deepSleep();
void setDifficulty();
void gameRound();

void initCore(){
  Serial.begin(9600);
}

void intro(){
  if (isJustEnteredInState()){
    Serial.println("Intro...");
    introEntryTime = millis();
  }

  const char welcomeMessage[] = "  Welcome to the React! Game. Press Buttons to Start. ";

  displayScrollingMessage(welcomeMessage, millis());
  ledFade(LED_R1_PIN, LED_R2_PIN);
  if (millis() - introEntryTime >= MAX_TIME_IN_INTRO_STATE){
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

void deepSleep(){
  if (isJustEnteredInState()) {
    Serial.println("Entro in Deep Sleep...");
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

void setDifficulty(){
  if (isJustEnteredInState()){
    Serial.println("Entrato in Selezione difficoltà...");
    difficultyEntryTime = millis();
    resetInput();
  }

  displayScrollingMessage(" Choose difficulty: 1-easy 4-hard", millis());

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
  if (millis() - difficultyEntryTime >= MAX_TIME_IN_DIFFICULTY_SELECT_STATE) {
    Serial.print("Difficolta' confermata automaticamente: ");
    Serial.println(selectedDifficulty);

    // Passa allo stato di gioco vero e proprio
    changeState(GAME_STATE);
    return;
  }
}

void game(){
  if (isJustEnteredInState()) {
    Serial.println("Siamo nello stato di gioco!");
    clearDisplay();
    displayMessage("      Go!      ",0,0);
    displayScores(p1score, p2score);
    delay(1000);
  }
  clearDisplay();
  changeState(ROUND_STATE);
}

void gameRound() {
  // Numero random da indovinare
  char buffer[16];
  if (isJustEnteredInState()) {
    roundEntryTime = millis();
    clearDisplay();
    // Spengo i led
    digitalWrite(LED_R1_PIN, LOW);
    digitalWrite(LED_R2_PIN, LOW);
    digitalWrite(LED_G1_PIN, LOW);
    digitalWrite(LED_G2_PIN, LOW);

    Serial.print("Round avviato. Numero random estratto: ");

    // Genera un tempo di attesa casuale tra 0 e MAX_WAIT millisecondi
    roundRandomWaitTime = random(0, MAX_TIME_WAIT_ROUND_STATE + 1);

    // inizializza le variabili del round
    randomNum = random(1, 4);
    Serial.println(randomNum);
    sprintf(buffer, "       %d   ", randomNum);
    p1winTime = 0;
    p2winTime = 0;
    p1clicks = 0;
    p2clicks = 0;
  }
  //aspetta roundRandomTime secondi
  if(millis() - roundEntryTime < roundRandomWaitTime){
    resetInput(); // se i giocatori cliccano prima che il numero venga mostrato non assegnare il click
    return;
  }
  displayMessage(buffer, 0, 0); // mostra il numero estratto ai giocatori

  if(millis() - (roundEntryTime + roundRandomWaitTime) < T1){
    if(isButtonPressed(0)){ // p1 button
      p1clicks++;
      resetInput(0);
      if(p1clicks == randomNum && p1winTime == 0){
        p1winTime = millis();
      } else if(p1winTime > 0){
        p1winTime = 0;
      }
    }
    if(isButtonPressed(1)){ // p2 button
      p2clicks++;
      resetInput(1);
      if(p2clicks == randomNum && p2winTime == 0){
        p2winTime = millis();
      } else if(p2winTime > 0){
        p2winTime = 0;
      }
    }
  } else {
    //check se qualcuno vince
    if(p1winTime > 0 && (p2winTime == 0 || p1winTime < p2winTime)){
      p1score++;
      Serial.println("P1 vince!");
      displayScores(p1score, p2score);
    } else if(p2winTime > 0 && (p1winTime == 0 || p2winTime < p1winTime)){
      p2score++;
      Serial.println("P2 vince!");
      displayScores(p1score, p2score);
    }
    changeState(GAME_STATE); // dovrei andare in un END_STATE veramente
  }
}
