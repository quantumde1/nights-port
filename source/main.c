#include <stdio.h>
#include "raylib.h"
#include "headers.h"

int main() {
    printf("%s\n", "entered main loop");
    printf("%s\n", "setting screen size");
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    printf("%s\n", "screen setup started");
    InitWindow(screenWidth, screenHeight, "NiGHTS into Dreams...");
    SetTargetFPS(60);
    ToggleFullscreen();
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 8.0f, 15.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    float cameraAngle = 90.0f;
    int currentTime = 0;
    int overallTime = 120;
    //Model world = LoadWorldModel("res/test.glb");
    int ideyaCounter = 0;
    int pointCounter = 0;
    Vector3 characterPosition = { 0.0, 0.0, 0.0 };
    int isNights = 0; // 0 means Elliot/Claris, 1 means NiGHTS
    /* 0 - in menu
     * 1 - at level
     * 2 - at bossfight
     * 3 - at results
    */
    int gameState = 0;
    while (WindowShouldClose() == false) {
        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        if (gameState != 0) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            currentTime = (int)GetTime();
            HUD(isNights, pointCounter, ideyaCounter, currentTime, overallTime, screenWidth, screenHeight);
            BeginMode3D(camera);
            DrawGrid(10, 1.0f);
            DrawCharacter(characterPosition, "res/test.glb");
            MoveCharacter3D(&characterPosition, &camera);
            JumpCharacter3D(&characterPosition, &camera);
            RotateCamera(&camera, &characterPosition, &cameraAngle);
            EndMode3D();
            EndDrawing();
        } else {
            BeginDrawing();
            GraphicalMenu(screenWidth, screenHeight, &gameState);
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
