#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define FPS 30
#define FRAME_TARGET_TIME 1000 / FPS

extern int window_width;
extern int window_height;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern SDL_Texture *color_buffer_texture;
extern uint32_t *color_buffer;

bool initialize_window(void);

void draw_grid(void);

void draw_pixel(int x, int y, uint32_t color);

void draw_rect(int x, int y, int w, int h, uint32_t color);

void render_color_buffer(void);

void clear_color_buffer(uint32_t color);

void destroy_window(void);

void draw_line(int x0, int y0, int x1, int y1, uint32_t color);

#endif