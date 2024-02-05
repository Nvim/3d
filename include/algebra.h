#ifndef ALGEBRA_H

#define ALGEBRA_H

typedef struct {
  double x, y, z, w;
} vec3;

typedef struct {
  int x, y;
} vec2;

typedef struct {
  float m[4][4];
} mat4;

/* algebra.c : */
vec3 Matrix_MultiplyVector(const mat4 *m, const vec3 *i);

// returns matrix full of 0s
mat4 Matrix_Init();
mat4 Matrix_MakeIdentity();
mat4 Matrix_MakeRotationX(const float fAngleRad);
mat4 Matrix_MakeRotationY(const float fAngleRad);
mat4 Matrix_MakeRotationZ(const float fAngleRad);
mat4 Matrix_MakeTranslation(const float x, const float y, const float z);
mat4 Matrix_MakeProjection(const float fFovDegrees, const float fAspectRatio,
                           const float fNear, const float fFar);

mat4 Matrix_MultiplyMatrix(const mat4 *m1, const mat4 *m2);
vec3 Vector_Add(const vec3 *v1, const vec3 *v2);
vec3 Vector_Sub(const vec3 *v1, const vec3 *v2);
vec3 Vector_Mul(const vec3 *v1, const float k);
vec3 Vector_Div(const vec3 *v1, const float k);
float Vector_DotProduct(const vec3 *v1, const vec3 *v2);
float Vector_Length(const vec3 *v);
vec3 Vector_Normalise(const vec3 *v);
vec3 Vector_CrossProduct(const vec3 *v1, const vec3 *v2);

/* void MultiplyMatrixVector(vec3 *i, vec3 *o, mat4 *m); */
#endif // !ALGEBRA_H
