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

vect3_t sub_vect3(vect3_t v1, vect3_t v2)
{
    vect3_t v_new = {.x = v1.x - v2.x, .y = v1.y - v2.y, .z = v1.z - v1.z};
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
