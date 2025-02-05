#include <stdio.h>
#include <stdlib.h>
#include "cjson/cJSON.h"
#include "string.h"

#include "raylib.h" 
#include "headers/system.h"

typedef struct {
    Vector3 position;
    float size;
    Color color;
} SphereData;

typedef struct {
    SphereData *spheres; // Массив сфер
    int sphere_count;    // Количество сфер
    char musicLevel[256]; // Путь к музыке уровня
} SceneData;

// Функция для парсинга JSON
void parse_json_file(const char *filename, SceneData *scene) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file %s\n", filename);
        return;
    }

    // Чтение файла
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *file_content = (char *)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    fclose(file);
    file_content[file_size] = '\0';

    // Парсинг JSON
    cJSON *json = cJSON_Parse(file_content);
    if (!json) {
        fprintf(stderr, "Error: Failed to parse JSON\n");
        free(file_content);
        return;
    }

    // Доступ к объекту "objects"
    cJSON *objects = cJSON_GetObjectItemCaseSensitive(json, "objects");
    if (objects) {
        // Парсинг сфер
        cJSON *object;
        scene->sphere_count = cJSON_GetArraySize(objects) - 2; // Исключаем musicLevel и musicBossfight
        scene->spheres = (SphereData *)malloc(scene->sphere_count * sizeof(SphereData));

        int index = 0;
        cJSON_ArrayForEach(object, objects) {
            const char *object_name = object->string;

            // Парсинг сфер
            if (strstr(object_name, "BlueSphere") != NULL) {
                cJSON *place = cJSON_GetObjectItemCaseSensitive(object, "place");
                if (place && cJSON_IsArray(place) && cJSON_GetArraySize(place) == 3) {
                    scene->spheres[index].position.x = (float)atof(cJSON_GetArrayItem(place, 0)->valuestring);
                    scene->spheres[index].position.y = (float)atof(cJSON_GetArrayItem(place, 1)->valuestring);
                    scene->spheres[index].position.z = (float)atof(cJSON_GetArrayItem(place, 2)->valuestring);
                }

                cJSON *size = cJSON_GetObjectItemCaseSensitive(object, "size");
                if (size && cJSON_IsString(size)) {
                    scene->spheres[index].size = (float)atof(size->valuestring);
                }

                cJSON *color = cJSON_GetObjectItemCaseSensitive(object, "color");
                if (color && cJSON_IsString(color)) {
                    if (strcmp(color->valuestring, "WHITE") == 0) {
                        scene->spheres[index].color = WHITE;
                    } else if (strcmp(color->valuestring, "BLUE") == 0) {
                        scene->spheres[index].color = BLUE;
                    } // Добавьте другие цвета по необходимости
                }

                index++;
            }
            // Парсинг музыки уровня
            else if (strcmp(object_name, "musicLevel") == 0) {
                strncpy(scene->musicLevel, object->valuestring, sizeof(scene->musicLevel) - 1);
                scene->musicLevel[sizeof(scene->musicLevel) - 1] = '\0'; // Гарантировать завершающий нуль
            }
        }
    }

    // Очистка
    cJSON_Delete(json);
    free(file_content);
}