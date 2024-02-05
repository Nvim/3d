#ifndef HEADER_H
#define HEADER_H

#include "algebra.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdint.h>

#define ASSERT(_e, ...)                                                        \
  if (!(_e)) {                                                                 \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  }

#define FPS 60
#define FRAMETIME (1000 / FPS)
#define WINDOW_W 600
#define WINDOW_H 600

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
  vec3 p[3];
  float light; // between 0 and 1
} triangle;

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  const u16 ScreenWidth;
  const u16 ScreenHeight;
  u32 last_frame_time;
  u8 gameRunning; // if 0, then break gameloop
} s_State;

extern s_State State;

/* main.c :  */
void process_input();

#endif
