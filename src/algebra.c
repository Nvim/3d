#include "../include/header.h"

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
