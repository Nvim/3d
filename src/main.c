#include "../include/header.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>
#include <time.h>

s_Color cubeColors = {255, 255, 255, 255};
s_Color red = {255, 0, 0, 255};
s_Color black = {0, 0, 0, 255};

triangle cubeMesh[12];
s_Game game;
const int ScreenWidth = 512;
const int ScreenHeight = 512;
u8 gameRunning = 1; // game loop
mat4 matProj;
u32 last_frame_time = 0;
float fTheta = 0.0f;
u8 rotateX = 0;
u8 rotateY = 0;
u8 rotateZ = 0;

void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    gameRunning = 0;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      gameRunning = 0;
      break;
    case SDLK_DOWN:
      if (rotateZ == 0) {
        rotateZ = 1;
      } else {
        rotateZ = 0;
      }
      break;
    case SDLK_UP:
      if (rotateX == 0) {
        rotateX = 1;
      } else {
        rotateX = 0;
      }
      break;
    case SDLK_LEFT:
      if (rotateY == 0) {
        rotateY = 1;
      } else {
        rotateY = 0;
      }
      break;
    }
  }
}

void init_matProj() {
  float fNear = 0.1f;
  float fFar = 1000.0f;
  float fFov = 90.0f;
  float fAspectRatio = (float)ScreenHeight / (float)ScreenWidth;
  float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

  matProj.m[0][0] = fAspectRatio * fFovRad;
  matProj.m[1][1] = fFovRad;
  matProj.m[2][2] = fFar / (fFar - fNear);
  matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
  matProj.m[2][3] = 1.0f;
  matProj.m[3][3] = 0.0f;
}

int main() {

  srand(time(NULL));
  ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL_Init failed: %s\n",
         SDL_GetError());

  ASSERT(IMG_Init(IMG_INIT_PNG), "IMG_Init failed: %s\n", SDL_GetError());
  ASSERT(init_window() == EXIT_SUCCESS, "Window Init failed.\n");

  init_cube();
  init_matProj();

  SDL_Color colors[12];
  for (int i = 0; i < 12; i += 2) {
    colors[i] = (SDL_Color){rand() % 254, rand() % 254, rand() % 254, 255};
    colors[i + 1] = colors[i];
  }

  triangle *c =
      (triangle *)malloc(sizeof(triangle) * 12); // nouveau cube: 12 tris

  SDL_Vertex vertices[3];

  /* ******* START LOOP HERE *********** */

  window_clear();
  window_display();
  while (gameRunning) {
    process_input();
    update_cube(c);

    // render triangles:
    window_clear();
    for (int i = 0; i < 12; i++) { // foreach triangle
      triangle tri = c[i];
      // if (i == 5 || i == 6) {
      //   printf("Tri #%d XYZ: {(%f, %f, %f), (%f, %f, %f), (%f, %f, %f)}\n",
      //   i,
      //          tri.p[0].x, tri.p[0].y, tri.p[0].z, tri.p[1].x, tri.p[1].y,
      //          tri.p[1].z, tri.p[2].x, tri.p[2].y, tri.p[2].z);
      // }
      for (int j = 0; j < 3; j++) { // foreach point of the tri
        SDL_FPoint p = {tri.p[j].x, tri.p[j].y};
        SDL_Vertex v = {p, colors[i], (SDL_FPoint){1, 1}};
        // if (i == 7 || i == 6) {
        //   v.color = (SDL_Color){255, 0, 0, 255};
        // }
        vertices[j] = v;
      }
      render_triangle(&black, &tri);
      SDL_RenderGeometry(game.renderer, NULL, vertices, 3, NULL, 0);
    }
    window_display();
  }
  window_cleanUp();
  free(c);
  return EXIT_SUCCESS;
}
