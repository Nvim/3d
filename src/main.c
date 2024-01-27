#include "../include/header.h"
#include <time.h>

s_Color cubeColors = {255, 255, 255, 255};

triangle cubeMesh[12];
s_Game game;
const int ScreenWidth = 1024;
const int ScreenHeight = 1024;
u8 gameRunning = 1; // game loop
mat4 matProj;
u32 last_frame_time = 0;
float fTheta = 0.0f;

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
    case SDLK_z:
      // rotate_cube_z(cubeMesh);
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

  ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL_Init failed: %s\n",
         SDL_GetError());

  ASSERT(IMG_Init(IMG_INIT_PNG), "IMG_Init failed: %s\n", SDL_GetError());
  ASSERT(init_window() == EXIT_SUCCESS, "Window Init failed.\n");

  init_cube();
  init_matProj();

  triangle *c =
      (triangle *)malloc(sizeof(triangle) * 12); // nouveau cube: 12 tris
  /* ******* START LOOP HERE *********** */

  window_clear();
  window_display();
  while (gameRunning) {
    process_input();
    update_cube(c);

    // render triangles:
    window_clear();
    for (int i = 0; i < 12; i++) {
      triangle tri = c[i];
      render_triangle(&cubeColors, &tri);
    }
    window_display();
  }
  window_cleanUp();
  free(c);
  return EXIT_SUCCESS;
}
