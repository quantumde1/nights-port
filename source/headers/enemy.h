#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"

void DrawEnemies(Enemy* enemies);
void UpdateEnemies(Entity* player,Enemy* enemies);
void SpawnEnemy(int screenWidth, int screenHeight,Enemy* enemies);
#endif