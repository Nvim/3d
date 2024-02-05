#include "../include/header.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>

s_Color bgColor = {40, 40, 40, 255};

u8 init_window() {
  State.window =
      SDL_CreateWindow("State", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       State.ScreenWidth, State.ScreenHeight, SDL_WINDOW_SHOWN);
  ASSERT(State.window, "Window failed to init: %s\n", SDL_GetError());

  State.renderer = SDL_CreateRenderer(
      State.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  ASSERT(State.renderer, "Renderer failed to init: %s\n", SDL_GetError());

  SDL_SetRenderDrawColor(State.renderer, bgColor.r, bgColor.g, bgColor.b, 255);
  return EXIT_SUCCESS;
}

void render_rectangle(const SDL_Rect *rect, const s_Color *colors) {
  SDL_SetRenderDrawColor(State.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderDrawRect(State.renderer, rect) < 0) {
    fprintf(stderr, "Erreur Creation Rectangle: %s", SDL_GetError());
  }
}

void render_filled_rectangle(const SDL_Rect *rect, const s_Color *colors) {
  SDL_SetRenderDrawColor(State.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderFillRect(State.renderer, rect) < 0) {
    fprintf(stderr, "Erreur Fill Rectangle: %s", SDL_GetError());
  }
}

void render_line(const s_Color *colors, const vec2 *point1,
                 const vec2 *point2) {
  SDL_SetRenderDrawColor(State.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderDrawLine(State.renderer, (int)point1->x, (int)point1->y,
                         (int)point2->x, (int)point2->y)) {
    fprintf(stderr, "Erreur Draw Line: %s", SDL_GetError());
  }
}

void render_triangle(const s_Color *colors, const triangle *tri) {
  SDL_SetRenderDrawColor(State.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  SDL_RenderDrawLine(State.renderer, tri->p[0].x, tri->p[0].y, tri->p[1].x,
                     tri->p[1].y);
  SDL_RenderDrawLine(State.renderer, tri->p[1].x, tri->p[1].y, tri->p[2].x,
                     tri->p[2].y);
  SDL_RenderDrawLine(State.renderer, tri->p[2].x, tri->p[2].y, tri->p[0].x,
                     tri->p[0].y);
}

void window_clear() {
  SDL_SetRenderDrawColor(State.renderer, bgColor.r, bgColor.g, bgColor.b, 255);
  SDL_RenderClear(State.renderer);
}

void window_display() { SDL_RenderPresent(State.renderer); }

void window_cleanUp() {
  SDL_DestroyRenderer(State.renderer);
  SDL_DestroyWindow(State.window);
  SDL_Quit();
  printf("Cleanup done\n");
}
