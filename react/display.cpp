#include "config.h"
#include "display.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define DISPLAY_REFRESH_MILLIS 3000

//initialize the liquid crystal library
//the first parameter is  the I2C address
LiquidCrystal_I2C lcd(0x27,  LCD_COLS, LCD_ROWS);

void SetupDisplay(){
  lcd.init();
  lcd.backlight();
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
