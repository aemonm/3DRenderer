
#include "display.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *color_buffer_texture = NULL;
color_t *color_buffer = NULL;

int window_width = 800;
int window_height = 600;

void draw_pixel(int x, int y, color_t color)
{
    if (x >= 0 && y >= 0 && x < window_width && y < window_height)
    {

        color_buffer[(window_width * y) + x] = color;
    }
}

bool initialize_window(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Error Initializing SDL\n");
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    window_width = display_mode.w;
    window_height = display_mode.h;

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS);

    if (!window)
    {
        fprintf(stderr, "Error creating window\n");
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer)
    {
        fprintf(stderr, "Error creating renderer\n");
        return false;
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    return true;
}

void render_color_buffer(void)
{
    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width * sizeof(color_t)));
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(color_t color)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            draw_pixel(x, y, color);
        }
    }
}

void draw_grid(void)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            if (x % 10 == 0 || y % 10 == 0)
                draw_pixel(x, y, 0xFFFFFFFF);
        }
    }
}

void draw_rect(int x, int y, int w, int h, color_t color)
{
    for (int yy = y; yy <= y + h; yy++)
    {
        for (int xx = x; xx <= x + w; xx++)
        {
            draw_pixel(xx, yy, color);
        }
    }
}

void destroy_window(void)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void draw_line(int x0, int y0, int x1, int y1, color_t color)
{
    int delta_x = x1 - x0;
    int delta_y = y1 - y0;
    float side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);

    float inc_x = delta_x / (float)side_length;
    float inc_y = delta_y / (float)side_length;

    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i <= side_length; i++)
    {
        draw_pixel(round(current_x), round(current_y), color);
        current_x += inc_x;
        current_y += inc_y;
    }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}
