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
//! Container component. Base component of MarinaTK.
class Container : public Component,
                  public std::enable_shared_from_this<Container> {
  private:
  std::vector<std::shared_ptr<Component>> children;

  std::weak_ptr<Component> parent;

  eventCallback pointer_cb;

  public:
  Layout::Node *layout_node = nullptr;

  glm::vec4 backgroundColor = glm::vec4(0.0);

  Container();
  Container(Layout::Node *n);

  bool onPointerEvent(Event *ev);
  bool onKeyboardEvent(Event *ev);

  void setPointerCustomCallback(const eventCallback cb);
  void removePointerCustomCallback();

  // Getters
  Layout::Node *getLayoutNode();
  std::weak_ptr<Component> getParent();
  std::vector<std::shared_ptr<Component>> getChildren();

  // Setters
  Component &setParent(std::weak_ptr<Component> c);
  Component &addChildren(std::shared_ptr<Component> c);
  Component &removeChildren(std::shared_ptr<Component> c);

  //! Set the size of the container
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax. */
  Container &setSize(Layout::Length x, Layout::Length y);
  //! Set the size of the padding
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax. */
  Container &setPadding(Layout::Length left, Layout::Length right,
                        Layout::Length top, Layout::Length bottom);
  //! Set the background color using a vector
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax. */
  Container &setBackgroundColor(glm::vec4 color);
  //! Set the background color using seperate RGBA values
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax. */
  Container &setBackgroundColor(float r, float g, float b, float a);
  //! Set the major axis (layout axis) for the component
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax. */
  Container &setMajorAxis(Layout::Axis a);

  ~Container();
};

} // namespace Components

} // namespace MTK
