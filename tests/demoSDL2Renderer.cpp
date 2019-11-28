#include <mtk.hpp>
#include <backend/SDL2.hpp>

#include <iostream>

using namespace MTK;

int main() {
  Backend::SDL2 *r = new Backend::SDL2();

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

  r->presentBuffer();

  std::cin.get();

  return 0;
}