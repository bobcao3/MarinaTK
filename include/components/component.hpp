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
#include <memory>

namespace MTK
{
//! Contains Components abstractions and basic components
namespace Components
{
//! Event base type for component events
struct Event {
  //! The target of the event
  void *target;
};

//! Event data for pointer (mouse, touch, pen, etc.) input event
struct PointerEvent : public Event {
  //! Device independent location of the pointer, relative to the target
  Layout::Extent2 location;
  //! The pointer action happened
  Backend::ButtonAction action;
};

//! Custom callback functions for events
typedef std::function<bool(Event *)> eventCallback;

//! The base type of all components
class Component {
  public:
  //! The rendering backend
  Backend::Backend *backend;

  //! The bounding box of this component
  SceneGraph::BBox2D bbox;

  //! Built-in event handler for pointer events
  /*! End user should not use / modify this handler without knowing what they
   *  are doing as this may contain logic that dictates pointer hit
   *  calculations, event propogations, etc. */
  virtual bool onPointerEvent(Event *ev) = 0;
  //! Built-in event handler for keyboard events
  /*! End user should not use / modify this handler without knowing what they
   *  are doing as this may contain logic that dictates pointer hit
   *  calculations, event propogations, etc. */
  virtual bool onKeyboardEvent(Event *ev) = 0;

  //! Set the custom callback for pointer events
  /*! End user should be utilizing this as their way of event callback. Lambda,
   *  functions, anything supported by STL's `std::function` is supported here.
   */
  virtual void setPointerCustomCallback(eventCallback e) = 0;
  //! Remove / reset the custom pointer event callback
  virtual void removePointerCustomCallback() = 0;

  // Getters
  //! Get the layout node of this component.
  virtual Layout::Node *getLayoutNode() = 0;
  //! Get the parent component.
  virtual std::weak_ptr<Component> getParent() = 0;
  //! Get the list of children as a vector of components
  virtual std::vector<std::shared_ptr<Component>> getChildren() = 0;

  // Setters
  //! Set the parent of the component.
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax.
   *  This function DOES NOT remove the component from the current parent's
   *  children list, so use it with caution */
  virtual Component &setParent(std::weak_ptr<Component> c) = 0;
  //! Add a children to this component.
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax.
   *  This function will call children's `setParent` method. */
  virtual Component &addChildren(std::shared_ptr<Component> c) = 0;
  //! Remove a children from this component
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax. */
  virtual Component &removeChildren(std::shared_ptr<Component> c) = 0;

  virtual ~Component()
  {
  }
};

} // namespace Components

} // namespace MTK
