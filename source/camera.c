#include <raylib.h>
#include <math.h>

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
