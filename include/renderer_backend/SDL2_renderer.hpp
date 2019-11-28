#pragma once

#include <renderer.hpp>

#include <SDL2/SDL.h>

class SDL2_Renderer : public Renderer {
private:
  SDL_Window *window;
  SDL_Renderer *ren;

public:
  SDL2_Renderer();
  ~SDL2_Renderer();

  void fillRect(float x, float y, float width, float height);
  void strokeRect(float x, float y, float width, float height);
  void clearRect(float x, float y, float width, float height);

  void presentBuffer();
  void presentRegion(float x, float y, float width, float height);
};