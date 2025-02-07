#include "raylib.h"
//engine
#include "headers/controller.h"
#include "headers/hud.h"
#include "headers/trail.h"
#include "headers/types.h"

void MainLoop(Entity *player, int isNights, int pointCounter, int ideyaCounter, int overallTime, int screenWidth, int screenHeight) {
    float deltaTime = GetFrameTime();
    float currentTime = GetTime();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    //trail
    UpdateTrail(player->position);
    DrawTrail(player->position, 20.0f);
    //character
    HandleInput(player);
    UpdateMovement(player);
    DrawEntity(player);
    //HUD
    HUD(isNights, pointCounter, ideyaCounter, currentTime, overallTime, screenWidth, screenHeight);
    EndDrawing();
}

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
    //creating initial character position
    Entity player = {
        .position = { screenWidth / 2.0f, screenHeight / 2.0f },
        .velocity = { 0.0f, 0.0f },
        .acceleration = { 0.0f, 0.0f }
    };
    while (WindowShouldClose() == false) {
        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        MainLoop(&player, isNights, pointCounter, ideyaCounter, overallTime, screenWidth, screenHeight);
    }
}