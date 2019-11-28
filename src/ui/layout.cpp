#include "layout.hpp"

namespace MTK::Layout {

const float standardDPI = 96.0;

float Length::getComputedValue(float dpi, float max) const {
  if (unit == NativePixel)
    return value;
  if (unit == Pixel)
    return value / standardDPI * dpi;
  if (unit == Percent)
    return value / 100 * max;

  return 0.0;
}

ComputedBox Node::getComputedSize(float dpi, float max_x, float max_y) const {
  return {size.width.getComputedValue(dpi, max_x),
          size.height.getComputedValue(dpi, max_y),
          padding.left.getComputedValue(dpi, max_x),
          padding.right.getComputedValue(dpi, max_x),
          padding.top.getComputedValue(dpi, max_y),
          padding.bottom.getComputedValue(dpi, max_y)};
}

glm::vec2 Box::layout(Node *root, float x, float y, float max_x,
                      float max_y) const {
  ComputedBox box = getComputedSize(standardDPI, max_x, max_y);

  renderer->layout(x, y, box.w, box.h);

  for (Node *child : root->children) {
    glm::vec2 r = child->layout(child, x + box.pad_left, y + box.pad_top,
                                box.w - box.pad_left - box.pad_right,
                                box.h - box.pad_top - box.pad_bottom);
    if (root->major_axis == Y) {
      y += r.y;
    } else {
      x += r.x;
    }
  }

  return glm::vec2(box.w, box.h);
}

glm::vec2 Grid::layout(Node *root, float x, float y, float max_x,
                       float max_y) const {
  ComputedBox box = getComputedSize(standardDPI, max_x, max_y);

  renderer->layout(x, y, box.w, box.h);

  if (root->children.size() > 0) {
    float inner_space;

    if (root->major_axis == Y) {
      inner_space = box.h - box.pad_top - box.pad_bottom;
    } else {
      inner_space = box.w - box.pad_left - box.pad_right;
    }

    float child_spacing = inner_space / root->children.size();
    float child_size = child_spacing -
                       ((Grid *)root)->gap.getComputedValue(standardDPI, max_x);

    for (Node *child : root->children) {
      float width_limit;
      float height_limit;
      if (root->major_axis == Y) {
        width_limit = box.w - box.pad_left - box.pad_right;
        height_limit = child_size;
      } else {
        width_limit = child_size;
        height_limit = box.h - box.pad_top - box.pad_bottom;
      }
      child->layout(child, x + box.pad_left, y + box.pad_top, width_limit,
                    height_limit);
      if (root->major_axis == Y) {
        y += child_spacing;
      } else {
        x += child_spacing;
      }
    }
  }

  return glm::vec2(box.w, box.h);
}

} // namespace MTK::Layout