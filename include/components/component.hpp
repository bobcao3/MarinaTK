#pragma once

#include "backend.hpp"
#include "geometry.hpp"
#include "layout.hpp"

#include <functional>

namespace MTK {

//! Contains Components abstractions and basic components
namespace Components {

struct Event {
  void *target;
};

struct PointerEvent : public Event {
  Layout::Extent2 location;
  Backend::ButtonAction action;
};

typedef std::function<bool(Event *)> eventCallback;

class Component {
public:
  Backend::Backend *backend;

  SceneGraph::BBox2D bbox;

  virtual bool onPointerEvent(Event *ev) = 0;
  virtual bool onKeyboardEvent(Event *ev) = 0;

  virtual void setPointerCustomCallback(eventCallback e) = 0;
  virtual void removePointerCustomCallback() = 0;

  // Getters
  virtual Layout::Node *getLayoutNode() = 0;
  virtual Component *getParent() = 0;
  virtual std::vector<Component *> getChildren() = 0;

  // Setters
  virtual Component &setParent(Component *c) = 0;
  virtual Component &addChildren(Component *c) = 0;
  virtual Component &removeChildren(Component *c) = 0;

  virtual ~Component() {}
};

} // namespace Components

} // namespace MTK
