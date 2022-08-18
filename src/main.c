#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"
#include "triangle.h"
#include "darray.h"

triangle_t *triangles_to_render = NULL;

bool is_running = false;
int previous_frame_time = 0;

int fov_factor = 640;

vect3_t camera_position = {0, 0, 0};

void setup(void)
{
    color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
    if (!color_buffer)
        fprintf(stderr, "Error allocating color buffer\n");
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

    // load_cube_mesh_data();
    load_obj_file_data("./assets/cube.obj");
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
    triangles_to_render = NULL;
    mesh.rotation.x += 0.001;
    mesh.rotation.y += 0.001;
    mesh.rotation.z += 0.001;

    for (int i = 0; i < array_length(mesh.faces); i++)
    {
        face_t mesh_face = mesh.faces[i];

        vect3_t face_vertices[3];
        face_vertices[0] = mesh.vertices[mesh_face.a - 1];
        face_vertices[1] = mesh.vertices[mesh_face.b - 1];
        face_vertices[2] = mesh.vertices[mesh_face.c - 1];

        vect3_t transformed_vertices[3];

        for (int j = 0; j < 3; j++)
        {
            vect3_t transformed_vertex = face_vertices[j];

            transformed_vertex = vec3_rotate_x(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotate_y(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotate_z(transformed_vertex, mesh.rotation.z);
            transformed_vertex.z += 5;

            transformed_vertices[j] = transformed_vertex;
        }

        triangle_t projected_triangle;

        // Check Back face culling
        vect3_t vec_a = transformed_vertices[0];
        vect3_t vec_b = transformed_vertices[1];
        vect3_t vec_c = transformed_vertices[2];

        // Get B-A and C-A vectors
        vect3_t vec_ab = sub_vect3(vec_b, vec_a);
        vect3_t vec_ac = sub_vect3(vec_c, vec_a);
        vec3_normalize(&vec_ab);
        vec3_normalize(&vec_ac);
        vect3_t camera_ray = sub_vect3(camera_position, vec_a);

        // Computer normal vector using cross product
        vect3_t normal = cross_vect3(vec_ab, vec_ac);
        vec3_normalize(&normal);

        float dot_normal_camera = dot_vect3(normal, camera_ray);

        if (dot_normal_camera < 0)
        {
            continue;
        }

        for (int j = 0; j < 3; j++)
        {

            vect2_t projected_point = project(transformed_vertices[j]);

            projected_point.x += (window_width / 2);
            projected_point.y += (window_height / 2);

            projected_triangle.points[j] = projected_point;
        }
        array_push(triangles_to_render, projected_triangle);
    }
}

void render(void)
{
    int triangle_count = array_length(triangles_to_render);
    for (int i = 0; i < triangle_count; i++)
    {
        triangle_t triangle = triangles_to_render[i];

        draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xffffff00);
        draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xffffff00);
        draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xffffff00);
        draw_filled_triangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xff000000);
        draw_triangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xffffffff);
    }
    // draw_filled_triangle(300, 100, 50, 400, 500, 700, 0xffffff00);
    array_free(triangles_to_render);
    render_color_buffer();
    clear_color_buffer(0xFF111111);
    SDL_RenderPresent(renderer);
}

void free_resources(void)
{
    array_free(mesh.faces);
    array_free(mesh.vertices);
    free(color_buffer);
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
    free_resources();
    return 0;
}
