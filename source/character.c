#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define XBOX_ALIAS_1 "xbox"
#define XBOX_ALIAS_2 "x-box"
#define PS_ALIAS     "playstation"

void writeln(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}

float Lerp(float a, float b, float t) {
    return a + t * (b - a);
}

void DrawCharacter(Vector3 initialPosition) {
    DrawCube(initialPosition, 2.0f, 2.0f, 2.0f, RED);
}

void MoveCharacter3D(Vector3 *position, Camera3D *camera, int isNights) {
    // Настройка переменных для скорости
    static float currentSpeed = 0.0f;
    const float maxSpeed = 0.35f;
    const float acceleration = 0.016f;
    const float deceleration = 0.016f;
    float movementSpeed = 0.2f;
    float vertical = IsKeyDown(KEY_D) - IsKeyDown(KEY_A);
    float horizontal = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
    // Чтение данных с контроллера
    if (IsGamepadAvailable(1)) {
        vertical = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_X);
        horizontal = GetGamepadAxisMovement(1, GAMEPAD_AXIS_LEFT_Y);
        //writeln("Gamepad X Y: %f %f",vertical, horizontal);
        // Применение сглаживания к входным данным
        vertical = Lerp(0.0f, vertical, 0.8f);
        horizontal = Lerp(0.0f, horizontal, 0.8f);
    }
    // Движение в 3D среде
    if (isNights == 0) {
        if (vertical != 0 && horizontal != 0) {
            movementSpeed *= 0.7f;
        }
        position->z += movementSpeed * horizontal;
        position->x += movementSpeed * vertical;
        camera->position.z += movementSpeed * horizontal;
        camera->position.x += movementSpeed * vertical;
    } else if (isNights == 1) { // Движение в 2.5D среде
        if (vertical != 0 || horizontal != 0) {
            currentSpeed = fminf(currentSpeed + acceleration, maxSpeed);
        } else {
            currentSpeed = fmaxf(currentSpeed - deceleration, 0.0f);
        }
        camera->position.y += position->y - (position->y * 0.2);
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

    // Проверка нажатия кнопки прыжка на контроллере
    if (IsGamepadButtonPressed(1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || IsKeyPressed(KEY_SPACE)) {
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