#include "raylib.h"

//interface
void HUD(int isNights, int pointCounter, int ideyaCounter, int currentTime, int overallTime, int screenWidth, int screenHeight);
void GraphicalMenu(int screenWidth, int screenHeight, int *gameState);

// world
Model LoadWorldModel(char* modelPath);
void DrawWorldModel(Model model);
void WorldMain(char* modelPath);

// character
void DrawCharacter(Vector3 initialPosition, char* modelPath);
void MoveCharacter3D(Vector3 *position, Camera3D *camera, int isNights);
void JumpCharacter3D(Vector3 *position, Camera3D *camera);

// camera
void RotateCamera(Camera3D *camera, Vector3 *characterPosition, short *cameraAngle);
void SwitchCameraTo2dot5D(Camera3D *camera, int isNights, short *cameraAngle);
