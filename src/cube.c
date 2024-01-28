#include "../include/header.h"
#include <SDL2/SDL_timer.h>

void MultiplyMatrixVector(vec3 *i, vec3 *o, mat4 *m) {
  float w = 1.0f;
  o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
  o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
  o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];

  w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

  if (w != 0.0f) {
    o->x /= w;
    o->y /= w;
    o->z /= w;
  }
}

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

void init_matRotZ(mat4 *matRotZ) {
  matRotZ->m[0][0] = cosf(fTheta);
  matRotZ->m[0][1] = sinf(fTheta);
  matRotZ->m[1][0] = -sinf(fTheta);
  matRotZ->m[1][1] = cosf(fTheta);
  matRotZ->m[2][2] = 1;
  matRotZ->m[3][3] = 1;
}

void init_matRotX(mat4 *matRotX) {
  matRotX->m[0][0] = 1;
  matRotX->m[1][1] = cosf(fTheta * 0.5f);
  matRotX->m[1][2] = sinf(fTheta * 0.5f);
  matRotX->m[2][1] = -sinf(fTheta * 0.5f);
  matRotX->m[2][2] = cosf(fTheta * 0.5f);
  matRotX->m[3][3] = 1;
}

void init_matRotY(mat4 *matRotY) {
  matRotY->m[0][0] = cosf(fTheta);
  matRotY->m[0][2] = -sinf(fTheta);
  matRotY->m[1][1] = 1;
  matRotY->m[2][0] = sinf(fTheta);
  matRotY->m[2][2] = cosf(fTheta);
  matRotY->m[3][3] = 1;
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

    // Project triangles from 3D --> 2D
    for (j = 0; j < 3; j++) {
      MultiplyMatrixVector(&triTranslated.p[j], &triProjected.p[j], &matProj);
    }

    // Scale into view
    triProjected.p[0].x += 1.0f;
    triProjected.p[0].y += 1.0f;
    triProjected.p[1].x += 1.0f;
    triProjected.p[1].y += 1.0f;
    triProjected.p[2].x += 1.0f;
    triProjected.p[2].y += 1.0f;
    triProjected.p[0].x *= 0.4f * (float)ScreenWidth;
    triProjected.p[0].y *= 0.4f * (float)ScreenHeight;
    triProjected.p[1].x *= 0.4f * (float)ScreenWidth;
    triProjected.p[1].y *= 0.4f * (float)ScreenHeight;
    triProjected.p[2].x *= 0.4f * (float)ScreenWidth;
    triProjected.p[2].y *= 0.4f * (float)ScreenHeight;

    c[i] = triProjected;
  }
}
