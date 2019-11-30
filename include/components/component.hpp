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

#pragma once

#include "backend.hpp"
#include "geometry.hpp"
#include "layout.hpp"

#include <functional>

namespace MTK
{
//! Contains Components abstractions and basic components
namespace Components
{
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

  virtual ~Component()
  {
  }
};

} // namespace Components

} // namespace MTK
