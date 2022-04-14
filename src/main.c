#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

bool is_running = false;

const int N_POINTS = 9 * 9 * 9;
vect3_t cube_points[N_POINTS];
vect2_t projected_points[N_POINTS];
int fov_factor = 640;

vect3_t camera_position = {.x = 0, .y = 0, .z = -5};

void setup(void)
{
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
    if (!color_buffer)
        fprintf(stderr, "Error allocating color buffer\n");
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

    int point_count = 0;
    for (float x = -1; x <= 1; x += .25)
    {
        for (float y = -1; y <= 1; y += .25)
        {
            for (float z = -1; z <= 1; z += .25)
            {
                vect3_t new_point = {.x = x, .y = y, .z = z};
                cube_points[point_count++] = new_point;
            }
        }
    }
}

void process_input(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            is_running = false;
        break;
    }
}

// Function that receives a 3D point and projects it into a 2D Point
vect2_t project(vect3_t point)
{
    vect2_t projected_point = {
        .x = (point.x * fov_factor) / point.z,
        .y = (point.y * fov_factor) / point.z};
    return projected_point;
}

void update(void)
{

    for (int i = 0; i < N_POINTS; i++)
    {
        vect3_t point = cube_points[i];
        point.z -= camera_position.z;
        vect2_t projected_point = project(point);
        projected_points[i] = projected_point;
    }
}

void render(void)
{
    // draw_grid();
    for (int i = 0; i < N_POINTS; i++)
    {
        vect2_t projected_point = projected_points[i];
        draw_rect(projected_point.x + window_width / 2, projected_point.y + window_height / 2, 4, 4, 0xFFFFFF00);
    }
    render_color_buffer();
    clear_color_buffer(0xFF111111);
    SDL_RenderPresent(renderer);
}

int main(void)
{
    is_running = initialize_window();
    setup();

    while (is_running)
    {
        process_input();
        update();
        render();
    }
    destroy_window();
    return 0;
}
