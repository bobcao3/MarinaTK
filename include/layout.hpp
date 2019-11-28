#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace MTK {

//! Contains Layout functionality and abstractions
namespace Layout {

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
};

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
class LayoutInterface {
public:
  //! The callback for the layout function.
  /*! All the inputs are in device native pixels,
   *  The `node` pointer specifies which node called this layout interface.
   *  Usually widgets uses this interface to get the rendering bound / location
   *  of the widget.
   */ 
  virtual void layout(Node* node, float x, float y, float w, float h) = 0;
  virtual ~LayoutInterface() {}
};

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
  LayoutInterface *interface;

  //! Get the computed size of the Box of this node
  ComputedBox getComputedSize(float dpi, float max_x = 0.0,
                              float max_y = 0.0) const;

  Node(Extent2 size, Extent4 padding, Axis major_axis,
       std::vector<Node *> children, LayoutInterface *interface)
      : size{size}, padding{padding},
        major_axis{major_axis}, children{children}, interface{interface} {}

  virtual ~Node() {}

  //! The layout function that recursively traverses the tree and layout boxes.
  /*! This is a O(N) implementation, with simple constrains and deep trees */
  virtual glm::vec2 layout(Node *root, float x, float y, float max_x,
                           float max_y) const = 0;
};

//! Box layout. Children inside the box lays side by side on major axis.
class Box : public Node {
public:
  Box(Extent2 size, Extent4 padding, Axis major_axis,
      std::vector<Node *> children, LayoutInterface *interface)
      : Node(size, padding, major_axis, children, interface) {}

  glm::vec2 layout(Node *root, float x, float y, float max_x,
                   float max_y) const;
};

//! Grid layout. Children inside the grid are evenly spaced with a gap.
class Grid : public Node {
public:
  //! The size of the gap
  Length gap;

  Grid(Extent2 size, Extent4 padding, Axis major_axis, Length gap,
       std::vector<Node *> children, LayoutInterface *interface)
      : Node(size, padding, major_axis, children, interface), gap{gap} {}

  glm::vec2 layout(Node *root, float x, float y, float max_x,
                   float max_y) const;
};

//! Layered layout. Children are layered on top of each other.
class Layered : public Node {
public:
  Layered(Extent2 size, Extent4 padding, Axis major_axis,
          std::vector<Node *> children, LayoutInterface *interface)
      : Node(size, padding, major_axis, children, interface) {}

  glm::vec2 layout(Node *root, float x, float y, float max_x,
                   float max_y) const;
};

}

} // namespace MTK::Layout