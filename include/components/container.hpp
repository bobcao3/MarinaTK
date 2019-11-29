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

  glm::vec4 backgroundColor;

  Container();
  Container(Layout::Node* n);

  bool onPointerEvent(Event *ev);
  bool onKeyboardEvent(Event *ev);

  void setPointerCustomCallback(const eventCallback cb);
  void removePointerCustomCallback();

  Layout::Node *getLayoutNode();
  void setParent(Component *c);
  Component *getParent();
  std::vector<Component *> getChildren();
  void addChildren(Component *c);
  void removeChildren(Component *c);

  ~Container();
};

} // namespace Components

} // namespace MTK
