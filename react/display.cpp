#include "config.h"
#include "display.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

//initialize the liquid crystal library
//the first parameter is  the I2C address
LiquidCrystal_I2C lcd(0x27,  LCD_COLS, LCD_ROWS);

void initDisplay(){
  lcd.init();
  lcd.backlight();
}

void turnOffDisplay() {
  lcd.noDisplay();      
  lcd.noBacklight();    
}

void displayMessage(const char *str, int col, int row) { // Go! 
  lcd.setCursor(col, row);
  lcd.print(str);
}

void displayScores(int score1, int score2) { // Per i punteggi
  // Pulisci l'intera riga in basso prima di scrivere i nuovi punteggi (supponendo 16 colonne)
  lcd.setCursor(0, 1);
  lcd.print("                "); 
  
  // Stampa il punteggio del Player 1 a sinistra
  lcd.setCursor(0, 1);
  lcd.print("P1:");
  lcd.print(score1);

  // Stampa il punteggio del Player 2 a destra (allineato verso la fine della riga)
  lcd.setCursor(10, 1);
  lcd.print("P2:");
  lcd.print(score2);
}

void displayScrollingMessage(const char *str, long time){
  char displayStr[LCD_COLS + 1];

  size_t stringLen = strlen(str);
  if (stringLen == 0) return;

  static long lastTime = 0;
  static size_t index = 0;

  long deltaTime = time - lastTime;
  if(deltaTime >= DISPLAY_REFRESH_MILLIS){ //update index and lastTime
    lastTime = time;
    index++;
  }

  if(index > stringLen - 1) index = 0;

  for(size_t i = 0; i < LCD_COLS; i++){
    displayStr[i] = str[(index + i) % stringLen];
  }

  displayStr[LCD_COLS] = '\0';
  lcd.setCursor(0,0);
  lcd.print(displayStr);
}
