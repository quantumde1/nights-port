#ifndef TRAIL_H
#define TRAIL_H

#include "raylib.h"

#define TRAIL_LENGTH 100
bool IsPointInPolygon(Vector2 point, Vector2* polygon, int vertexCount);
bool CheckLineIntersection(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4);
void DrawTrail(Vector2 *trail, int trailLength, int currentIndex);

#endif