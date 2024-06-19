#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "display.h"
#include "vector.h"

const float fov = 128;
const int N_POINTS_IN_CUBE = (9 * 9 * 9);

bool is_running = false;

vec3_t cube_points[9 * 9 * 9];
vec2_t projected_cube_points[9 * 9 * 9];

void setup(void)
{
    // Alocando quantidade de memoria do colorbuffer
    color_buffer = (u_int32_t *)malloc(sizeof(u_int32_t) * (WINDOW_SIZE_X * WINDOW_SIZE_y));

    // Criando sdl_texture para mostrarmos o colorbuffer
    color_buffer_texture = SDL_CreateTexture(
        render,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WINDOW_SIZE_X,
        WINDOW_SIZE_y);

    // Criando os pontos do cubo
    int pointers_counter = 0;
    for (float x = -1; x <= 1; x += 0.25)
    {
        for (float y = -1; y <= 1; y += 0.25)
        {
            for (float z = -1; z <= 1; z += 0.25)
            {
                // (0.25, 0.25, 0.25) -> Precisa ser escalonado
                vec3_t new_point = {x, y, z};
                cube_points[pointers_counter++] = new_point;
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
        {
            is_running = false;
            break;
        }
    }
}

// Função que recebe um vetor 3d e retorna um vetor 2d projetado ortogonalmente
vec2_t project_vector(vec3_t point)
{
    vec2_t projected_pointer = {
        .x = (point.x * fov),
        .y = (point.y * fov)};

    return projected_pointer;
}

void update()
{
    // Projetar todos os pontos do cubo
    for (int i = 0; i <= N_POINTS_IN_CUBE; i++)
    {
        projected_cube_points[i] = project_vector(cube_points[i]);
    }
}

void renderer(void)
{
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderClear(render);

    draw_grid(0xFFFFFFFF);

    for (int i = 0; i < N_POINTS_IN_CUBE; i++)
    {
        vec2_t point = projected_cube_points[i];
        draw_retangle(
            0xff00ff,
            point.x + (WINDOW_SIZE_X / 2),
            point.y + (WINDOW_SIZE_y / 2),
            10,
            10);
    }

    render_color_buffer();
    clean_color_buffer(0xFF000000);

    SDL_RenderPresent(render);
}

int main(int argc, char *argv[])
{
    is_running = initialize_window();

    setup();
    while (is_running)
    {
        process_input();
        update();
        renderer();
    }

    destroy();

    return 0;
}
