#include <LiquidCrystal_I2C.h>

#define LCD_COLS 16
#define LCD_ROWS 2

//initialize the liquid crystal library
//the first parameter is  the I2C address
LiquidCrystal_I2C lcd(0x27,  LCD_COLS, LCD_ROWS);

const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";
size_t index = 0;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}

void loop() {
  delay(300);
  displayScrollingMessage(welcomeMessage, index++);
  if(index > sizeof(welcomeMessage) - 1) index = 0;
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
