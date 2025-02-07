#include "raylib.h"
#include "raymath.h"
#include "headers/types.h"

#define FRICTION 0.95f
#define ACCELERATION 0.5f
#define MAX_SPEED 10.0f

// Function to update the entity's movement
void UpdateMovement(Entity *entity) {
    // Apply friction
    entity->velocity.x *= FRICTION;
    entity->velocity.y *= FRICTION;

    // Apply acceleration to velocity
    entity->velocity.x += entity->acceleration.x;
    entity->velocity.y += entity->acceleration.y;

    // Limit the speed
    if (Vector2Length(entity->velocity) > MAX_SPEED) {
        entity->velocity = Vector2Scale(Vector2Normalize(entity->velocity), MAX_SPEED);
    }

    // Update position based on velocity
    entity->position.x += entity->velocity.x;
    entity->position.y += entity->velocity.y;

    // Reset acceleration for the next frame
    entity->acceleration = (Vector2){ 0.0f, 0.0f };
}

// Function to handle input and apply acceleration
void HandleInput(Entity *entity) {
    if (IsKeyDown(KEY_W)) entity->acceleration.y -= ACCELERATION;
    if (IsKeyDown(KEY_S)) entity->acceleration.y += ACCELERATION;
    if (IsKeyDown(KEY_A)) entity->acceleration.x -= ACCELERATION;
    if (IsKeyDown(KEY_D)) entity->acceleration.x += ACCELERATION;
}

// Function to draw the entity
void DrawEntity(Entity *entity) {
    DrawCircleV(entity->position, 20.0f, RED);
}