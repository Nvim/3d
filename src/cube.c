#include "../include/header.h"
#include <SDL2/SDL_timer.h>

void MultiplyMatrixVector(vec3 *i, vec3 *o, mat4 *m) {
  o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
  o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
  o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
  float w =
      i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

  if (w != 0.0f) {
    o->x /= w;
    o->y /= w;
    o->z /= w;
  }
}

void init_cube() {

  // South:
  cubeMesh[0].p[0] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[0].p[1] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[0].p[2] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[1].p[0] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[1].p[1] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[1].p[2] = (vec3){1.0f, 0.0f, 0.0f};

  // East:
  cubeMesh[2].p[0] = (vec3){1.0f, 0.0f, 0.0f};
  cubeMesh[2].p[1] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[2].p[2] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[3].p[0] = (vec3){1.0f, 0.0f, 0.0f};
  cubeMesh[3].p[1] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[3].p[2] = (vec3){1.0f, 0.0f, 1.0f};

  // North
  cubeMesh[4].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[4].p[1] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[4].p[2] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[5].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[5].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[5].p[2] = (vec3){0.0f, 0.0f, 1.0f};

  // West:
  cubeMesh[6].p[0] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[6].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[6].p[2] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[7].p[0] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[7].p[1] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[7].p[2] = (vec3){0.0f, 0.0f, 0.0f};

  // Top:
  cubeMesh[8].p[0] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[8].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[8].p[2] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[9].p[0] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[9].p[1] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[9].p[2] = (vec3){1.0f, 1.0f, 0.0f};

  // Bottom:
  cubeMesh[10].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[10].p[2] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[10].p[2] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[11].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[11].p[2] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[11].p[2] = (vec3){1.0f, 0.0f, 0.0f};
}

// updates cubes xyz by multiplying it with matrices:
void update_cube(triangle *c) {

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
  mat4 matRotZ, matRotX;
  fTheta += 1.0f * delta_time;

  // // Rotation Z
  matRotZ.m[0][0] = cosf(fTheta);
  matRotZ.m[0][1] = sinf(fTheta);
  matRotZ.m[1][0] = -sinf(fTheta);
  matRotZ.m[1][1] = cosf(fTheta);
  matRotZ.m[2][2] = 1;
  matRotZ.m[3][3] = 1;

  // // Rotation X
  matRotX.m[0][0] = 1;
  matRotX.m[1][1] = cosf(fTheta * 0.5f);
  matRotX.m[1][2] = sinf(fTheta * 0.5f);
  matRotX.m[2][1] = -sinf(fTheta * 0.5f);
  matRotX.m[2][2] = cosf(fTheta * 0.5f);
  matRotX.m[3][3] = 1;

  // Draw Triangles
  for (int i = 0; i < 12; i++) {
    triangle tri = cubeMesh[i];
    triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

    // Rotate in Z-Axis
    MultiplyMatrixVector(&tri.p[0], &triRotatedZ.p[0], &matRotZ);
    MultiplyMatrixVector(&tri.p[1], &triRotatedZ.p[1], &matRotZ);
    MultiplyMatrixVector(&tri.p[2], &triRotatedZ.p[2], &matRotZ);

    // Rotate in X-Axis
    MultiplyMatrixVector(&triRotatedZ.p[0], &triRotatedZX.p[0], &matRotX);
    MultiplyMatrixVector(&triRotatedZ.p[1], &triRotatedZX.p[1], &matRotX);
    MultiplyMatrixVector(&triRotatedZ.p[2], &triRotatedZX.p[2], &matRotX);

    // Offset into the screen
    triTranslated = triRotatedZX;
    triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
    triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
    triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

    // Project triangles from 3D --> 2D
    MultiplyMatrixVector(&triTranslated.p[0], &triProjected.p[0], &matProj);
    MultiplyMatrixVector(&triTranslated.p[1], &triProjected.p[1], &matProj);
    MultiplyMatrixVector(&triTranslated.p[2], &triProjected.p[2], &matProj);

    // Scale into view
    triProjected.p[0].x += 1.0f;
    triProjected.p[0].y += 1.0f;
    triProjected.p[1].x += 1.0f;
    triProjected.p[1].y += 1.0f;
    triProjected.p[2].x += 1.0f;
    triProjected.p[2].y += 1.0f;
    triProjected.p[0].x *= 0.5f * (float)ScreenWidth;
    triProjected.p[0].y *= 0.5f * (float)ScreenHeight;
    triProjected.p[1].x *= 0.5f * (float)ScreenWidth;
    triProjected.p[1].y *= 0.5f * (float)ScreenHeight;
    triProjected.p[2].x *= 0.5f * (float)ScreenWidth;
    triProjected.p[2].y *= 0.5f * (float)ScreenHeight;

    c[i] = triProjected;
  }
}
