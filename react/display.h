#ifndef __DISPLAY__
#define __DISPLAY__

#include <Arduino.h>

void initDisplay();
void displayScrollingMessage(const char *str, long time);
void turnOffDisplay();
void displayMessage(const char *str, int col, int row);
void displayScores(int score1, int score2);


#endif
