#include "raylib.h"

void DrawCharacter(Vector3 initialPosition, char* modelPath) {
    DrawCube(initialPosition, 2.0f, 2.0f, 2.0f, RED);
}

void MoveCharacter3D(Vector3 *position, Camera3D *camera, int isNights) {
    float movementSpeed = 0.2f;
    /*
     * -1 - a pressed
     * 0 - nothing pressed
     * 1 - d pressed
     */
    int vertical = 0;
    /*
     * -1 - w pressed
     * 0 - nothing pressed
     * 1 - s pressed
     */
    int horizontal = 0;
    if (horizontal != 0 && vertical != 0) {
        movementSpeed *= 0.7f;
    }
    if (IsKeyDown(KEY_W)) {
        horizontal = -1;
    }
    else if (IsKeyDown(KEY_S)) {
        horizontal = 1;
    }
    if (IsKeyDown(KEY_A)) {
        vertical = -1;
    }
    else if (IsKeyDown(KEY_D)) {
        vertical = 1;
    }
    if (isNights == 0) {
        position->z += movementSpeed*horizontal;
        position->x += movementSpeed*vertical;
        camera->position.z += movementSpeed*horizontal;
        camera->position.x += movementSpeed*vertical;
        camera->target = (Vector3){ position->x, position->y, position->z };
    } else {
        position->y += movementSpeed*-(horizontal);
        position->x += movementSpeed*vertical;
        camera->position.y += movementSpeed*-(horizontal);
        camera->position.x += movementSpeed*vertical;
        camera->target = (Vector3){ position->x, position->y, position->z };
    }
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
