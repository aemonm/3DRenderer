#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "triangle.h"

triangle_t triangles_to_render[N_MESH_FACES];

bool is_running = false;
int previous_frame_time = 0;

int fov_factor = 640;

vect3_t camera_position = {.x = 0, .y = 0, .z = -5};
vect3_t cube_rotation = {.x = 0, .y = 0, .z = 0};

void setup(void)
{
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
    if (!color_buffer)
        fprintf(stderr, "Error allocating color buffer\n");
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
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
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks64() - previous_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
    {
        SDL_Delay(time_to_wait);
    }
    previous_frame_time = SDL_GetTicks64();
    cube_rotation.x += 0.001;
    cube_rotation.y += 0.001;
    cube_rotation.z += 0.001;
    for (int i = 0; i < N_MESH_FACES; i++)
    {
        face_t mesh_face = mesh_faces[i];
        vect3_t face_vertices[3];
        face_vertices[0] = mesh_vertices[mesh_face.a - 1];
        face_vertices[1] = mesh_vertices[mesh_face.b - 1];
        face_vertices[2] = mesh_vertices[mesh_face.c - 1];
        triangle_t projected_triangle;
        for (int j = 0; j < 3; j++)
        {
            vect3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, cube_rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, cube_rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, cube_rotation.z);
            transformed_vertex.z -= camera_position.z;

            vect2_t projected_point = project(transformed_vertex);

            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }
        triangles_to_render[i] = projected_triangle;
    }
}

void render(void)
{
    // draw_grid();
    for (int i = 0; i < N_MESH_FACES; i++)
    {
        triangle_t triangle = triangles_to_render[i];

        // render vertices;
        for (int j = 0; j < 3; j++)
        {
            draw_rect(triangle.points[j].x, triangle.points[j].y, 3, 3, 0xffffff00);
        }
        // render lines
        for (int j = 0; j < 3; j++)
        {
            vect2_t next_points = j == 2 ? triangle.points[0] : triangle.points[j + 1];
            draw_line(triangle.points[j].x, triangle.points[j].y, next_points.x, next_points.y, 0xffffff00);
        }
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
