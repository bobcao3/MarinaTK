#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace MTK::Layout {

enum Unit { Pixel, NativePixel, Percent };

enum Axis { X, Y };

struct Length {
  float value;
  Unit unit;

  float getComputedValue(float dpi, float max = 0.0) const;
};

struct ComputedBox {
  float w, h;
  float pad_left, pad_right, pad_top, pad_bottom;
};

struct Extent2 {
  Length width, height;
};

struct Extent4 {
  Length left, right, top, bottom;
};

class LayoutInterface {
public:
  virtual void layout(float x, float y, float w, float h) = 0;
  virtual ~LayoutInterface() {}
};

class Node {
public:
  Extent2 size;
  Extent4 padding;
  Axis major_axis;

  std::vector<Node *> children;

  LayoutInterface *renderer;

  ComputedBox getComputedSize(float dpi, float max_x = 0.0,
                              float max_y = 0.0) const;

  Node(Extent2 size, Extent4 padding, Axis major_axis,
       std::vector<Node *> children, LayoutInterface *renderer)
      : size{size}, padding{padding},
        major_axis{major_axis}, children{children}, renderer{renderer} {}

  virtual ~Node() {}

  virtual glm::vec2 layout(Node *root, float x, float y, float max_x,
                           float max_y) const = 0;
};

class Box : public Node {
public:
  Box(Extent2 size, Extent4 padding, Axis major_axis,
      std::vector<Node *> children, LayoutInterface *renderer)
      : Node(size, padding, major_axis, children, renderer) {}

  glm::vec2 layout(Node *root, float x, float y, float max_x,
                   float max_y) const;
};

class Grid : public Node {
public:
  Length gap;

  Grid(Extent2 size, Extent4 padding, Axis major_axis, Length gap,
       std::vector<Node *> children, LayoutInterface *renderer)
      : Node(size, padding, major_axis, children, renderer), gap{gap} {}

  glm::vec2 layout(Node *root, float x, float y, float max_x,
                   float max_y) const;
};

} // namespace MTK::Layout