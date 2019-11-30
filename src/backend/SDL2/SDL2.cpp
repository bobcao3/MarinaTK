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

#include <backend.hpp>
#include <backend/SDL2.hpp>

#include <functional>
#include <iostream>

#include "SDL_FontCache/SDL_FontCache.h"

namespace MTK::Backend
{
size_t SDL2::getFontNameHash(std::string name, int size)
{
  return std::hash<std::string>{}(name) ^ size;
}

SDL2::SDL2()
{
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

  ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (ren == nullptr) {
    SDL_DestroyWindow(window);
    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    exit(-1);
  }

  SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

  SDL_AddEventWatch(window_events, this);

  fillColor32(255, 255, 255, 255);
  SDL_RenderClear(ren);
  fillColor32(0, 0, 0, 255);
}

SDL2::~SDL2()
{
  for (auto f : fonts) {
    FC_FreeFont(f.second);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}

glm::vec2 SDL2::getSize()
{
  int x, y;
  SDL_GetWindowSize(window, &x, &y);
  return glm::vec2(x, y);
}

// Drawing funcitons
void SDL2::fillRect(float x, float y, float width, float height)
{
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = width;
  r.h = height;

  SDL_RenderFillRect(ren, &r);
}

void SDL2::strokeRect(float x, float y, float width, float height)
{
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = width;
  r.h = height;

  SDL_RenderDrawRect(ren, &r);
}

void SDL2::clearRect(float x, float y, float width, float height)
{
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  fillRect(x, y, width, height);
  fillColor32(curr_fill_color.r, curr_fill_color.g, curr_fill_color.b,
              curr_fill_color.a);
}

void SDL2::clear()
{
  SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
  SDL_RenderClear(ren);
  fillColor32(curr_fill_color.r, curr_fill_color.g, curr_fill_color.b,
              curr_fill_color.a);
}

void SDL2::presentBuffer()
{
  SDL_RenderPresent(ren);
}

void SDL2::presentRegion([[maybe_unused]] float x, [[maybe_unused]] float y,
                         [[maybe_unused]] float width,
                         [[maybe_unused]] float height)
{
  // SDL2 does not have partial update
  presentBuffer();
}

void SDL2::font(const char *name, int size)
{
  std::string name_s = std::string(name);
  if (fonts.find(getFontNameHash(name_s, size)) != fonts.end()) {
    curr_font = fonts[getFontNameHash(name_s, size)];
  } else {
    FC_Font *font = FC_CreateFont();
    FC_LoadFont(font, ren, name, size, FC_MakeColor(0, 0, 0, 255),
                TTF_STYLE_NORMAL);
    curr_font = font;
    fonts.insert({ getFontNameHash(name_s, size), font });
  }
}

void SDL2::fillText(const char *str, float x, float y)
{
  if (!curr_font)
    return;

  FC_SetDefaultColor(curr_font, curr_fill_color);
  FC_Draw(curr_font, ren, x, y, str);
}

void SDL2::fillColor(float r, float g, float b, float a)
{
  fillColor32(r * 255, g * 255, b * 255, a * 255);
}

void SDL2::fillColor32(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  curr_fill_color.r = r;
  curr_fill_color.g = g;
  curr_fill_color.b = b;
  curr_fill_color.a = a;
  SDL_SetRenderDrawColor(ren, r, g, b, a);
}

int SDLCALL SDL2::window_events(void *data, SDL_Event *event)
{
  SDL2 *backend = (SDL2 *)data;

  if (event->type == SDL_QUIT) {
    backend->shouldClose = true;
  } else if (event->type == SDL_KEYDOWN) {
    if (backend->key_cb) {
      EventKey e = { backend, "SomeKey", DOWN };
      backend->key_cb(&e);
    }
  } else if (event->type == SDL_KEYUP) {
    if (backend->key_cb) {
      EventKey e = { backend, "SomeKey", UP };
      backend->key_cb(&e);
    }
  } else if (event->type == SDL_MOUSEMOTION) {
    if (backend->pointer_cb) {
      EventPointer e = { backend, "Mouse", HOVER, event->motion.x,
                         event->motion.y };
      backend->pointer_cb(&e);
    }
  }

  return 0;
}

void SDL2::waitEvents()
{
  SDL_Event ev;
  SDL_WaitEvent(&ev);
}

bool SDL2::isTerminated()
{
  return shouldClose;
}

void SDL2::setKeyCallback(eventCallback cb)
{
  key_cb = cb;
}

void SDL2::setPointerCallback(eventCallback cb)
{
  pointer_cb = cb;
}

} // namespace MTK::Backend