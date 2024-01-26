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

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
} s_Game;

extern s_Game game;

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

const int ScreenWidth = 512;
const int ScreenHeight = 512;

typedef struct {
  double x, y, z;
} vec3;

typedef struct {
  int x, y;
} vec2;

typedef struct {
  vec3 p[3];
} triangle;

typedef struct {
  float m[4][4];
} mat4;

extern triangle cubeMesh[12]; // 12 triangles, 2 par face
//
void init_cube();
void render_triangle(s_Color *colors, triangle tri);

#endif
