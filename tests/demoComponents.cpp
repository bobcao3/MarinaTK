#include "backend/SDL2.hpp"
#include "components/components.hpp"

using namespace MTK;

int main() {
  Components::Window w(new Backend::SDL2());

  w.run();

  return 0;
}