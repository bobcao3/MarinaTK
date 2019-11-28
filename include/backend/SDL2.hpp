#pragma once

#include <backend.hpp>

#include <SDL2/SDL.h>

namespace MTK::Backend {

class SDL2 : public Backend {
private:
  SDL_Window *window;
  SDL_Renderer *ren;

public:
  SDL2();
  ~SDL2();

  void fillRect(float x, float y, float width, float height);
  void strokeRect(float x, float y, float width, float height);
  void clearRect(float x, float y, float width, float height);

  void presentBuffer();
  void presentRegion(float x, float y, float width, float height);
};

}