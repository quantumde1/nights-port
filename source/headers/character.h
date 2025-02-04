#include "raylib.h"

// character
void DrawCharacter(Vector3 initialPosition, char* modelPath);
void MoveCharacter3D(Vector3 *position, Camera3D *camera, int isNights);
void JumpCharacter3D(Vector3 *position, Camera3D *camera);
void UpdateTrail(Vector3 characterPosition);
void DrawTrail();