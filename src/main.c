#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

bool is_running = false;


SDL_Window* window = NULL;
SDL_Renderer* render = NULL;

SDL_Texture* color_buffer_texture = NULL;
u_int32_t* color_buffer = NULL;

int WINDOW_SIZE_X;
int WINDOW_SIZE_y;


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



void renderer(void) {
 SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
 SDL_RenderClear(render);


  draw_retangle(0xFFFF00FF, 90, 90, 100, 100);
  draw_grid(0x3eff00);
 render_color_buffer(); // Render
 clean_color_buffer(0xffffff); // Clean


 SDL_RenderPresent(render); 
}


void destroy(void) {
 free(color_buffer);
 SDL_DestroyRenderer(render);
 SDL_DestroyWindow(window);
 SDL_Quit();
}





int main(void) {
 is_running = initialize_window();

 //game loop
 setup();
 while (is_running) {
  process_input();
  update();
  renderer();
 }

 destroy();

 return 0;
}