#ifndef SCENE_H

#define SCENE_H

#include "header.h"
#include "stack.h"

typedef struct {
  mat4 matTrans;
  mat4 matProj;
} s_Matrices;

typedef struct {
  float fTheta;
  vec3 vCamera;
  vec3 light_direction;
  float obj_depth; // distance to camera
  u8 rotateX;
  u8 rotateZ;
  u8 rotateY;
} s_Scene;

extern s_Matrices Matrices;
extern s_Scene Scene;

/* scene.c : */
void wait_frame();
void update_scene(triStack *stack);
s_Scene init_scene();
s_Matrices init_matrices();

#endif
