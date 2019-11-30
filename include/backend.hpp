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

#include "geometry.hpp"

#include <functional>

namespace MTK
{
//! Contains backend abstrations.
namespace Backend
{
//! Backend Event Base Class
struct Event {
  //! Target of this event.
  /*! Usually it's the pointer to the backend instance triggered the event. */
  void *target;
};

//! Enum for Button (mouse, keyboard, touch, etc.) Actions
enum ButtonAction { DOWN, UP, HOVER };

//! Backend Keyboard Event Class
struct EventKey : public Event {
  //! String encoded key. May switch to XCB key code in the future.
  std::string key;
  //! The action type of the event
  ButtonAction action;
};

//! Backend Pointer Event Class
struct EventPointer : public Event {
  //! String encoded pointer/button id. May switch to XCB code in the future
  std::string button;
  //! The action type of the event
  ButtonAction action;
  //! The native device coordinate of the pointer event
  int x, y;
};

//! Backend Event Callback Type
typedef std::function<void(Event *)> eventCallback;

//! Platform Backend Abstraction
/*! Each instance represents a native platform "window" or "view", with its
 *  corresponding inputs / outputs.
 *  The graphics API is similar to HTML5 Canvas API.
 */
class Backend {
  public:
  //! Get the size of the window
  virtual glm::vec2 getSize() = 0;

  //! Draw a filled rectangle
  virtual void fillRect(float x, float y, float width, float height) = 0;
  //! Draw a rectangle outline. The width of outline is always 1 native pixel
  virtual void strokeRect(float x, float y, float width, float height) = 0;
  //! Clear a region to background color
  virtual void clearRect(float x, float y, float width, float height) = 0;
  //! Clear the framebuffer
  virtual void clear() = 0;

  //! Present the whole framebuffer to display server / driver
  virtual void presentBuffer() = 0;
  //! Present a region to display server / driver.
  /*! Depending on the backend implementation, this may present a larger area
   *  than specified, or even a fullscreen present.
   */
  virtual void presentRegion(float x, float y, float width, float height) = 0;

  //! Set the font (typeface, size, style) of the paint brush.
  /*! Caching is handled by the backend implementation. */
  virtual void font(const char *name, int size) = 0;
  //! Draw filled text
  virtual void fillText(const char *str, float x, float y) = 0;

  //! Set the fill color of the paint brush.
  virtual void fillColor(float r, float g, float b, float a) = 0;

  //! Wait for events to happen.
  /*! In some implementations this is needed for event callbacks to work. */
  virtual void waitEvents() = 0;
  //! Get whether the backend received termination signal (window close).
  virtual bool isTerminated() = 0;

  //! Set the keyboard event callback
  virtual void setKeyCallback(eventCallback cb) = 0;
  //! Set the pointer event callback
  virtual void setPointerCallback(eventCallback cb) = 0;

  virtual ~Backend()
  {
  }
};

} // namespace Backend

} // namespace MTK