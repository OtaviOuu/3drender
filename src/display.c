#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* color_buffer_texture = NULL;
u_int32_t* color_buffer = NULL;
int WINDOW_SIZE_X = 800;
int WINDOW_SIZE_y = 600;


bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error loading std\n");
        return false;
    }

    // Buscano x e y maximos
    SDL_DisplayMode display_mode;  
    SDL_GetCurrentDisplayMode(0, &display_mode);

    WINDOW_SIZE_X = display_mode.w;
    WINDOW_SIZE_y = display_mode.h;


    // Crianjo a janela
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_SIZE_X,
        WINDOW_SIZE_y, 
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error SDL window\n");
        return false;
    }
    // sdl render
    render = SDL_CreateRenderer(window, -1, 0);
    if (!render) {
        fprintf(stderr, "Error in render\n");
        return false;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void clean_color_buffer(uint32_t color) {
    for (int i = 0; i < WINDOW_SIZE_X*WINDOW_SIZE_y; i++) {
        color_buffer[i] = color;
    }
}

void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(WINDOW_SIZE_X * sizeof(uint32_t))
    );

    SDL_RenderCopy(
        render,
        color_buffer_texture,
        NULL,
        NULL
    );
}

void draw_retangle(uint32_t color, int x, int y, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            color_buffer[(WINDOW_SIZE_X * current_y) + current_x] = color;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color) {
    color_buffer[(WINDOW_SIZE_X * y) + x] = color;
}

void draw_grid(uint32_t color) {
    // (i, k)
    for (int x = 0; x < (WINDOW_SIZE_X); x++) {
        for (int y = 0; y < (WINDOW_SIZE_y); y++) {
            if (x % 10 == 0 || y % 10 == 0) {
                color_buffer[(WINDOW_SIZE_X * y) + x] = color; 
            }
        }
    }
}

void destroy(void) {
    free(color_buffer);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
