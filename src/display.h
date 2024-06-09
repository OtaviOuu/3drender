#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>


extern SDL_Window* window;
extern SDL_Renderer* render;
extern SDL_Texture* color_buffer_texture;
extern u_int32_t* color_buffer;
extern int WINDOW_SIZE_X;
extern int WINDOW_SIZE_y;

bool initialize_window(void);
void draw_grid(uint32_t color);
void draw_retangle(uint32_t color, int x, int y, int width, int height);
void render_color_buffer(void);
void clean_color_buffer(uint32_t color);
void destroy(void);

#endif