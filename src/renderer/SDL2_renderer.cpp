#include <renderer.hpp>
#include <renderer_backend/SDL2_renderer.hpp>

#include <iostream>

SDL2_Renderer::SDL2_Renderer() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  window = SDL_CreateWindow("SDL2", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(-1);
  }

  ren = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr) {
    SDL_DestroyWindow(window);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(-1);
  }

  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderClear(ren);
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}

SDL2_Renderer::~SDL2_Renderer() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

// Drawing funcitons
void SDL2_Renderer::fillRect(float x, float y, float width, float height) {
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = width;
  r.h = height;

  SDL_RenderFillRect(ren, &r);
}

void SDL2_Renderer::strokeRect(float x, float y, float width, float height) {
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = width;
  r.h = height;

  SDL_RenderDrawRect(ren, &r);
}

void SDL2_Renderer::clearRect(float x, float y, float width, float height) {
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  fillRect(x, y, width, height);
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
}

void SDL2_Renderer::presentBuffer() { SDL_RenderPresent(ren); }

void SDL2_Renderer::presentRegion([[maybe_unused]] float x,
                                  [[maybe_unused]] float y,
                                  [[maybe_unused]] float width,
                                  [[maybe_unused]] float height) {
  // SDL2 does not have partial update
  presentBuffer();
}