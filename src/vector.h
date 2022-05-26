#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    float x;
    float y;
} vect2_t;

typedef struct
{
    float x;
    float y;
    float z;
} vect3_t;

float get_vect2_length(vect2_t v);
float get_vect3_length(vect3_t v);

vect2_t add_vect2(vect2_t v1, vect2_t v2);
vect3_t add_vect3(vect3_t v1, vect3_t v2);

vect2_t sub_vect2(vect2_t v1, vect2_t v2);
vect3_t sub_vect3(vect3_t v1, vect3_t v2);

vect3_t vec3_rotate_x(vect3_t vec, float angle);
vect3_t vec3_rotate_y(vect3_t vec, float angle);
vect3_t vec3_rotate_z(vect3_t vec, float angle);

#endif