// types.h
#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

#define MAX_ENEMIES 50

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
} Entity;

typedef struct Enemy {
    Vector2 position;
    bool active;
} Enemy;

#endif // TYPES_H