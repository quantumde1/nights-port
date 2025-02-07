#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "raylib.h"
#include "types.h"

void HandleInput(Entity *entity);
void UpdateMovement(Entity *entity);
void DrawEntity(Entity *entity);

#endif