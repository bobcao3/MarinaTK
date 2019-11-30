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

#include <functional>
#include <glm/glm.hpp>
#include <vector>

namespace MTK
{
//! Contains Layout functionality and abstractions
namespace Layout
{
const float standardDPI = 96.0f;

//! Enum for device native / independent units
enum Unit { Pixel, NativePixel, Percent };

//! Enum for X/Y axis / directions. Used to specify layout
enum Axis { X, Y };

//! Length type, contains a value and a unit
struct Length {
  //! The value
  float value;
  //! The unit
  Unit unit;

  //! Get the device native (pixel) length, given a DPI and a maximum limit.
  /*! The maximum is used to calculate percentage (relative) sizes */
  float getComputedValue(float dpi, float max = 0.0) const;

  //! Construct a length from native pixel length
  static Length fromNative(float dpi, float value);
};

namespace Units
{
constexpr Length operator"" _px(long double v)
{
  return Length{ (float)v, Pixel };
}

constexpr Length operator"" _px(unsigned long long v)
{
  return Length{ (float)v, Pixel };
}

constexpr Length operator"" _percent(long double v)
{
  return Length{ (float)v, Percent };
}

constexpr Length operator"" _percent(unsigned long long v)
{
  return Length{ (float)v, Percent };
}

} // namespace Units

//! Strut to store computed Box information
struct ComputedBox {
  //! Width & height in device native pixels
  float w, h;
  //! Size of padding in device native pixels
  float pad_left, pad_right, pad_top, pad_bottom;
};

//! Struct to store vector with 2 length
struct Extent2 {
  Length width, height;
};

//! Struct to store vector with 4 length
struct Extent4 {
  Length left, right, top, bottom;
};

class Node;

//! The interface to use the layout functionality for other parts of MTK.
typedef std::function<void(float, float, float, float)> layoutCallback;

//! Base class for a Layout Tree Node
class Node {
  public:
  //! Box size of this node
  Extent2 size;
  //! Box padding of this node
  Extent4 padding;
  //! The major axis of this node (Verticle / Horizontal)
  Axis major_axis;

  //! The list of children
  std::vector<Node *> children;

  //! The LayoutInterface that will be called for this node
  layoutCallback interface;

  //! Get the computed size of the Box of this node
  ComputedBox getComputedSize(float dpi, float max_x = 0.0,
                              float max_y = 0.0) const;

  Node(Extent2 size, Extent4 padding, Axis major_axis,
       std::vector<Node *> children, layoutCallback interface)
    : size{ size }
    , padding{ padding }
    , major_axis{ major_axis }
    , children{ children }
    , interface{ interface }
  {
  }

  virtual ~Node()
  {
  }

  //! The layout function that recursively traverses the tree and layout boxes.
  /*! This is a O(N) implementation, with simple constrains and deep trees */
  virtual glm::vec2 layout(float x, float y, float max_x,
                           float max_y) const = 0;
};

//! Box layout. Children inside the box lays side by side on major axis.
class Box : public Node {
  public:
  Box(Extent2 size, Extent4 padding, Axis major_axis,
      std::vector<Node *> children, layoutCallback interface)
    : Node(size, padding, major_axis, children, interface)
  {
  }

  glm::vec2 layout(float x, float y, float max_x, float max_y) const;
};

//! Grid layout. Children inside the grid are evenly spaced with a gap.
class Grid : public Node {
  public:
  //! The size of the gap
  Length gap;

  Grid(Extent2 size, Extent4 padding, Axis major_axis, Length gap,
       std::vector<Node *> children, layoutCallback interface)
    : Node(size, padding, major_axis, children, interface)
    , gap{ gap }
  {
  }

  glm::vec2 layout(float x, float y, float max_x, float max_y) const;
};

//! Layered layout. Children are layered on top of each other.
class Layered : public Node {
  public:
  Layered(Extent2 size, Extent4 padding, Axis major_axis,
          std::vector<Node *> children, layoutCallback interface)
    : Node(size, padding, major_axis, children, interface)
  {
  }

  glm::vec2 layout(float x, float y, float max_x, float max_y) const;
};

} // namespace Layout

} // namespace MTK