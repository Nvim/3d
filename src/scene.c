#include "../include/scene.h"
#include "../include/algebra.h"
#include "../include/mesh.h"
#include <SDL2/SDL_timer.h>

s_Matrices init_matrices() {
  s_Matrices matrices = {Matrix_MakeTranslation(0.0f, 0.0f, 6.0f),
                         Matrix_MakeProjection(90.0f,
                                               (float)State.ScreenHeight /
                                                   (float)State.ScreenWidth,
                                               0.1f, 1000.0f)};
  return matrices;
}

s_Scene init_scene() {
  float fTheta = 0.0f;
  vec3 vCamera = {0.0f, 0.0f, 0.0f, 1.0f};
  vec3 light_direction = {0.0f, 0.0f, -1.0f, 1.0f};
  float obj_depth = 8.0f; // distance to camera
  u8 rotateX = 0;
  u8 rotateZ = 0;
  u8 rotateY = 0;

  s_Scene render = {fTheta,  vCamera, light_direction, obj_depth,
                    rotateX, rotateZ, rotateY};
  return render;
}

// FPS stuff:
void wait_frame() {
  // sleep until we reach target frametime:
  const i16 time_to_wait = FRAMETIME - (SDL_GetTicks() - State.last_frame_time);
  if (time_to_wait > 0 && time_to_wait <= FRAMETIME) {
    SDL_Delay(time_to_wait);
  }
}

// updates cubes xyz by multiplying it with matrices:
void update_scene(triStack *stack) {

  // time between last frame and current frame in seconds:
  const float delta_time = (SDL_GetTicks() - State.last_frame_time) / 1000.0f;
  State.last_frame_time = SDL_GetTicks();

  u16 i;
  u8 j;
  // Set up rotation matrices - TODO: less redundant

  mat4 matRotZ, matRotX, matRotY;
  Scene.fTheta += 1.2f * delta_time;
  matRotZ = Matrix_MakeRotationZ(Scene.fTheta);
  matRotX = Matrix_MakeRotationX(Scene.fTheta);
  matRotY = Matrix_MakeRotationY(Scene.fTheta);
  // mat4 matTrans; // to offset the object back into the screen (hide clipping)
  mat4 matWorld; // product of all transformations

  matWorld = Matrix_MakeIdentity();

  // Apply rotations:
  if (Scene.rotateX) {
    matWorld = Matrix_MultiplyMatrix(&matWorld, &matRotX);
  }
  if (Scene.rotateY) {
    matWorld = Matrix_MultiplyMatrix(&matWorld, &matRotY);
  }
  if (Scene.rotateZ) {
    matWorld = Matrix_MultiplyMatrix(&matWorld, &matRotZ);
  }
  matWorld =
      Matrix_MultiplyMatrix(&matWorld, &Matrices.matTrans); // then translate

  triangle triProjected, triTransformed;

  // Draw Triangles
  i = 0;
  for (i = 0; i < Mesh.meshSize; i++) {
    triangle tri = Mesh.mesh[i];
    for (j = 0; j < 3; j++) {
      tri.p[j].w = 1;
      triProjected.p[j].w = 1;
      triTransformed.p[j].w = 1;
    }

    // apply world matrix:
    triTransformed.p[0] = Matrix_MultiplyVector(&matWorld, &tri.p[0]);
    triTransformed.p[1] = Matrix_MultiplyVector(&matWorld, &tri.p[1]);
    triTransformed.p[2] = Matrix_MultiplyVector(&matWorld, &tri.p[2]);

    // get the triangle's normal vector:
    vec3 normal, line1, line2;
    line1 = Vector_Sub(&triTransformed.p[1], &triTransformed.p[0]);
    line2 = Vector_Sub(&triTransformed.p[2], &triTransformed.p[0]);
    normal = Vector_CrossProduct(&line1, &line2);
    normal = Vector_Normalise(&normal);

    vec3 vCameraRay = Vector_Sub(&triTransformed.p[0], &Scene.vCamera);

    // rasterize only visible triangles:
    // printf("DP: %f\n", Vector_DotProduct(&normal, &vCameraRay));
    if (Vector_DotProduct(&normal, &vCameraRay) < 0.0f) {

      //  Project triangles from 3D --> 2D and normalize it
      triProjected.p[0] =
          Matrix_MultiplyVector(&Matrices.matProj, &triTransformed.p[0]);
      triProjected.p[1] =
          Matrix_MultiplyVector(&Matrices.matProj, &triTransformed.p[1]);
      triProjected.p[2] =
          Matrix_MultiplyVector(&Matrices.matProj, &triTransformed.p[2]);
      triProjected.p[0] = Vector_Div(&triProjected.p[0], triProjected.p[0].w);
      triProjected.p[1] = Vector_Div(&triProjected.p[1], triProjected.p[1].w);
      triProjected.p[2] = Vector_Div(&triProjected.p[2], triProjected.p[2].w);

      // min brightness at 0.1:
      Scene.light_direction = Vector_Normalise(&Scene.light_direction);
      float brightness =
          fmax(0.1f, Vector_DotProduct(&Scene.light_direction, &normal));
      triProjected.light = brightness;

      vec3 vOffsetView = {1.0f, 1.0f, 0.0f, 1.0f};
      triProjected.p[0] = Vector_Add(&triProjected.p[0], &vOffsetView);
      triProjected.p[1] = Vector_Add(&triProjected.p[1], &vOffsetView);
      triProjected.p[2] = Vector_Add(&triProjected.p[2], &vOffsetView);
      triProjected.p[0].x *= 0.5f * (float)State.ScreenWidth;
      triProjected.p[0].y *= 0.5f * (float)State.ScreenHeight;
      triProjected.p[1].x *= 0.5f * (float)State.ScreenWidth;
      triProjected.p[1].y *= 0.5f * (float)State.ScreenHeight;
      triProjected.p[2].x *= 0.5f * (float)State.ScreenWidth;
      triProjected.p[2].y *= 0.5f * (float)State.ScreenHeight;

      stack_push(stack, triProjected);
    }
  }
  // printf("Stack Full, %d triangles\n", stack->count);
}
