#include "raylib.h"
#include "raymath.h"
#include "headers/types.h"

void SpawnEnemy(int screenWidth, int screenHeight, Enemy* enemies) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            enemies[i].position = (Vector2){
                GetRandomValue(0, 10),
                GetRandomValue(0, 10)
            };
            enemies[i].active = true;
            break;
        }
    }
}

void UpdateEnemies(Entity* player, Enemy* enemies) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            //simple logic for movement to player
            Vector2 direction = Vector2Subtract(player->position, enemies[i].position);
            direction = Vector2Normalize(direction);
            enemies[i].position = Vector2Add(enemies[i].position, Vector2Scale(direction, 1.5f));
        }
    }
}

void DrawEnemies(Enemy* enemies) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            DrawCircleV(enemies[i].position, 15, RED);
        }
    }
}