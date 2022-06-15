#include <math.h>
#include "vector.h"

// Vector 2D Functions
float get_vect2_length(vect2_t v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

vect2_t add_vect2(vect2_t v1, vect2_t v2)
{
    vect2_t v_new = {.x = v1.x + v2.x, .y = v1.y + v2.y};
    return v_new;
}

vect2_t sub_vect2(vect2_t v1, vect2_t v2)
{
    vect2_t v_new = {.x = v1.x - v2.x, .y = v1.y - v2.y};
    return v_new;
}

vect2_t mul_vect2(vect2_t v, float factor)
{
    vect2_t v_new = {.x = v.x * factor, .y = v.y * factor};
    return v_new;
}

vect2_t div_vect2(vect2_t v, float factor)
{
    vect2_t v_new = {.x = v.x / factor, .y = v.y / factor};
    return v_new;
}

float dot_vect2(vect2_t a, vect2_t b)
{
    return (a.x * b.x) + (a.y * b.y);
}

void vec2_normalize(vect2_t *vec)
{
    float length = sqrt(vec->x * vec->x + vec->y * vec->y);
    vec->x /= length;
    vec->y /= length;
}

// Vector 3D Functions
float get_vect3_length(vect3_t v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vect3_t add_vect3(vect3_t v1, vect3_t v2)
{
    vect3_t v_new = {.x = v1.x + v2.x, .y = v1.y + v2.y, .z = v1.z + v1.z};
    return v_new;
}

vect3_t sub_vect3(vect3_t a, vect3_t b)
{
    vect3_t v_new = {.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z};
    return v_new;
}

vect3_t mul_vect3(vect3_t v, float factor)
{
    vect3_t v_new = {.x = v.x * factor, .y = v.y * factor, .z = v.z * factor};
    return v_new;
}

vect3_t div_vect3(vect3_t v, float factor)
{
    vect3_t v_new = {.x = v.x / factor, .y = v.y / factor, .z = v.z / factor};
    return v_new;
}

vect3_t vec3_rotate_x(vect3_t v, float angle)
{
    vect3_t rotated_vector = {
        .x = v.x,
        .y = v.y * cos(angle) - v.z * sin(angle),
        .z = v.y * sin(angle) + v.z * cos(angle)};
    return rotated_vector;
}

vect3_t vec3_rotate_y(vect3_t v, float angle)
{
    vect3_t rotated_vector = {
        .x = v.x * cos(angle) - v.z * sin(angle),
        .y = v.y,
        .z = v.x * sin(angle) + v.z * cos(angle)};
    return rotated_vector;
}

vect3_t vec3_rotate_z(vect3_t v, float angle)
{
    vect3_t rotated_vector = {
        .x = v.x * cos(angle) - v.y * sin(angle),
        .y = v.x * sin(angle) + v.y * cos(angle),
        .z = v.z};
    return rotated_vector;
}

vect3_t cross_vect3(vect3_t a, vect3_t b)
{
    vect3_t result = {
        .x = a.y * b.z - a.z * b.y,
        .y = a.z * b.x - a.x * b.z,
        .z = a.x * b.y - a.y * b.x};
    return result;
}

float dot_vect3(vect3_t a, vect3_t b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void vec3_normalize(vect3_t *vec)
{
    float length = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
    vec->x /= length;
    vec->y /= length;
    vec->z /= length;
}