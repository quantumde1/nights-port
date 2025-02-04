#include "raylib.h"

// Define a struct to store the character's trail
typedef struct {
    Vector3 position;
    float time;
} TrailPoint;

// Define an array to store the trail points
#define MAX_TRAIL_POINTS 200
TrailPoint trailPoints[MAX_TRAIL_POINTS];
int trailIndex = 0;

// In your main loop, update the trail points
void UpdateTrail(Vector3 characterPosition) {
    trailPoints[trailIndex].position = characterPosition;
    trailPoints[trailIndex].time = GetTime();
    trailIndex = (trailIndex + 1) % MAX_TRAIL_POINTS;
}

void DrawTrail() {
    for (int i = 0; i < MAX_TRAIL_POINTS - 1; i++) {
        int index = (trailIndex + i) % MAX_TRAIL_POINTS;
        if (GetTime() - trailPoints[index].time < 1.5f) { // adjust the time to control the trail length
            DrawLine3D(trailPoints[index].position, trailPoints[(index + 1) % MAX_TRAIL_POINTS].position, GREEN);
        }
    }
}