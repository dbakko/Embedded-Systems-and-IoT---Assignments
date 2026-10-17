#include "Game.h"
#include "Display.h"

// React game logic
namespace Game {
  const char welcomeMessage[] = "Welcome to the React! Game. Press Buttons to Start. ";
  size_t index = 0;

  void Begin(){
    //initialize Game Logic
  }

  void Update(){
    delay(300);
    Display::displayScrollingMessage(welcomeMessage, 0);
    if(index > sizeof(welcomeMessage) - 1) index = 0;
  }
}
