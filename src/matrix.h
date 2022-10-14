#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"

typedef struct
{
    float m[4][4];
} mat4_t;

mat4_t mat4_identity(void);
mat4_t mat4_make_scale(float sx, float sy, float sz);
vect4_t mat4_mul_vec(mat4_t m, vect4_t v);

#endif