#include "Config.h"
#include "Display.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

namespace Display {
  //initialize the liquid crystal library
  //the first parameter is  the I2C address
  LiquidCrystal_I2C lcd(0x27,  LCD_COLS, LCD_ROWS);

  void SetupDisplay(){
    lcd.init();
    lcd.backlight();
  }

  void displayScrollingMessage(const char *str, size_t startIndex){
    char displayStr[LCD_COLS + 1];

    size_t stringLen = strlen(str);
    if (stringLen == 0) return;

    for(size_t i = 0; i < LCD_COLS; i++){
      displayStr[i] = str[(startIndex + i) % stringLen];
    }

    displayStr[LCD_COLS] = '\0';
    lcd.setCursor(0,0);
    lcd.print(displayStr);

    Serial.print(displayStr);
  }
}
