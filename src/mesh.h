#ifndef MESH_H
#define MESH_H

#define N_MESH_VERTICES 8

#include "vector.h"
#include "triangle.h"

extern vect3_t mesh_vertices[N_MESH_VERTICES];

#define N_MESH_FACES (6 * 2) // 6 cube faces, 2 triangles per face
extern face_t mesh_faces[N_MESH_FACES];

#endif