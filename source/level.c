#include "raylib.h"
#include "headers/types.h"
#include "headers/controller.h"
#include "headers/hud.h"
#include "headers/trail.h"
#include "stdio.h"

void SetupLevel(char* backgroundImage, char* levelMusicPath, Texture2D *backgroundTexture, Music *levelMusic) {
    *backgroundTexture = LoadTexture(backgroundImage);
    *levelMusic = LoadMusicStream(levelMusicPath);
    PlayMusicStream(*levelMusic);
}

void MainLoop(Entity *player, int isNights, int pointCounter, int ideyaCounter, int overallTime, int screenWidth, int screenHeight, 
Camera2D *camera, Texture2D backgroundTexture) {
    static Vector2 trail[TRAIL_LENGTH] = { 0 };
    static int currentIndex = 0;
    float deltaTime = GetFrameTime();
    float currentTime = GetTime();
    camera->target = player->position;
    camera->offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(*camera);
    Vector2 camPos = camera->target;
    Vector2 texSize = { (float)backgroundTexture.width, (float)backgroundTexture.height };
    float startX = ((camPos.x - (float)screenWidth/2) / texSize.x) - 1;
    float endX = (int)((camPos.x + (float)screenWidth/2) / texSize.x) + 1;
    float startY = (int)((camPos.y - (float)screenHeight/2) / texSize.y) - 1;
    float endY = (int)((camPos.y + (float)screenHeight/2) / texSize.y) + 1;
    for (int x = startX; x <= endX; x++) {
        for (int y = startY; y <= endY; y++) {
            Vector2 pos = { x * texSize.x, y * texSize.y };
            DrawTextureV(backgroundTexture, pos, WHITE);
        }
    }
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