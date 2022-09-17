#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdint.h>
#include "vector.h"
#include "display.h"

typedef struct
{
    int a;
    int b;
    int c;
    color_t color;
} face_t;

typedef struct
{
    vect2_t points[3];
    color_t color;
    float avg_depth;
} triangle_t;

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, u_int32_t color);

#endif