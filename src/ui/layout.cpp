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

  if (interface)
    interface->layout((Node *)this, x, y, box.w, box.h);

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

glm::vec2 Layered::layout(Node *root, float x, float y, float max_x,
                          float max_y) const {
  ComputedBox box = getComputedSize(standardDPI, max_x, max_y);

  if (interface)
    interface->layout((Node *)this, x, y, box.w, box.h);

  for (Node *child : root->children) {
    child->layout(child, x + box.pad_left, y + box.pad_top,
                  box.w - box.pad_left - box.pad_right,
                  box.h - box.pad_top - box.pad_bottom);
  }

  return glm::vec2(box.w, box.h);
}

glm::vec2 Grid::layout(Node *root, float x, float y, float max_x,
                       float max_y) const {
  ComputedBox box = getComputedSize(standardDPI, max_x, max_y);

  if (interface)
    interface->layout((Node *)this, x, y, box.w, box.h);

  if (root->children.size() > 0) {
    float inner_space;

    if (root->major_axis == Y) {
      inner_space = box.h - box.pad_top - box.pad_bottom;
    } else {
      inner_space = box.w - box.pad_left - box.pad_right;
    }

    float gap =
        std::round(((Grid *)root)->gap.getComputedValue(standardDPI, max_x));
    float child_size = inner_space / root->children.size();

    int i = 0;
    for (Node *child : root->children) {
      float anchor_x;
      float anchor_y;
      float width_limit;
      float height_limit;

      if (root->major_axis == Y) {
        anchor_x = x + box.pad_left;
        anchor_y = std::round(y + box.pad_top + i * child_size);
        width_limit = box.w - box.pad_left - box.pad_right;
        height_limit =
            std::round(y + box.pad_top + (i + 1) * child_size) - anchor_y - gap;
      } else {
        anchor_x = std::round(x + box.pad_left + i * child_size);
        anchor_y = y + box.pad_top;
        width_limit = std::round(x + box.pad_left + (i + 1) * child_size) -
                      anchor_x - gap;
        height_limit = box.h - box.pad_top - box.pad_bottom;
      }

      child->layout(child, anchor_x, anchor_y, width_limit, height_limit);

      i++;
    }
  }

  return glm::vec2(box.w, box.h);
}

} // namespace MTK::Layout