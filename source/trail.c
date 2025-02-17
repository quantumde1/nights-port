#include "raylib.h"
#include "stdbool.h"

void DrawTrail(Vector2 *trail, int trailLength, int currentIndex) {
    for (int i = 0; i < trailLength - 1; i++) {
        int index = (currentIndex + i) % trailLength;
        int nextIndex = (currentIndex + i + 1) % trailLength;
        DrawLineV(trail[index], trail[nextIndex], Fade(YELLOW, 255.0f));
    }
}

bool CheckLineIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4) {
    float denominator = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);
    if (denominator == 0) return false;

    float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denominator;
    float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denominator;
    return ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1;
}

bool IsPointInPolygon(Vector2 point, Vector2* polygon, int vertexCount) {
    if (vertexCount < 3) return false;
    bool inside = false;
    for (int i = 0, j = vertexCount-1; i < vertexCount; j = i++) {
        if (((polygon[i].y > point.y) != (polygon[j].y > point.y)) &&
            (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / 
            (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }
    return inside;
}
