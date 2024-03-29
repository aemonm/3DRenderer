#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define FPS 240
#define FRAME_TARGET_TIME 1000 / FPS

enum cull_method
{
    CULL_NONE,
    CULL_BACKFACE
} cull_method;

enum render_method
{
    RENDER_WIRE,
    RENDER_WIRE_VERTEX,
    RENDER_FILL_TRIANGLE,
    RENDER_FILL_TRIANGLE_WIRE
} render_method;

extern int window_width;
extern int window_height;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern SDL_Texture *color_buffer_texture;

typedef uint32_t color_t;

extern color_t *color_buffer;

bool initialize_window(void);

void draw_grid(void);

void draw_pixel(int x, int y, color_t color);

void draw_rect(int x, int y, int w, int h, color_t color);

void render_color_buffer(void);

void clear_color_buffer(color_t color);

void destroy_window(void);

void draw_line(int x0, int y0, int x1, int y1, color_t color);

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);

#endif