#include <stdio.h>
#include "raylib.h"

void DrawHUDText(const char* text, int fontSize, Color color, Vector2 position) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, position.x, position.y, fontSize, color);
}

void DrawTimer(int isNights, int currentTime, int overallTime, int screenWidth, int screenHeight) {
    char text[20];
    if (isNights == 0) {
        snprintf(text, sizeof(text), "Time: %d", overallTime);
    } else {
        snprintf(text, sizeof(text), "Time: %d", overallTime - currentTime);
    }
    Vector2 position = { (screenWidth - MeasureText(text, 40)) / 2.0f, 70 };
    DrawHUDText(text, 40, YELLOW, position);
}

void DrawIdeyas(int ideyaCounter, int screenWidth, int screenHeight) {
    char text[9];
    snprintf(text, sizeof(text), "Ideya: %d", ideyaCounter);
    Vector2 position = { screenWidth / 8.0f, 70 };
    DrawHUDText(text, 40, YELLOW, position);
}

void DrawPoints(int pointsCounter, int screenWidth, int screenHeight) {
    char text[16];
    snprintf(text, sizeof(text), "Points: %d", pointsCounter);
    int textWidth = MeasureText(text, 40);
    Vector2 position = { screenWidth - textWidth - (screenWidth / 8.0f), 70 };
    DrawHUDText(text, 40, YELLOW, position);
}

//main function
void HUD(int isNights, int pointCounter, int ideyaCounter, int currentTime, int overallTime, int screenWidth, int screenHeight) {
    DrawTimer(isNights, currentTime, overallTime, screenWidth, screenHeight);
    DrawIdeyas(ideyaCounter, screenWidth, screenHeight);
    DrawPoints(pointCounter, screenWidth, screenHeight);
}