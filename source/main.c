#include "raylib.h"
//engine
#include "headers/controller.h"
#include "headers/hud.h"
#include "headers/types.h"
#include "headers/trail.h"
//system
#include "stdio.h"

void SetupLevel(char* backgroundImage, char* levelMusicPath, Texture2D *backgroundTexture, Music *levelMusic) {
    *backgroundTexture = LoadTexture(backgroundImage);
    *levelMusic = LoadMusicStream(levelMusicPath);
    PlayMusicStream(*levelMusic);
}

void MainLoop(Entity *player, int isNights, int pointCounter, int ideyaCounter, int overallTime, int screenWidth, int screenHeight, Camera2D *camera) {
    static Vector2 trail[TRAIL_LENGTH] = { 0 };
    static int currentIndex = 0;
    float deltaTime = GetFrameTime();
    float currentTime = GetTime();
    camera->target = player->position;
    camera->offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(*camera);
    //character
    HandleInput(player);
    UpdateMovement(player);
    DrawEntity(player);
    trail[currentIndex] = player->position;
    currentIndex = (currentIndex + 1) % TRAIL_LENGTH;
    DrawTrail(trail, TRAIL_LENGTH, currentIndex);
    for (int i = 0; i < TRAIL_LENGTH - 3; i++) {
        for (int j = i + 2; j < TRAIL_LENGTH - 1; j++) {
            int index1 = (currentIndex + i) % TRAIL_LENGTH;
            int index2 = (currentIndex + i + 1) % TRAIL_LENGTH;
            int index3 = (currentIndex + j) % TRAIL_LENGTH;
            int index4 = (currentIndex + j + 1) % TRAIL_LENGTH;

            if (CheckLineIntersection(trail[index1], trail[index2], trail[index3], trail[index4])) {
                printf("paraloop\n");
                break;
            }
        }
    }
    EndMode2D();
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
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
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
        MainLoop(&player, isNights, pointCounter, ideyaCounter, overallTime, screenWidth, screenHeight, &camera);
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}