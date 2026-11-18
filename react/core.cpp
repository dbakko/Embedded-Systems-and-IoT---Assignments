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
unsigned long roundResultEntryTime = 0;
int selectedDifficulty = 1;
int roundTime = T1;
int roundTimeDecreaseFactor = BASE_DECREASE_FACTOR;
int p1score = 0;
int p2score = 0;
int p1clicks = 0;
int p2clicks = 0;
unsigned long p1winTime = 0;
unsigned long p2winTime = 0;
int randomNum = 0;
bool p1Penalized = false;
bool p2Penalized = false;
bool roundErrorOccurred = false;


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
    delay(1000);
  }
  changeState(ROUND_STATE);
} // forse ci conviene ancche qui definire un MAX_TIME_IN_GAME_STATE e togliere il delay...

void gameRound() {
  // Numero random da indovinare
  char buffer[16];
  if (isJustEnteredInState()) {
    roundEntryTime = millis();
    clearDisplay();
    resetInput();
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
    p1Penalized = false;
    p2Penalized = false;
    roundErrorOccurred = false;
  }

  // Penalizzazione per pressione anticipata
  if(millis() - roundEntryTime < roundRandomWaitTime){
    if (!roundErrorOccurred) {
      if(isButtonPressed(0)) {
        p1Penalized = true;
        roundErrorOccurred = true;
        p1score--;
        Serial.println("P1 ha premuto troppo presto!");
        changeState(ROUND_RESULT);
        return;
      }
      if(isButtonPressed(1)) {
        p2Penalized = true;
        roundErrorOccurred = true;
        p2score--;
        Serial.println("P2 ha premuto troppo presto!");
        changeState(ROUND_RESULT);
        return;
      }
    }
    return;
  }
  displayMessage(buffer, 0, 0); // mostra il numero estratto ai giocatori

//TODO: ad ogni round fai decrementare T1 a seconda della difficoltà
  if(millis() - (roundEntryTime + roundRandomWaitTime) < roundTime){
    if(isButtonPressed(0)){ // p1 button
      p1clicks++;
      resetInput(0);
      
      // P1 Penalità per aver premuto più volte
      if(p1clicks > randomNum && !roundErrorOccurred) {
        p1Penalized = true;
        roundErrorOccurred = true;
        p1score--;
        Serial.println("P1 ha cliccato troppe volte!");
        resetInput();
        changeState(ROUND_RESULT);
        return;
      }

      if(p1clicks == randomNum && p1winTime == 0){
        p1winTime = millis();
      } /*else if(p1winTime > 0){ // p1 ha cliccato troppe volte
        p1winTime = 0; //per ora semplicemente metto il suo tempo di vittoria a 0 che significa che ha perso
        }*/
    }
    if(isButtonPressed(1)){ // p2 button
      p2clicks++;
      resetInput(1);

    // P2 Penalità per aver premuto più volte 
    if(p2clicks > randomNum && !roundErrorOccurred) {
      p2Penalized = true;
      roundErrorOccurred = true;
      p2score--;
      Serial.println("P2 ha cliccato troppe volte!");
      resetInput();
      changeState(ROUND_RESULT);
      return;
      }
      
    if(p2clicks == randomNum && p2winTime == 0){
      p2winTime = millis();
      } /*else if(p2winTime > 0){
        p2winTime = 0;
      }*/
    }

  } else { // game finito
    changeState(ROUND_RESULT);
  }

}

void roundResult(){
  if(isJustEnteredInState()){
    roundResultEntryTime = millis();
    Serial.println("Entrato in round result state");
    displayScores(p1score, p2score);
    
    // Check se qualcuno perde
    if(p1Penalized){
      Serial.println("P1 penalizzato!");
      displayMessage("P1 penalty!", 0, 0);
      digitalWrite(LED_R1_PIN, HIGH); // Accende il LED rosso di P1 (L2)
    } 
    else if(p2Penalized){
      Serial.println("P2 penalizzato!");
      displayMessage("P2 penalty!", 0, 0);
      digitalWrite(LED_R2_PIN, HIGH); // Accende il LED rosso di P2 (L3)
    }
    // Check se qualcuno vince
    else if(p1winTime > 0 && (p2winTime == 0 || p1winTime < p2winTime)){
      p1score++;
      Serial.println("P1 vince!");
      displayMessage("    P1 wins!    ",0,0);
      digitalWrite(LED_G1_PIN, HIGH);
    } 
    else if(p2winTime > 0 && (p1winTime == 0 || p2winTime < p1winTime)){
      p2score++;
      Serial.println("P2 vince!");
      displayMessage("    P2 wins!    ",0,0);
      digitalWrite(LED_G2_PIN, HIGH);
    }
    else { 
      displayMessage("  Time's up!   ", 0, 0);
    }
    
    displayScores(p1score, p2score);
    //changeState(END_STATE); //da fare per il game over
  }
  
  if (millis() - roundResultEntryTime >= MAX_TIME_IN_RESULT_STATE){
    // aggiorna roundTime
    if(roundTime > TMIN){ // TMIN e' il cap minimo al tempo del round
      roundTime = roundTime - roundTimeDecreaseFactor * selectedDifficulty;
    }
    Serial.println(String("Round Time: ") + roundTime);
    digitalWrite(LED_G1_PIN, LOW);
    digitalWrite(LED_G2_PIN, LOW);
    digitalWrite(LED_R1_PIN, LOW);
    digitalWrite(LED_R2_PIN, LOW);
    changeState(ROUND_STATE);
  }
}


