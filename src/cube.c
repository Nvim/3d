#include "../include/header.h"
#include <SDL2/SDL_timer.h>

void init_cube() {

  cubeMesh[0].p[0] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[0].p[1] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[0].p[2] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[1].p[0] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[1].p[1] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[1].p[2] = (vec3){1.0f, 0.0f, 0.0f};
  cubeMesh[2].p[0] = (vec3){1.0f, 0.0f, 0.0f};
  cubeMesh[2].p[1] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[2].p[2] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[3].p[0] = (vec3){1.0f, 0.0f, 0.0f};
  cubeMesh[3].p[1] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[3].p[2] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[4].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[4].p[1] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[4].p[2] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[5].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[5].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[5].p[2] = (vec3){0.0f, 0.0f, 1.0f};

  cubeMesh[6].p[0] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[6].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[6].p[2] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[7].p[0] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[7].p[1] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[7].p[2] = (vec3){0.0f, 0.0f, 0.0f};

  cubeMesh[8].p[0] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[8].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[8].p[2] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[9].p[0] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[9].p[1] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[9].p[2] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[10].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[10].p[1] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[10].p[2] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[11].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[11].p[1] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[11].p[2] = (vec3){1.0f, 0.0f, 0.0f};
}

void rotate_cube_z(triangle *c) {
  mat4 matRotZ;
  u8 i, j;
  for (i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matRotZ.m[i][j] = 0;
    }
  }
  init_matRotZ(&matRotZ);
  triangle triRotatedZ;

  for (i = 0; i < 12; i++) {
    triangle tri = cubeMesh[i];

    for (j = 0; j < 4; j++) {
      MultiplyMatrixVector(&tri.p[j], &triRotatedZ.p[j], &matRotZ);
    }

    c[i] = triRotatedZ;
  }
}

void rotate_cube_x(triangle *c) {
  mat4 matRotX;
  u8 i, j;
  for (i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matRotX.m[i][j] = 0;
    }
  }
  init_matRotX(&matRotX);
  triangle triRotatedX;

  for (i = 0; i < 12; i++) {
    triangle tri = cubeMesh[i];

    for (j = 0; j < 4; j++) {
      MultiplyMatrixVector(&tri.p[j], &triRotatedX.p[j], &matRotX);
    }

    c[i] = triRotatedX;
  }
}

// updates cubes xyz by multiplying it with matrices:
void update_cube(triStack *stack) {

  // FPS stuff:
  // sleep until we reach target frametime:
  i16 time_to_wait = FRAMETIME - (SDL_GetTicks() - last_frame_time);
  if (time_to_wait > 0 && time_to_wait <= FRAMETIME) {
    SDL_Delay(time_to_wait);
  }

  // time between last frame and current frame in seconds:
  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
  last_frame_time = SDL_GetTicks();
  // printf("Time between frames: %f\n", delta_time);

  // Set up rotation matrices
  mat4 matRotZ, matRotX, matRotY;
  u8 i, j;
  fTheta += 1.0f * delta_time;
  for (i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matRotX.m[i][j] = 0;
      matRotZ.m[i][j] = 0;
      matRotY.m[i][j] = 0;
    }
  }
  init_matRotX(&matRotX);
  init_matRotZ(&matRotZ);
  init_matRotY(&matRotY);
  triangle triProjected, triTranslated, triRotatedX, triRotatedZ, triRotatedY;

  // Draw Triangles
  for (i = 0; i < 12; i++) {
    triangle tri = cubeMesh[i];

    // x rotation:
    if (rotateX == 1) {
      for (j = 0; j < 3; j++) {
        MultiplyMatrixVector(&tri.p[j], &triRotatedX.p[j], &matRotX);
      }
      tri = triRotatedX;
    }

    // z rotation:
    if (rotateZ == 1) {
      for (j = 0; j < 3; j++) {
        MultiplyMatrixVector(&tri.p[j], &triRotatedZ.p[j], &matRotZ);
      }
      tri = triRotatedZ;
    }

    // y rotation:
    if (rotateY == 1) {
      for (j = 0; j < 3; j++) {
        MultiplyMatrixVector(&tri.p[j], &triRotatedY.p[j], &matRotY);
      }
      tri = triRotatedY;
    }

    // Offset into the screen
    triTranslated = tri;
    for (j = 0; j < 3; j++) {
      triTranslated.p[j].z = tri.p[j].z + 3.0f;
    }

    vec3 normal, line1, line2;
    line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
    line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
    line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

    line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
    line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
    line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

    normal.x = line1.y * line2.z - line1.z * line2.y;
    normal.y = line1.z * line2.x - line1.x * line2.z;
    normal.z = line1.x * line2.y - line1.y * line2.x;

    // normalize the normal
    float len =
        sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal.x /= len;
    normal.y /= len;
    normal.z /= len;

    // rasterize only visible triangles:
    // if (normal.z < 0) {
    if (normal.x * (triTranslated.p[0].x - vCamera.x) +
            normal.y * (triTranslated.p[0].y - vCamera.y) +
            normal.z * (triTranslated.p[0].z - vCamera.z) <
        0) {

      // calculate luminescence:
      float l = sqrtf(light_direction.x * light_direction.x +
                      light_direction.y * light_direction.y +
                      light_direction.z * light_direction.z);
      light_direction.x /= l;
      light_direction.y /= l;
      light_direction.z /= l;

      float dp = normal.x * light_direction.x + normal.y * light_direction.y +
                 normal.z * light_direction.z;

      //  Project triangles from 3D --> 2D
      for (j = 0; j < 3; j++) {
        MultiplyMatrixVector(&triTranslated.p[j], &triProjected.p[j], &matProj);
      }

      // Apply light level and scale into view
      triProjected.light = dp;
      // printf("DP: %f\n", dp);
      triProjected.p[0].x += 0.8f;
      triProjected.p[0].y += 0.8f;
      triProjected.p[1].x += 0.8f;
      triProjected.p[1].y += 0.8f;
      triProjected.p[2].x += 0.8f;
      triProjected.p[2].y += 0.8f;
      triProjected.p[0].x *= 0.4f * (float)ScreenWidth;
      triProjected.p[0].y *= 0.4f * (float)ScreenHeight;
      triProjected.p[1].x *= 0.4f * (float)ScreenWidth;
      triProjected.p[1].y *= 0.4f * (float)ScreenHeight;
      triProjected.p[2].x *= 0.4f * (float)ScreenWidth;
      triProjected.p[2].y *= 0.4f * (float)ScreenHeight;

      // c[i] = triProjected;
      stack_push(stack, triProjected);
    }
  }
}
