#ifndef __CORE__
#define __CORE__

//Definisci gli stati del gioco
#define INTRO_STATE 1 //print welcome message
#define SET_DIFFICULTY_STATE 2
#define GAME_STATE 3
#define DEEP_SLEEP_STATE 4

/* core business logic */

void initCore();
void intro();
void game();
void setDifficulty();
void deepSleep();

#endif
