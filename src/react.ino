#include "Config.h"
#include "Game.h"
#include "Display.h"

const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";

void setup() {
  Serial.begin(9600);
  Display::SetupDisplay();
}

void loop() {
  Game::Update();
}

