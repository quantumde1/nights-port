#include "raylib.h"

void HUD(int isNights, int pointCounter, int ideyaCounter, int currentTime, int overallTime, int screenWidth, int screenHeight);
void GraphicalMenu(int screenWidth, int screenHeight, int *gameState);
Model LoadWorldModel(char* modelPath);
void DrawWorldModel(Model model);
void WorldMain(char* modelPath);
void DrawCharacter(Vector3 initialPosition, char* modelPath);
void MoveCharacter3D(Vector3 *position, Camera3D *camera);
void JumpCharacter3D(Vector3 *position, Camera3D *camera);
void RotateCamera(Camera3D *camera, Vector3 *characterPosition, float *cameraAngle);
