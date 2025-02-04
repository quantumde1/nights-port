#include "raylib.h"
#include "system.h"

typedef struct {
    Vector3 position;
    float size;
    Color color;
} SphereData;

typedef struct {
    SphereData *spheres; // Массив сфер
    int sphere_count;    // Количество сфер
    char musicLevel[256]; // Путь к музыке уровня
    char musicBossfight[256]; // Путь к музыке босса
} SceneData;

void parse_json_file(const char *filename, SceneData *scene);