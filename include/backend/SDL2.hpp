/*
 * Copyright 2019 Cheng Cao (bobcao3)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <backend.hpp>

#include <SDL2/SDL.h>

struct FC_Font;

#include <string>
#include <unordered_map>

namespace MTK::Backend
{
class SDL2 : public Backend {
  private:
  SDL_Window *window;
  SDL_Renderer *ren;

  std::unordered_map<size_t, FC_Font *> fonts;
  FC_Font *curr_font = NULL;

  SDL_Color curr_fill_color = { 0, 0, 0, 255 };

  static size_t getFontNameHash(std::string name, int size);

  void fillColor32(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  bool shouldClose = false;

  eventCallback key_cb = NULL, pointer_cb = NULL;

  static int SDLCALL window_events(void *data, SDL_Event *ev);

  public:
  SDL2();
  ~SDL2();

  glm::vec2 getSize();

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