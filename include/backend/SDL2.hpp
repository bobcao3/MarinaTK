#pragma once

#include <backend.hpp>

#include <SDL2/SDL.h>

struct FC_Font;

#include <unordered_map>
#include <string>

namespace MTK::Backend {

class SDL2 : public Backend {
private:
  static size_t getFontNameHash(std::string name, int size);

private:
  SDL_Window *window;
  SDL_Renderer *ren;

  std::unordered_map<size_t, FC_Font *> fonts;
  FC_Font* curr_font = NULL;

public:
  SDL2();
  ~SDL2();

  void fillRect(float x, float y, float width, float height);
  void strokeRect(float x, float y, float width, float height);
  void clearRect(float x, float y, float width, float height);

  void presentBuffer();
  void presentRegion(float x, float y, float width, float height);

  void font(const char *name, int size);
  void fillText(const char *str, float x, float y);
};

}