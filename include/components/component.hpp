#pragma once

#include "layout.hpp"
#include "backend.hpp"

namespace MTK {

//! Contains Components abstractions and basic components
namespace Components {

struct Event {
    void* target;
};

struct PointerEvent : public Event {
    Layout::Extent2 location;
    Backend::ButtonAction action;
};

class Component {
public:
    virtual bool onPointerEvent(Event* ev) = 0;
    virtual bool onKeyboardEvent(Event* ev) = 0;

    virtual Layout::Node* getLayoutNode() = 0;
    virtual Component *getParent() = 0;
    virtual std::vector<Component *> getChildren() = 0;
    virtual void removeChildren(Component* c) = 0;

    virtual ~Component() {}
};

}

}
