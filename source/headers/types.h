// types.h
#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
} Entity;

#endif // TYPES_H