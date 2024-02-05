#ifndef RENDER_H

#define RENDER_H
#include "header.h"

/* render.c : */
u8 init_window();
void window_clear();
void window_display();
void window_cleanUp();
void render_triangle(const s_Color *colors, const triangle *tri);
void render_rectangle(const SDL_Rect *rect, const s_Color *colors);

#endif // !RENDER_H
