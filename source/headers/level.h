#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include "types.h"
void SetupLevel(char* backgroundImage, char* levelMusicPath, Texture2D *backgroundTexture, Music *levelMusic);
void MainLoop(Entity *player, int *isNights, int *pointCounter, int *ideyaCounter, int overallTime, int screenWidth, int screenHeight, Camera2D *camera, Texture2D backgroundTexture, Enemy* enemies);
#endif