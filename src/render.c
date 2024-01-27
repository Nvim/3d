#include "../include/header.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <unistd.h>

s_Color bgColor = {40, 40, 40, 255};

u8 init_window() {
  game.window =
      SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
  ASSERT(game.window, "Window failed to init: %s\n", SDL_GetError());

  game.renderer = SDL_CreateRenderer(
      game.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  ASSERT(game.renderer, "Renderer failed to init: %s\n", SDL_GetError());

  SDL_SetRenderDrawColor(game.renderer, bgColor.r, bgColor.g, bgColor.b, 255);
  return EXIT_SUCCESS;
}

void render_rectangle(SDL_Rect *rect, s_Color *colors) {
  SDL_SetRenderDrawColor(game.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderDrawRect(game.renderer, rect) < 0) {
    fprintf(stderr, "Erreur Creation Rectangle: %s", SDL_GetError());
  }
}

void render_filled_rectangle(SDL_Rect *rect, s_Color *colors) {
  SDL_SetRenderDrawColor(game.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderFillRect(game.renderer, rect) < 0) {
    fprintf(stderr, "Erreur Fill Rectangle: %s", SDL_GetError());
  }
}

void render_line(s_Color *colors, vec2 *point1, vec2 *point2) {
  SDL_SetRenderDrawColor(game.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  if (SDL_RenderDrawLine(game.renderer, (int)point1->x, (int)point1->y,
                         (int)point2->x, (int)point2->y)) {
    fprintf(stderr, "Erreur Draw Line: %s", SDL_GetError());
  }
}

void render_triangle(s_Color *colors, triangle *tri) {
  SDL_SetRenderDrawColor(game.renderer, colors->r, colors->g, colors->b,
                         colors->a);
  SDL_RenderDrawLine(game.renderer, tri->p[0].x, tri->p[0].y, tri->p[1].x,
                     tri->p[1].y);
  SDL_RenderDrawLine(game.renderer, tri->p[1].x, tri->p[1].y, tri->p[2].x,
                     tri->p[2].y);
  SDL_RenderDrawLine(game.renderer, tri->p[2].x, tri->p[2].y, tri->p[0].x,
                     tri->p[0].y);
}

void window_clear() {
  // SDL_SetRenderDrawColor(game.renderer, bgColor.r, bgColor.g, bgColor.b,
  // 255);
  SDL_SetRenderDrawColor(game.renderer, bgColor.r, bgColor.g, bgColor.b, 255);
  SDL_RenderClear(game.renderer);
}

void window_display() { SDL_RenderPresent(game.renderer); }

void window_cleanUp() {
  SDL_DestroyRenderer(game.renderer);
  SDL_DestroyWindow(game.window);
  SDL_Quit();
  printf("Cleanup done\n");
}
