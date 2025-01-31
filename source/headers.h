#include "raylib.h"

//interface
void HUD(short isNights, short pointCounter, short ideyaCounter, short currentTime, short overallTime, int screenWidth, int screenHeight);
void GraphicalMenu(int screenWidth, int screenHeight, short *gameState);

// world
Model LoadWorldModel(char* modelPath);
void DrawWorldModel(Model model);
void WorldMain(char* modelPath);

// character
void DrawCharacter(Vector3 initialPosition, char* modelPath);
void MoveCharacter3D(Vector3 *position, Camera3D *camera, short isNights);
void JumpCharacter3D(Vector3 *position, Camera3D *camera);

// camera
void RotateCamera(Camera3D *camera, Vector3 *characterPosition, short *cameraAngle);
void SwitchCameraTo2dot5D(Camera3D *camera, short isNights, short *cameraAngle);
