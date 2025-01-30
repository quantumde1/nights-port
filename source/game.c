#include <stdio.h>
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
