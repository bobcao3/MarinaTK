#pragma once

#include "component.hpp"

namespace MTK {

namespace Components {

class Window : public Component {
private:
  Backend::Backend *backend;

  glm::vec2 size;

  Layout::Box *layout_node;

  int mouseX, mouseY;

  void onPointer(Backend::Event *_e);

public:
  Window(Backend::Backend *b);

  bool onPointerEvent(Event *ev);
  bool onKeyboardEvent(Event *ev);

  Layout::Node *getLayoutNode();
  Component *getParent();
  std::vector<Component *> getChildren();
  void removeChildren(Component *c);

  void run();

  ~Window();
};

} // namespace Components

} // namespace MTK
