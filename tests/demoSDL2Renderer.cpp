#include <backend/SDL2.hpp>
#include <mtk.hpp>

#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

using namespace MTK;

int mouseX, mouseY;
bool hasEvents = true;

void onPointer(Backend::Event *_e) {
  Backend::EventPointer *e = (Backend::EventPointer *)_e;

  if (e->action == Backend::HOVER) {
    mouseX = e->x;
    mouseY = e->y;
  }
}

using namespace std::chrono_literals;

int main() {
  Backend::SDL2 *r = new Backend::SDL2();

  r->setPointerCallback(&onPointer);

  uint32_t fpstick = SDL_GetTicks();
  int fps = 0;
  int fps_count = 0;

  while (!r->isTerminated()) {
    r->waitEvents();

    fps_count++;

    r->clear();
    r->fillColor(0.0, 0.0, 0.0, 1.0);
    r->fillRect(50, 50, 100, 50);
    r->fillColor(1.0, 0.0, 0.0, 1.0);
    r->strokeRect(25, 25, 150, 100);
    r->clearRect(100, 75, 50, 50);

    r->font("/usr/share/fonts/truetype/NotoSans-Regular.ttf", 20);
    r->fillText("Test FONT!", 50, 200);

    r->font("/usr/share/fonts/truetype/NotoSans-Regular.ttf", 30);
    r->fillText("Test FONT BIG!", 50, 250);

    r->fillColor(0.0, 1.0, 1.0, 1.0);
    r->font("/usr/share/fonts/truetype/NotoSans-Regular.ttf", 20);
    r->fillText("Test FONT cache", 50, 300);

    std::stringstream ss;
    ss << "FPS: " << fps;

    r->fillText(ss.str().data(), 50, 350);

    r->fillColor(0.2, 1.0, 0.6, 0.5);
    r->fillRect(0, mouseY, 800, 1);
    r->fillRect(mouseX, 0, 1, 600);

    if (fpstick + 1000 < SDL_GetTicks()) {
      fps = fps_count;
      fps_count = 0;
      fpstick = SDL_GetTicks();
    }

    r->presentBuffer();
  }

  return 0;
}