#include "raylib.h"

void StartScreen(int screenWidth, int screenHeight, short *gameState);

void GraphicalMenu(int screenWidth, int screenHeight, short *gameState) {
    StartScreen(screenWidth, screenHeight, gameState);
}

void StartScreen(int screenWidth, int screenHeight, short *gameState) {
    ClearBackground(BLACK);
    char *text = "Start game";
    int textWidth = MeasureText(text, 30);
    int posY = screenHeight - (screenHeight / 8);
    int posX = (screenWidth - textWidth) / 2;
    DrawText(text, posX, posY, 30, WHITE);
    if (IsKeyPressed(KEY_ENTER)) {
        *gameState = 1;
    }
}
