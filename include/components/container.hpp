#pragma once

#include "component.hpp"

namespace MTK {

namespace Components {

class Container : public Component {
private:
  std::vector<Component *> children;

  Component *parent = nullptr;

  eventCallback pointer_cb;

public:
  Layout::Node *layout_node;

  glm::vec4 backgroundColor = glm::vec4(0.0);

  Container();
  Container(Layout::Node *n);

  bool onPointerEvent(Event *ev);
  bool onKeyboardEvent(Event *ev);

  void setPointerCustomCallback(const eventCallback cb);
  void removePointerCustomCallback();

  // Getters
  Layout::Node *getLayoutNode();
  Component *getParent();
  std::vector<Component *> getChildren();

  // Setters
  Component &setParent(Component *c);
  Component &addChildren(Component *c);
  Component &removeChildren(Component *c);

  Container &setSize(Layout::Length x, Layout::Length y);
  Container &setPadding(Layout::Length left, Layout::Length right,
                        Layout::Length top, Layout::Length bottom);
  Container &setBackgroundColor(glm::vec4 color);
  Container &setBackgroundColor(float r, float g, float b, float a);
  Container &setMajorAxis(Layout::Axis a);

  ~Container();
};

} // namespace Components

} // namespace MTK
