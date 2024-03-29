#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2) // 6 cube faces, 2 triangles per face

extern vect3_t cube_vertices[N_CUBE_VERTICES];
extern face_t cube_faces[N_CUBE_FACES];

void load_cube_mesh_data(void);
void load_obj_file_data(char *filename);

typedef struct
{
    vect3_t *vertices;
    face_t *faces;
    vect3_t rotation;
    vect3_t scale;
    vect3_t translation;
} mesh_t;

extern mesh_t mesh;

#endif