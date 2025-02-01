#include "raylib.h"
#include <math.h>

void DrawCharacter(Vector3 initialPosition, char* modelPath) {
    DrawCube(initialPosition, 2.0f, 2.0f, 2.0f, RED);
}

void MoveCharacter3D(Vector3 *position, Camera3D *camera, int isNights) {
    static float currentSpeed = 0.0f;
    const float maxSpeed = 0.29f;
    const float acceleration = 0.013f;
    const float deceleration = 0.013f;
    float movementSpeed = 0.2f;

    int vertical = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    int horizontal = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);

    if (isNights == 0) {
        if (horizontal != 0 && vertical != 0) {
            movementSpeed *= 0.7f;
        }
        position->z += movementSpeed * horizontal;
        position->x += movementSpeed * vertical;
        camera->position.z += movementSpeed * horizontal;
        camera->position.x += movementSpeed * vertical;
    } else if (isNights == 1) {
        if (horizontal != 0 || vertical != 0) {
            currentSpeed = fminf(currentSpeed + acceleration, maxSpeed);
        } else {
            currentSpeed = fmaxf(currentSpeed - deceleration, 0.0f);
        }
        if (position->y >= 7.0f) {
            camera->position.y = 7.0f;
        } else if (position->y <= -7.0f) {
            camera->position.y = -7.0f;
        } else {
            camera->position.y += position->y;
        }
        position->y += currentSpeed * -horizontal;
        position->x += currentSpeed * vertical;
        camera->position.x += currentSpeed * vertical;
    }
    camera->target = *position;
}

void JumpCharacter3D(Vector3 *position, Camera3D *camera) {
    static float jumpSpeed = 1.0f;
    static float gravity = 0.07f;
    static float verticalSpeed = 0.0f;
    static int jumpCount = 0;
    if (IsKeyPressed(KEY_SPACE)) {
        if (jumpCount < 2) {
            verticalSpeed = jumpSpeed;
            jumpCount++;
        }
    }
    if (jumpCount > 0) {
        position->y += verticalSpeed;
        camera->position.y += verticalSpeed;
        verticalSpeed -= gravity;
        if (position->y <= 0.0f) {
            position->y = 0.0f;
            camera->position.y = 8.0f;
            jumpCount = 0;
            verticalSpeed = 0.0f;
        }
    }
}
