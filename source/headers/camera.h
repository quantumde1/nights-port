#include "raylib.h"

// camera
void RotateCamera(Camera3D *camera, Vector3 *characterPosition, int *cameraAngle, int isNights);
void SwitchCameraTo2dot5D(Camera3D *camera, int isNights, int *cameraAngle);