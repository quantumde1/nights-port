#ifndef HUD_H
#define HUD_H

#include "raylib.h"

//interface
void HUD(int isNights, int pointCounter, int ideyaCounter, int currentTime, int overallTime, int screenWidth, int screenHeight);
void GraphicalMenu(int screenWidth, int screenHeight, int *gameState);
#endif