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
    InitAudioDevice();
    SetTargetFPS(60);
    ToggleFullscreen();
    //camera setup
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 8.0f, 15.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    int cameraAngle = 90;
    //timer and counters
    int currentTime = 0;
    int overallTime = 120;
    int nightsStartTime;
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
    int isEnded = 0; //0 - not ended, 1 - ended
    int isStartedLevel = 0; //0 - not started, 1 - started
    //music playback, for now its hardcoded, sorry
    Music levelMusic;
    //player position
    Vector3 playerPosition = {0.0f, 0.0f, 0.0f};
    while (WindowShouldClose() == false) {
        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        switch (gameState) {
            case 0: // menu
                BeginDrawing();
                GraphicalMenu(screenWidth, screenHeight, &gameState);
                EndDrawing();
                break;
            case 1: //game
                //first, play and update music
                if (isStartedLevel == 0) {
                    levelMusic = LoadMusicStream("resources/mystic_forest_4.mp3");
                    PlayMusicStream(levelMusic);
                    isStartedLevel = 1;
                }
                UpdateMusicStream(levelMusic);
                //3d mode
                BeginDrawing();
                ClearBackground(RAYWHITE);
                BeginMode3D(camera);
                DrawGrid(10, 1.0f);
                if (IsKeyPressed(KEY_C)) {
                    nightsStartTime = (int)GetTime();
                    isNights = 1;
                }
                if (isNights == 1) {
                    currentTime = (int)(GetTime() - nightsStartTime);
                }
                if (IsKeyPressed(KEY_E)) {
                    StopMusicStream(levelMusic);
                    UnloadMusicStream(levelMusic);
                    gameState = 3;
                }
                SwitchCameraTo2dot5D(&camera, isNights, &cameraAngle);
                DrawCharacter(characterPosition, "res/test.glb");
                MoveCharacter3D(&characterPosition, &camera, isNights);
                JumpCharacter3D(&characterPosition, &camera);
                RotateCamera(&camera, &characterPosition, &cameraAngle, isNights);
                //drawing UI
                EndMode3D();
                HUD(isNights, pointCounter, ideyaCounter, currentTime, overallTime, screenWidth, screenHeight);
                EndDrawing();
                break;
            case 2: //bossfight
                currentTime = overallTime-(int)GetTime();
                break;
            case 3: // level cleared
                //Setting music, again...
                if (isEnded == 0) {
                    levelMusic = LoadMusicStream("resources/peaceful_moment.mp3");
                    PlayMusicStream(levelMusic);
                    isEnded = 1;
                }
                UpdateMusicStream(levelMusic);
                //drawing 2d
                BeginDrawing();
                DrawText("Results:\n",screenWidth/2-MeasureText("Results:\n", 40), screenHeight/2, 40, BLACK);
                EndDrawing();
                break;
        }
    }

    CloseWindow();
    return 0;
}
