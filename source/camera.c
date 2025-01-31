#include <raylib.h>
#include <math.h>

void SwitchCameraTo2dot5D(Camera3D *camera, int isNights, float *cameraAngle) {
    if (isNights == 1) {
        *cameraAngle = 90.0f;
        camera->position = (Vector3){0.0f, 1.5f, 10.0f};
        camera->target = (Vector3){0.0f, 0.0f, 0.0f};
        camera->up = (Vector3){0.0f, 1.0f, 0.0f};
        camera->fovy = 90.0f;
    }
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
