#include "raylib.h"
#include "raymath.h"

// Define a struct to store the character's trail
typedef struct {
    Vector2 position;
    float time;
} TrailPoint;

// Define an array to store the trail points
#define MAX_TRAIL_POINTS 200
TrailPoint trailPoints[MAX_TRAIL_POINTS];
int trailIndex = 0;

Vector2 Vector2LinePoint(Vector2 start, Vector2 end, Vector2 point) {
    Vector2 line = Vector2Subtract(end, start);
    Vector2 pointToStart = Vector2Subtract(point, start);
    float t = Vector2DotProduct(pointToStart, line) / Vector2DotProduct(line, line);

    t = fmaxf(0, fminf(1, t)); // Clamp t to [0, 1]

    return Vector2Add(start, Vector2Scale(line, t));
}

bool CheckCollisionTrail(Vector2 entityPosition, float entityRadius) {
    for (int i = 0; i < MAX_TRAIL_POINTS - 1; i++) {
        int index = (trailIndex + i) % MAX_TRAIL_POINTS;
        int nextIndex = (index + 1) % MAX_TRAIL_POINTS;

        Vector2 start = trailPoints[index].position;
        Vector2 end = trailPoints[nextIndex].position;

        // Check if the entity is close enough to the line segment
        float distance = Vector2Distance(entityPosition, Vector2LinePoint(start, end, entityPosition));
        if (distance < entityRadius) {
            return true;
        }
    }
    return false;
}

// In your main loop, update the trail points
void UpdateTrail(Vector2 characterPosition) {
    trailPoints[trailIndex].position = characterPosition;
    trailPoints[trailIndex].time = GetTime();
    trailIndex = (trailIndex + 1) % MAX_TRAIL_POINTS;
}

void DrawTrail(Vector2 entityPosition, float entityRadius) {
    bool collisionDetected = false;

    for (int i = 0; i < MAX_TRAIL_POINTS - 1; i++) {
        int index = (trailIndex + i) % MAX_TRAIL_POINTS;
        int nextIndex = (index + 1) % MAX_TRAIL_POINTS;

        if (!collisionDetected) {
            // Check for collision with the current segment
            Vector2 start = trailPoints[index].position;
            Vector2 end = trailPoints[nextIndex].position;

            float distance = Vector2Distance(entityPosition, Vector2LinePoint(start, end, entityPosition));
            if (distance < entityRadius) {
                collisionDetected = true;
            }

            if (GetTime() - trailPoints[index].time < 1.5f) {
                DrawLineV(start, end, GREEN);
            }
        }
    }
}