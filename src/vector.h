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

vect2_t mul_vect2(vect2_t v, float factor);
vect3_t mul_vect3(vect3_t v, float factor);

vect2_t div_vect2(vect2_t v, float factor);
vect3_t div_vect3(vect3_t v, float factor);

vect3_t cross_vect3(vect3_t a, vect3_t b);

float dot_vect3(vect3_t a, vect3_t b);
float dot_vect2(vect2_t a, vect2_t b);

vect3_t vec3_rotate_x(vect3_t vec, float angle);
vect3_t vec3_rotate_y(vect3_t vec, float angle);
vect3_t vec3_rotate_z(vect3_t vec, float angle);

void vec2_normalize(vect2_t *vec);
void vec3_normalize(vect3_t *vec);

#endif