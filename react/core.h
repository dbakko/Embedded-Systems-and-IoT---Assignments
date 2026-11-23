#ifndef __CORE__
#define __CORE__

// Definisci gli stati del gioco
#define INTRO_STATE 1 
#define DEEP_SLEEP_STATE 2
#define SET_DIFFICULTY_STATE 3
#define GAME_STATE 4
#define ROUND_STATE 5
#define ROUND_RESULT 6
#define END_STATE 7


/* core business logic */

void initCore();
void intro();
void game();
void setDifficulty();
void deepSleep();
void gameRound();
void roundResult();
void endGame();

#endif
