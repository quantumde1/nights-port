#include "raylib.h"
#include "headers/system.h"

Model LoadWorldModel(char* model_path) {
    writeln("loading overworld model, file: %s", model_path);
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
