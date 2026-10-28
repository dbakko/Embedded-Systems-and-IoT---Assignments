#ifndef __DISPLAY__
#define __DISPLAY__

#include <Arduino.h>

void initDisplay();
void displayScrollingMessage(const char *str, long time);
void turnOffDisplay();
void displayMessage();
void displayScores();


#endif
