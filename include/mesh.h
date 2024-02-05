#ifndef MESH_H

#define MESH_H

#include "header.h"

typedef struct {
  triangle *mesh;
  u32 meshSize;
} s_Mesh;

extern s_Mesh Mesh;

/* obj_loader.c */
u8 load_obj();

#endif // !MESH_H
