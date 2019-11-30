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

#include "component.hpp"

namespace MTK
{
namespace Components
{
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
