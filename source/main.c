#include "raylib.h"
//engine
#include "headers/types.h"
#include "headers/level.h"

Enemy enemies[MAX_ENEMIES];

int main() {
    //window init
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    InitWindow(screenWidth, screenHeight, "Tsuki-no-Me");
    SetTargetFPS(60);
    InitAudioDevice();
    ToggleFullscreen();
    int isNights = 1;
    int ideyaCounter = 0;
    int overallTime = 120;
    int pointCounter = 0;
    Camera2D camera = { 0 };
    camera.zoom = 3.0f;
    //creating initial character position
    Entity player = {
        .position = { screenWidth / 2.0f, screenHeight / 2.0f },
        .velocity = { 0.0f, 0.0f },
        .acceleration = { 0.0f, 0.0f }
    };
    Music levelMusic;
    Texture2D backgroundTexture;
    SetupLevel("resources/test_background.png", "resources/out.mp3", &backgroundTexture, &levelMusic);
    while (WindowShouldClose() == false) {
        UpdateMusicStream(levelMusic);
        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        MainLoop(&player, &isNights, &pointCounter, &ideyaCounter, overallTime, screenWidth, screenHeight, &camera, backgroundTexture, enemies);
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}