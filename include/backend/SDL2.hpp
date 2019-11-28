#pragma once

#include <backend.hpp>

#include <SDL2/SDL.h>

struct FC_Font;

#include <string>
#include <unordered_map>

namespace MTK::Backend {

class SDL2 : public Backend {
private:
  SDL_Window *window;
  SDL_Renderer *ren;

  std::unordered_map<size_t, FC_Font *> fonts;
  FC_Font *curr_font = NULL;

  SDL_Color curr_fill_color = {0, 0, 0, 255};

  static size_t getFontNameHash(std::string name, int size);

  void fillColor32(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  bool shouldClose = false;

  eventCallback key_cb = NULL, pointer_cb = NULL;

  int mouseX = -1, mouseY = -1;

  static int SDLCALL window_events(void* data, SDL_Event* ev);

public:
  SDL2();
  ~SDL2();

  void fillRect(float x, float y, float width, float height);
  void strokeRect(float x, float y, float width, float height);
  void clearRect(float x, float y, float width, float height);
  void clear();

  void presentBuffer();
  void presentRegion(float x, float y, float width, float height);

  void font(const char *name, int size);
  void fillText(const char *str, float x, float y);

  void fillColor(float r, float g, float b, float a);

  void waitEvents();
  bool isTerminated();

  void setKeyCallback(eventCallback cb);
  void setPointerCallback(eventCallback cb);
};

} // namespace MTK::Backend