#include <mtk.hpp>
#include <renderer_backend/SDL2_renderer.hpp>

#include <iostream>

int main() {
  SDL2_Renderer *r = new SDL2_Renderer();

  r->fillRect(50, 50, 100, 50);
  r->strokeRect(25, 25, 150, 100);
  r->clearRect(100, 75, 50, 50);

  r->presentBuffer();

  std::cin.get();

  return 0;
}