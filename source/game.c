#include <stdio.h>
#include "raylib.h"

Model LoadWorldModel(char* model_path) {
    printf("%s\n", "loading overworld model");
    Model world = LoadModel(model_path);
    return world;
}

void DrawWorldModel(Model model, float size) {
    DrawModel(model, (Vector3){0, 0, 0}, size, BLUE);
}

void WorldMain(char* model_path, int size) {
    Model world = LoadWorldModel(model_path);
    DrawWorldModel(world, size);
}
