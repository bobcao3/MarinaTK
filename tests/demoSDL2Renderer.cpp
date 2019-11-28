#include <mtk.hpp>
#include <backend/SDL2.hpp>

#include <iostream>

using namespace MTK;

int main() {
  Backend::SDL2 *r = new Backend::SDL2();

  r->fillRect(50, 50, 100, 50);
  r->strokeRect(25, 25, 150, 100);
  r->clearRect(100, 75, 50, 50);

  r->presentBuffer();

  std::cin.get();

  return 0;
}