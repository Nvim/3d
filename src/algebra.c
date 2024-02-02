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

vec3 Matrix_MultiplyVector(mat4 *m, vec3 *i) {
  vec3 v = {0.0f, 0.0f, 0.0f, 1.0f};
  v.x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] +
        i->w * m->m[3][0];
  v.y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] +
        i->w * m->m[3][1];
  v.z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] +
        i->w * m->m[3][2];
  v.w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] +
        i->w * m->m[3][3];
  return v;
}

// returns matrix full of 0s
mat4 Matrix_Init() {
  mat4 matrix;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix.m[i][j] = 0.0f;
    }
  }
  return matrix;
}

mat4 Matrix_MakeIdentity() {
  mat4 matrix = Matrix_Init();
  matrix.m[0][0] = 1.0f;
  matrix.m[1][1] = 1.0f;
  matrix.m[2][2] = 1.0f;
  matrix.m[3][3] = 1.0f;
  return matrix;
}

mat4 Matrix_MakeRotationX(float fAngleRad) {
  mat4 matrix = Matrix_Init();
  matrix.m[0][0] = 1.0f;
  matrix.m[1][1] = cosf(fAngleRad);
  matrix.m[1][2] = sinf(fAngleRad);
  matrix.m[2][1] = -sinf(fAngleRad);
  matrix.m[2][2] = cosf(fAngleRad);
  matrix.m[3][3] = 1.0f;
  return matrix;
}

mat4 Matrix_MakeRotationY(float fAngleRad) {
  mat4 matrix = Matrix_Init();
  matrix.m[0][0] = cosf(fAngleRad);
  matrix.m[0][2] = sinf(fAngleRad);
  matrix.m[2][0] = -sinf(fAngleRad);
  matrix.m[1][1] = 1.0f;
  matrix.m[2][2] = cosf(fAngleRad);
  matrix.m[3][3] = 1.0f;
  return matrix;
}

mat4 Matrix_MakeRotationZ(float fAngleRad) {
  mat4 matrix = Matrix_Init();
  matrix.m[0][0] = cosf(fAngleRad);
  matrix.m[0][1] = sinf(fAngleRad);
  matrix.m[1][0] = -sinf(fAngleRad);
  matrix.m[1][1] = cosf(fAngleRad);
  matrix.m[2][2] = 1.0f;
  matrix.m[3][3] = 1.0f;
  return matrix;
}

mat4 Matrix_MakeTranslation(float x, float y, float z) {
  mat4 matrix = Matrix_Init();
  matrix.m[0][0] = 1.0f;
  matrix.m[1][1] = 1.0f;
  matrix.m[2][2] = 1.0f;
  matrix.m[3][3] = 1.0f;
  matrix.m[3][0] = x;
  matrix.m[3][1] = y;
  matrix.m[3][2] = z;
  return matrix;
}

mat4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear,
                           float fFar) {
  float fFovRad = 1.0f / tanf(fFovDegrees * 0.5f / 180.0f * 3.14159f);
  mat4 matrix = Matrix_Init();
  matrix.m[0][0] = fAspectRatio * fFovRad;
  matrix.m[1][1] = fFovRad;
  matrix.m[2][2] = fFar / (fFar - fNear);
  matrix.m[3][2] = (-fFar * fNear) / (fFar - fNear);
  matrix.m[2][3] = 1.0f;
  matrix.m[3][3] = 0.0f;
  return matrix;
}

mat4 Matrix_MultiplyMatrix(mat4 *m1, mat4 *m2) {
  mat4 matrix;
  for (int c = 0; c < 4; c++)
    for (int r = 0; r < 4; r++)
      matrix.m[r][c] = m1->m[r][0] * m2->m[0][c] + m1->m[r][1] * m2->m[1][c] +
                       m1->m[r][2] * m2->m[2][c] + m1->m[r][3] * m2->m[3][c];
  return matrix;
}

vec3 Vector_Add(vec3 *v1, vec3 *v2) {
  return (vec3){v1->x + v2->x, v1->y + v2->y, v1->z + v2->z};
}

vec3 Vector_Sub(vec3 *v1, vec3 *v2) {
  return (vec3){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
}

vec3 Vector_Mul(vec3 *v1, float k) {
  return (vec3){v1->x * k, v1->y * k, v1->z * k};
}

vec3 Vector_Div(vec3 *v1, float k) {
  return (vec3){v1->x / k, v1->y / k, v1->z / k};
}

float Vector_DotProduct(vec3 *v1, vec3 *v2) {
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

float Vector_Length(vec3 *v) { return sqrtf(Vector_DotProduct(v, v)); }

vec3 Vector_Normalise(vec3 *v) {
  float l = Vector_Length(v);
  return (vec3){v->x / l, v->y / l, v->z / l};
}

vec3 Vector_CrossProduct(vec3 *v1, vec3 *v2) {
  vec3 v;
  v.x = v1->y * v2->z - v1->z * v2->y;
  v.y = v1->z * v2->x - v1->x * v2->z;
  v.z = v1->x * v2->y - v1->y * v2->x;
  return v;
}

// void init_matRotZ(mat4 *matRotZ) {
//   matRotZ->m[0][0] = cosf(fTheta);
//   matRotZ->m[0][1] = sinf(fTheta);
//   matRotZ->m[1][0] = -sinf(fTheta);
//   matRotZ->m[1][1] = cosf(fTheta);
//   matRotZ->m[2][2] = 1;
//   matRotZ->m[3][3] = 1;
// }
//
// void init_matRotX(mat4 *matRotX) {
//   matRotX->m[0][0] = 1;
//   matRotX->m[1][1] = cosf(fTheta * 0.5f);
//   matRotX->m[1][2] = sinf(fTheta * 0.5f);
//   matRotX->m[2][1] = -sinf(fTheta * 0.5f);
//   matRotX->m[2][2] = cosf(fTheta * 0.5f);
//   matRotX->m[3][3] = 1;
// }
//
// void init_matRotY(mat4 *matRotY) {
//   matRotY->m[0][0] = cosf(fTheta);
//   matRotY->m[0][2] = -sinf(fTheta);
//   matRotY->m[1][1] = 1;
//   matRotY->m[2][0] = sinf(fTheta);
//   matRotY->m[2][2] = cosf(fTheta);
//   matRotY->m[3][3] = 1;
// }
