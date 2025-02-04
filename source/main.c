//os
#include <stdio.h>
//raylib
#include "raylib.h"
#include "rlgl.h"
//engine
#include "headers/system.h"
#include "headers/character.h"
#include "headers/game.h"
#include "headers/camera.h"
#include "headers/hud.h"

int main() {
    writeln("NiGHTS into Dreams -reload- engine started.\nInitializing base variables...");
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    writeln("screen and audio setup started");
    InitWindow(screenWidth, screenHeight, "NiGHTS into Dreams...");
    SetTargetFPS(60);
    InitAudioDevice();
    ToggleFullscreen();
    //camera setup
    writeln("setting up camera");
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 8.0f, 15.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    writeln("configuring variables");
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
    writeln("configuring frustum");
    rlFrustum(0.01, 0.01, 0.01, 0.01, 0.01, 0.01);
    int isEnded = 0; //0 - not ended, 1 - ended
    int isStartedLevel = 0; //0 - not started, 1 - started
    //music playback, for now its hardcoded, sorry
    Music levelMusic;
    //player position
    Vector3 playerPosition = {0.0f, 0.0f, 0.0f};
    //Model overworld = LoadWorldModel("resources/spring_valley.glb");
    writeln("entering main loop");
    while (WindowShouldClose() == false) {
        char buffer[38];
        snprintf(buffer, sizeof(buffer), "%f, %f, %f", characterPosition.x, characterPosition.y, characterPosition.z);
        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        switch (gameState) {
            case 0: // menu
                BeginDrawing();
                GraphicalMenu(screenWidth, screenHeight, &gameState);
                EndDrawing();
                break;
            case 1: // game
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
                if (IsKeyPressed(KEY_C)) {
                    nightsStartTime = (int)GetTime();
                    isNights = 1;
                }
                if (isNights == 1) {
                    currentTime = (int)(GetTime() - nightsStartTime);
                }
                if (IsKeyPressed(KEY_G)) {
                    nightsStartTime = 0;
                    isNights = 0;
                }
                if (IsKeyPressed(KEY_E)) {
                    StopMusicStream(levelMusic);
                    UnloadMusicStream(levelMusic);
                    gameState = 3;
                }
                SwitchCameraTo2dot5D(&camera, isNights, &cameraAngle);
                //DrawWorldModel(overworld);
                DrawCharacter(characterPosition, "res/test.glb");
                MoveCharacter3D(&characterPosition, &camera, isNights);
                UpdateTrail(characterPosition);
                DrawTrail();
                JumpCharacter3D(&characterPosition, &camera);
                RotateCamera(&camera, &characterPosition, &cameraAngle, isNights);
                //drawing UI
                EndMode3D();
                HUD(isNights, pointCounter, ideyaCounter, currentTime, overallTime, screenWidth, screenHeight);
                DrawText(buffer, 10, 10, 20, GREEN);
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
