#include "raylib.h"
#include "headers/enemy.h"
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

void MainLoop(Entity *player, int *isNights, int *pointCounter, int *ideyaCounter, int overallTime, int screenWidth, int screenHeight, 
Camera2D *camera, Texture2D backgroundTexture, Enemy* enemies) {
    static bool initialized = false;
    if (!initialized) {
        for (int i = 0; i < MAX_ENEMIES; i++) enemies[i].active = false;
        initialized = true;
    }
    static double lastSpawnTime = 0;
    if (GetTime() - lastSpawnTime > 5.0) {
        SpawnEnemy(screenWidth, screenHeight, enemies);
        lastSpawnTime = GetTime();
    }
    static bool isLoopClosed = false;
    static int loopStartIndex = 0;
    static Vector2 trail[TRAIL_LENGTH] = { 0 };
    static int currentIndex = 0;
    float deltaTime = GetFrameTime();
    float currentTime = GetTime();
    static double displayLinkTime = 0.0;
    static int displayLinkNumber = 0;
    camera->target = player->position;
    camera->offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(*camera);
    Vector2 camPos = camera->target;
    Vector2 texSize = { (float)backgroundTexture.width, (float)backgroundTexture.height };
    int startX = (int)((camPos.x - screenWidth/2) / texSize.x) - 1;
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
                isLoopClosed = true;
                loopStartIndex = (currentIndex + i) % TRAIL_LENGTH;
            }
        }
    }
    if (isLoopClosed) {
        Vector2 polygon[TRAIL_LENGTH];
        int vertexCount = 0;
        int count = 0;
        for (int k = 0; k < TRAIL_LENGTH; k++) {
            int idx = (loopStartIndex + k) % TRAIL_LENGTH;
            polygon[count++] = trail[idx];
            if (idx == currentIndex) break;
        }
        vertexCount = count;
        int enemiesDestroyedThisFrame = 0;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active && IsPointInPolygon(enemies[i].position, polygon, vertexCount)) {
                enemies[i].active = false;
                enemiesDestroyedThisFrame++;
            }
        }

        // Process link and points
        if (enemiesDestroyedThisFrame > 0) {
            static double lastHitTime = 0.0;
            static int currentLink = 0;
            double currentTime = GetTime();

            if (currentTime - lastHitTime <= 4.0) {
                currentLink += enemiesDestroyedThisFrame;
            } else {
                currentLink = enemiesDestroyedThisFrame;
            }
            if (currentLink > 1) {
                *pointCounter += (5 + currentLink) * currentLink;
            } else {
                *pointCounter += 5 * currentLink;
            }
            lastHitTime = currentTime;

            if (currentLink >= 2) {
                displayLinkNumber = currentLink;
                displayLinkTime = 2.0; // Display for 2 seconds
            }
        }
        isLoopClosed = false;
    }
    UpdateEnemies(player, enemies);
    DrawEnemies(enemies);
    EndMode2D();
    //HUD
    HUD(*isNights, *pointCounter, *ideyaCounter, currentTime, overallTime, screenWidth, screenHeight);
    if (displayLinkTime > 0) {
        char linkText[32];
        snprintf(linkText, sizeof(linkText), "Link %d", displayLinkNumber);
        int textWidth = MeasureText(linkText, 40);
        int posX = (screenWidth - textWidth) / 2;
        int posY = 150;
        DrawText(linkText, posX, posY, 40, YELLOW);
        displayLinkTime -= deltaTime;
        if (displayLinkTime < 0) {
            displayLinkTime = 0.0;
        }
    }
    EndDrawing();
}