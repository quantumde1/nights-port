#include "raylib.h"
#include <math.h>
#include <stdio.h>

void writeln(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}

void DrawCharacter(Vector3 initialPosition) {
    DrawCube(initialPosition, 2.0f, 2.0f, 2.0f, RED);
}

void MoveCharacter3D(Vector3 *position, Camera3D *camera, int isNights) {
    //setting variables for speed
    static float currentSpeed = 0.0f;
    const float maxSpeed = 0.35f;
    const float acceleration = 0.016f;
    const float deceleration = 0.016f;
    float movementSpeed = 0.2f;
    //movement vectors
    int vertical = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    int horizontal = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
    //check for player type
    if (isNights == 0) {
        //default moveset in 3d environment
        if (horizontal != 0 && vertical != 0) {
            movementSpeed *= 0.7f;
        }
        position->z += movementSpeed * horizontal;
        position->x += movementSpeed * vertical;
        camera->position.z += movementSpeed * horizontal;
        camera->position.x += movementSpeed * vertical;
    } else if (isNights == 1) { //moveset for 2.5d with specific camera view(like in NiGHTS) and movement by X/Y and not Z
        if (horizontal != 0 || vertical != 0) { // moving
            currentSpeed = fminf(currentSpeed + acceleration, maxSpeed);
        } else { //stopping
            currentSpeed = fmaxf(currentSpeed - deceleration, 0.0f);
        }
        //setting camera target so camera will be slightly slower than player
        camera->position.y += position->y-(position->y*0.2);
        position->y += currentSpeed * -horizontal;
        position->x += currentSpeed * vertical;
        camera->position.x += currentSpeed * vertical;
    }
    camera->target = *position;
}

void JumpCharacter3D(Vector3 *position, Camera3D *camera) {
    //variables for jumps physics
    static float jumpSpeed = 1.0f;
    static float gravity = 0.07f;
    static float verticalSpeed = 0.0f;
    //double jump counter
    static int jumpCount = 0;
    if (IsKeyPressed(KEY_SPACE)) {
        //check for first jump
        if (jumpCount < 2) {
            verticalSpeed = jumpSpeed;
            jumpCount++;
        }
    }
    //check for second jump
    if (jumpCount > 0) {
        //adding values to y of camera and player position when jumping in 3D environment
        position->y += verticalSpeed;
        camera->position.y += verticalSpeed;
        // decrease speed with gravity force
        verticalSpeed -= gravity;
        // check is player staying on "ground"
        if (position->y <= 0.0f) {
            position->y = 0.0f;
            camera->position.y = 8.0f;
            jumpCount = 0;
            verticalSpeed = 0.0f;
        }
    }
}
