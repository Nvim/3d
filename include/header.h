#ifndef HEADER_H
#define HEADER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(_e, ...)                                                        \
  if (!(_e)) {                                                                 \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  }

#define FPS 30
#define FRAMETIME (1000 / FPS)

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} s_Game;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} s_Color;

typedef struct {
  double x, y, z, w;
} vec3;

typedef struct {
  int x, y;
} vec2;

typedef struct {
  vec3 p[3];
  float light; // between 0 and 1
} triangle;

typedef struct {
  float m[4][4];
} mat4;

typedef struct triStackNode {
  triangle tri;
  struct triStackNode *next;
} triStackNode;

typedef struct {
  u32 count;
  triStackNode *top;
} triStack;

/* ********** VARS ************ */

extern u8 gameRunning;
extern u32 last_frame_time;
extern float fTheta;
extern u8 rotateX;
extern u8 rotateZ;
extern u8 rotateY;
extern u32 meshSize;
const extern int ScreenWidth;
const extern int ScreenHeight;
extern s_Game game;
// extern mat4 matProj;
// extern triangle cubeMesh[12]; // 12 triangles, 2 par face
// extern triStack mesh;
extern triangle *mesh;
extern vec3 vCamera;
extern vec3 light_direction;

/* ********** METHODS ************ */

void init_cube();
u8 init_window();
void window_clear();
void window_display();
void window_cleanUp();
void render_triangle(s_Color *colors, triangle *tri);
void render_rectangle(SDL_Rect *rect, s_Color *colors);
void update_cube(triStack *stack);
void rotate_cube_z(triangle *c);
void rotate_cube_x(triangle *c);

void init_matRotY(mat4 *matRotY);
void init_matRotX(mat4 *matRotX);
void init_matRotZ(mat4 *matRotZ);
void MultiplyMatrixVector(vec3 *i, vec3 *o, mat4 *m);

void init_stack(triStack *stack);
int stack_empty(triStack *stack);
void stack_push(triStack *stack, triangle tri);
triangle stack_pop(triStack *stack);
triangle stack_peek(triStack *stack);
u8 load_obj();

////

void MultiplyMatrixVector(vec3 *i, vec3 *o, mat4 *m);
vec3 Matrix_MultiplyVector(mat4 *m, vec3 *i);
mat4 Matrix_MakeIdentity();
mat4 Matrix_MakeRotationX(float fAngleRad);
mat4 Matrix_MakeRotationY(float fAngleRad);
mat4 Matrix_MakeRotationZ(float fAngleRad);
mat4 Matrix_MakeTranslation(float x, float y, float z);
mat4 Matrix_MakeProjection(float fFovDegrees, float fAspectRatio, float fNear,
                           float fFar);
mat4 Matrix_MultiplyMatrix(mat4 *m1, mat4 *m2);

vec3 Vector_Add(vec3 *v1, vec3 *v2);
vec3 Vector_Sub(vec3 *v1, vec3 *v2);
vec3 Vector_Mul(vec3 *v1, float k);
vec3 Vector_Div(vec3 *v1, float k);
float Vector_DotProduct(vec3 *v1, vec3 *v2);
float Vector_Length(vec3 *v);
vec3 Vector_Normalise(vec3 *v);
vec3 Vector_CrossProduct(vec3 *v1, vec3 *v2);

#endif
