#include <stdio.h>
#include <math.h>
#include "raylib.h"

Model LoadWorldModel(char* model_path) {
    printf("%s\n", "loading overworld model");
    Model world = LoadModel(model_path);
    return world;
}

void DrawWorldModel(Model model) {
    printf("%s\n", "drawing overworld model");
    DrawModel(model, (Vector3){0, 0, 0}, 1.0, WHITE);
}

void WorldMain(char* model_path) {
    Model world = LoadWorldModel(model_path);
    DrawWorldModel(world);
}

void DrawCharacter(Vector3 initialPosition, char* modelPath) {
    DrawCube(initialPosition, 2.0f, 2.0f, 2.0f, RED);
}

void MoveCharacter3D(Vector3 *position, Camera3D *camera) {
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
    position->z += movementSpeed*horizontal;
    position->x += movementSpeed*vertical;
    camera->position.z += movementSpeed*horizontal;
    camera->position.x += movementSpeed*vertical;
    camera->target = (Vector3){ position->x, position->y, position->z };
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

void SwitchCameraTo25D(Camera3D *camera) {

}

void RotateCamera(Camera3D *camera, Vector3 *characterPosition, float *cameraAngle) {
    const float rotationSpeed = 2.0f;
    if (IsKeyDown(KEY_LEFT)) {
        *cameraAngle -= rotationSpeed;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        *cameraAngle += rotationSpeed;
    }
    if (*cameraAngle < 0) {
        *cameraAngle += 360;
    }
    if (*cameraAngle >= 360) {
        *cameraAngle -= 360;
    }
    camera->position.x = characterPosition->x + 10 * cosf(DEG2RAD * (*cameraAngle));
    camera->position.z = characterPosition->z + 10 * sinf(DEG2RAD * (*cameraAngle));
    camera->target = (Vector3){ characterPosition->x, characterPosition->y + 1.5f, characterPosition->z };
}
