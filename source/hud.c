#include <stdio.h>
#include "raylib.h"

//definitions
void DrawTimer(int isNights, int currentTime, int overallTime, int screenWidth, int screenHeight);
void DrawIdeyas(int ideyaCounter, int screenWidth, int screenHeight);
void DrawPoints(int pointsCounter, int screenWidth, int screenHeight);

//main function
void HUD(int isNights, int pointCounter, int ideyaCounter, int currentTime, int overallTime, int screenWidth, int screenHeight) {
    DrawTimer(isNights, currentTime, overallTime, screenWidth, screenHeight);
    DrawIdeyas(ideyaCounter, screenWidth, screenHeight);
    DrawPoints(pointCounter, screenWidth, screenHeight);
}

//drawing timer
void DrawTimer(int isNights, int currentTime, int overallTime, int screenWidth, int screenHeight) {
    char text[4];
    //check for mode
    if (isNights == 0) {
        snprintf(text, sizeof(text), "%d", overallTime);
    } else {
        snprintf(text, sizeof(text), "%d", overallTime-currentTime);
    }
    int textWidth = MeasureText(text, 40);
    int posY = 70;
    int posX = (screenWidth - textWidth) / 2;
    DrawText(text, posX, posY, 40, BLACK);
}

//drawing ideyas
void DrawIdeyas(int ideyaCounter, int screenWidth, int screenHeight) {
    char text[4];
    snprintf(text, sizeof(text), "%d", ideyaCounter);
    int textWidth = MeasureText(text, 40);
    int posX = (screenWidth - textWidth) / 8;
    int posY = 70;
    DrawText(text, posX, posY, 40, BLACK);
}

//drawing points
void DrawPoints(int pointsCounter, int screenWidth, int screenHeight) {
    char text[4];
    snprintf(text, sizeof(text), "%d", pointsCounter);
    int textWidth = MeasureText(text, 40);
    int posX = screenWidth - textWidth - (screenWidth / 8);
    int posY = 70;
    DrawText(text, posX, posY, 40, BLACK);
}
