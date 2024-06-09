#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "display.h"

bool is_running = false;

void setup(void) {
    // Alocando quantidade de memoria do colorbuffer
    color_buffer = (u_int32_t*) malloc(sizeof(u_int32_t) * (WINDOW_SIZE_X * WINDOW_SIZE_y));

    // Criando sdl_texture para mostrarmos o colorbuffer
    color_buffer_texture = SDL_CreateTexture(
        render,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WINDOW_SIZE_X,
        WINDOW_SIZE_y
    );

}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
                break;
            }
    }
}

void update() {}

void renderer(void) {
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

    draw_retangle(0xFFFF00FF, 90, 90, 100, 100);
    //draw_grid(0x3eff00);
    draw_pixel(20, 20, 0xFFFF00FF);


    render_color_buffer(); 
    clean_color_buffer(0xffffff);

    SDL_RenderPresent(render); 
}

int main(void) {
    is_running = initialize_window();

    setup();
    while (is_running) {
        process_input();
        update();
        renderer();
    }

    destroy();

    return 0;
}
