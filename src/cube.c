#include "../include/header.h"
#include <SDL2/SDL_timer.h>
#include <math.h>

// FPS stuff:
void wait_frame() {
  // sleep until we reach target frametime:
  const i16 time_to_wait = FRAMETIME - (SDL_GetTicks() - last_frame_time);
  if (time_to_wait > 0 && time_to_wait <= FRAMETIME) {
    SDL_Delay(time_to_wait);
  }
}

// updates cubes xyz by multiplying it with matrices:
void update_cube(triStack *stack) {

  // time between last frame and current frame in seconds:
  const float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
  last_frame_time = SDL_GetTicks();

  u16 i;
  u8 j;
  // Set up rotation matrices - TODO: less redundant
  mat4 matTrans = Matrix_MakeTranslation(0.0f, 0.0f, 6.0f);
  mat4 matProj = Matrix_MakeProjection(
      90.0f, (float)ScreenHeight / (float)ScreenWidth, 0.1f, 1000.0f);

  mat4 matRotZ, matRotX, matRotY;
  fTheta += 1.2f * delta_time;
  matRotZ = Matrix_MakeRotationZ(fTheta);
  matRotX = Matrix_MakeRotationX(fTheta);
  matRotY = Matrix_MakeRotationY(fTheta);
  // mat4 matTrans; // to offset the object back into the screen (hide clipping)
  mat4 matWorld; // product of all transformations

  matWorld = Matrix_MakeIdentity();

  // Apply rotations:
  if (rotateX) {
    matWorld = Matrix_MultiplyMatrix(&matWorld, &matRotX);
  }
  if (rotateY) {
    matWorld = Matrix_MultiplyMatrix(&matWorld, &matRotY);
  }
  if (rotateZ) {
    matWorld = Matrix_MultiplyMatrix(&matWorld, &matRotZ);
  }
  matWorld = Matrix_MultiplyMatrix(&matWorld, &matTrans); // then translate

  triangle triProjected, triTransformed;

  // Draw Triangles
  i = 0;
  for (i = 0; i < meshSize; i++) {
    triangle tri = mesh[i];
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

    vec3 vCameraRay = Vector_Sub(&triTransformed.p[0], &vCamera);

    // rasterize only visible triangles:
    // printf("DP: %f\n", Vector_DotProduct(&normal, &vCameraRay));
    if (Vector_DotProduct(&normal, &vCameraRay) < 0.0f) {

      //  Project triangles from 3D --> 2D and normalize it
      triProjected.p[0] = Matrix_MultiplyVector(&matProj, &triTransformed.p[0]);
      triProjected.p[1] = Matrix_MultiplyVector(&matProj, &triTransformed.p[1]);
      triProjected.p[2] = Matrix_MultiplyVector(&matProj, &triTransformed.p[2]);
      triProjected.p[0] = Vector_Div(&triProjected.p[0], triProjected.p[0].w);
      triProjected.p[1] = Vector_Div(&triProjected.p[1], triProjected.p[1].w);
      triProjected.p[2] = Vector_Div(&triProjected.p[2], triProjected.p[2].w);

      // min brightness at 0.1:
      light_direction = Vector_Normalise(&light_direction);
      float brightness =
          fmax(0.1f, Vector_DotProduct(&light_direction, &normal));
      triProjected.light = brightness;

      vec3 vOffsetView = {1.0f, 1.0f, 0.0f, 1.0f};
      triProjected.p[0] = Vector_Add(&triProjected.p[0], &vOffsetView);
      triProjected.p[1] = Vector_Add(&triProjected.p[1], &vOffsetView);
      triProjected.p[2] = Vector_Add(&triProjected.p[2], &vOffsetView);
      triProjected.p[0].x *= 0.5f * (float)ScreenWidth;
      triProjected.p[0].y *= 0.5f * (float)ScreenHeight;
      triProjected.p[1].x *= 0.5f * (float)ScreenWidth;
      triProjected.p[1].y *= 0.5f * (float)ScreenHeight;
      triProjected.p[2].x *= 0.5f * (float)ScreenWidth;
      triProjected.p[2].y *= 0.5f * (float)ScreenHeight;

      stack_push(stack, triProjected);
    }
  }
  // printf("Stack Full, %d triangles\n", stack->count);
}
