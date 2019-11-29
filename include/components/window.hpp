#pragma once

#include "container.hpp"

namespace MTK {

namespace Components {

class Window : public Container {
private:
  glm::vec2 size;

  void onPointer(Backend::Event *_e);

public:
  Window(Backend::Backend *b);

  void run();
};

} // namespace Components

} // namespace MTK
