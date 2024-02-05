#include "../include/header.h"
#include "../include/mesh.h"
#include "../include/render.h"
#include "../include/scene.h"
#include "../include/stack.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

s_Color cubeColors = {255, 255, 255, 255};
s_Color red = {255, 0, 0, 255};
s_Color black = {0, 0, 0, 255};

s_State State = {
    NULL,     // window
    NULL,     // renderer
    WINDOW_W, // ScreenHeight
    WINDOW_H, // ScreenWidth
    0,        // last_frame_time
    1         // gameRunning
};

s_Mesh Mesh = {
    NULL, // mesh
    0     // meshSize
};

s_Scene Scene;
s_Matrices Matrices;

int main() {

  ASSERT(load_obj(), "Loading obj file failed.\n");
  ASSERT(&Mesh.mesh[0] != NULL, "Loading obj file failed: mesh empty.\n");
  ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "SDL_Init failed: %s\n",
         SDL_GetError());

  ASSERT(IMG_Init(IMG_INIT_PNG), "IMG_Init failed: %s\n", SDL_GetError());
  ASSERT(init_window() == EXIT_SUCCESS, "Window Init failed.\n");

  Scene = init_scene();
  Matrices = init_matrices(); // constant matrices
  srand(time(NULL));

  u8 i;
  SDL_Color cols = (SDL_Color){rand() % 254, rand() % 254, rand() % 254, 255};
  SDL_Color tmpCols;
  triStack trisToRender;
  init_stack(&trisToRender);
  SDL_Vertex vertices[3];

  /* ******* START LOOP HERE *********** */

  window_clear();
  window_display();
  while (State.gameRunning) {
    process_input();
    wait_frame();                // wait to display next frame
    update_scene(&trisToRender); // fills the stack

    // render triangles:
    window_clear();
    i = 0;
    while (!stack_empty(&trisToRender)) { // foreach triangle
      triangle tri = stack_pop(&trisToRender);
      tmpCols = cols;
      tmpCols.r *= tri.light;
      tmpCols.g *= tri.light;
      tmpCols.b *= tri.light;
      for (int j = 0; j < 3; j++) { // foreach point of the tri
        SDL_FPoint p = {tri.p[j].x, tri.p[j].y};
        SDL_Vertex v = {p, tmpCols, (SDL_FPoint){1, 1}};
        vertices[j] = v;
      }
      // render_triangle(&cubeColors, &tri);
      SDL_RenderGeometry(State.renderer, NULL, vertices, 3, NULL, 0);
      i++;
    }
    window_display();
  }
  window_cleanUp();
  free(Mesh.mesh);
  return EXIT_SUCCESS;
}

void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    State.gameRunning = 0;
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      State.gameRunning = 0;
      break;
    case SDLK_DOWN:
      if (Scene.rotateZ == 0) {
        Scene.rotateZ = 1;
      } else {
        Scene.rotateZ = 0;
      }
      break;
    case SDLK_UP:
      if (Scene.rotateX == 0) {
        Scene.rotateX = 1;
      } else {
        Scene.rotateX = 0;
      }
      break;
    case SDLK_LEFT:
      if (Scene.rotateY == 0) {
        Scene.rotateY = 1;
      } else {
        Scene.rotateY = 0;
      }
      break;
    }
  }
}
