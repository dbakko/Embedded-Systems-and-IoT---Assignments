#ifndef __CORE__
#define __CORE__

//Definisci gli stati del gioco
#define INTRO_STATE 1 //print welcome message
#define GAME_STATE 2
// #define DEEP_SLEEP_STATE 3

/* core business logic */

void initCore();
void intro();
void game();
void checkPotentiometer();

#endif
