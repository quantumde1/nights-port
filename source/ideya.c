#include "raylib.h"
#include "headers/system.h"

Texture2D LoadSphereTexture() {
    writeln("Loading sphere texture");
    Texture2D SphereTexture = LoadTexture("resources/sphere.png");
    return SphereTexture;
}

void DrawBlueSphere(Texture2D SphereTexture, int spherePosX, int spherePosY) {
    DrawTexture(SphereTexture, spherePosX, spherePosY, WHITE);
}

void DrawDebugBlueSphere(Vector3 Position, float radius, Color color) {
    DrawSphere(Position, radius, color);
}