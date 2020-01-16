/*
 * Copyright 2019 Cheng Cao (bobcao3)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "components/container.hpp"

using namespace MTK;
using namespace MTK::Components;

Container::Container()
  : Container(new Layout::Box({ { 100.0, Layout::Percent },
                                { 100.0, Layout::Percent } },
                              {
                                { 0.0, Layout::Pixel },
                                { 0.0, Layout::Pixel },
                                { 0.0, Layout::Pixel },
                                { 0.0, Layout::Pixel },
                              },
                              Layout::X, {}, NULL))
{
}

Container::Container(Layout::Node *n)
  : layout_node{ n }
{
  layout_node->interface = [this](float x, float y, float w, float h) {
    bbox.box = { { x, y }, { x + w, y + h } };

    backend->fillColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                       backgroundColor.a);
    backend->fillRect(x, y, w, h);
  };
}

bool Container::onPointerEvent(Event *ev)
{
  PointerEvent *event = (PointerEvent *)ev;

  float px = event->location.width.getComputedValue(Layout::standardDPI);
  float py = event->location.height.getComputedValue(Layout::standardDPI);
  glm::vec2 p(px, py);
  p += bbox.box.p0;

  bool propogate = true;

  for (auto child : children) {
    if (child->bbox && p) {
      glm::vec2 p_in_child = p - child->bbox.box.p0;
      Layout::Extent2 hit_pos = {
        Layout::Length::fromNative(Layout::standardDPI, p_in_child.x),
        Layout::Length::fromNative(Layout::standardDPI, p_in_child.y)
      };
      PointerEvent new_ev = { child.get(), hit_pos, event->action };
      propogate = propogate && child->onPointerEvent(&new_ev);
    }
  }

  if (propogate) {
    if (pointer_cb) {
      propogate = propogate && pointer_cb(event);
    } else {
      propogate = true;
    }
  }

  return propogate;
}

bool Container::onKeyboardEvent([[maybe_unused]] Event *ev)
{
  return true;
}

void Container::setPointerCustomCallback(const eventCallback cb)
{
  pointer_cb = cb;
}

void Container::removePointerCustomCallback()
{
  pointer_cb = nullptr;
}

// Getters
Layout::Node *Container::getLayoutNode()
{
  return layout_node;
}

std::weak_ptr<Component> Container::getParent()
{
  return parent;
}

std::vector<std::shared_ptr<Component>> Container::getChildren()
{
  return children;
}

// Setters
Component &Container::setParent(std::weak_ptr<Component> c)
{
  parent = c;
  return *this;
}

Component &Container::addChildren(std::shared_ptr<Component> c)
{
  children.push_back(c);
  layout_node->children.push_back(c->getLayoutNode());

  c->setParent(weak_from_this());
  c->backend = backend;

  return *this;
}

Component &Container::removeChildren(std::shared_ptr<Component> c)
{
  children.erase(std::find(children.begin(), children.end(), c));
  return *this;
}

Container &Container::setSize(Layout::Length x, Layout::Length y)
{
  layout_node->size = { x, y };

  return *this;
}

Container &Container::setPadding(Layout::Length left, Layout::Length right,
                                 Layout::Length top, Layout::Length bottom)
{
  layout_node->padding = { left, right, top, bottom };

  return *this;
}

Container &Container::setBackgroundColor(glm::vec4 color)
{
  backgroundColor = color;

  return *this;
}

Container &Container::setBackgroundColor(float r, float g, float b, float a)
{
  backgroundColor = { r, g, b, a };

  return *this;
}

Container &Container::setMajorAxis(Layout::Axis a)
{
  layout_node->major_axis = a;
  return *this;
}

// Destructor
Container::~Container()
{
  if (layout_node) {
    delete layout_node;
    layout_node = nullptr;
  }
}