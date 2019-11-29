#include "backend/SDL2.hpp"
#include "components/components.hpp"

using namespace MTK;

#include <iostream>

int main() {
  Backend::SDL2 b;

  Components::Window w(&b);

  Components::Container big_blue_box;
  big_blue_box.layout_node->size = {{50, Layout::Pixel}, {50, Layout::Pixel}};
  big_blue_box.backgroundColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
  w.addChildren(&big_blue_box);

  w.setPointerCustomCallback([&b](Components::Event *_e) {
    Components::PointerEvent *e = (Components::PointerEvent *)_e;
    float x = e->location.width.getComputedValue(Layout::standardDPI);
    float y = e->location.height.getComputedValue(Layout::standardDPI);

    b.fillColor(0.2, 1.0, 0.6, 0.5);
    b.fillRect(0, y, 800, 1);
    b.fillRect(x, 0, 1, 600);

    return true;
  });

  Components::Container big_red_box;
  big_red_box.layout_node->size = {{250, Layout::Pixel}, {150, Layout::Pixel}};
  big_red_box.layout_node->padding = {{25, Layout::Pixel},
                                      {25, Layout::Pixel},
                                      {25, Layout::Pixel},
                                      {25, Layout::Pixel}};
  big_red_box.backgroundColor = glm::vec4(1.0, 0.0, 0.0, 1.0);
  w.addChildren(&big_red_box);

  Components::Container small_yellow_box;
  small_yellow_box.layout_node->size = {{100, Layout::Percent},
                                        {100, Layout::Percent}};
  small_yellow_box.backgroundColor = glm::vec4(1.0, 1.0, 0.0, 1.0);
  big_red_box.addChildren(&small_yellow_box);

  Components::Grid verticle_grid;
  verticle_grid.layout_node->size = {{100, Layout::Percent},
                                     {100, Layout::Percent}};
  verticle_grid.layout_node->major_axis = Layout::Y;
  verticle_grid.layout_node->padding = {{25, Layout::Pixel},
                                        {25, Layout::Pixel},
                                        {25, Layout::Pixel},
                                        {25, Layout::Pixel}};
  verticle_grid.setGap({25, Layout::Pixel});
  verticle_grid.backgroundColor = glm::vec4(0.8, 0.8, 0.8, 1.0);
  w.addChildren(&verticle_grid);

  for (int i = 0; i < 5; i++) {
    auto hover = new Components::Container();
    hover->layout_node->size = {{100, Layout::Percent}, {100, Layout::Percent}};
    hover->backgroundColor = glm::vec4(1.0, 0.0, 0.0, 1.0);
    hover->setPointerCustomCallback([hover](Components::Event *ev) {
      hover->backgroundColor = glm::vec4(0.0, 1.0, 0.0, 1.0);
      return true;
    });
    verticle_grid.addChildren(hover);
  }

  w.run();

  return 0;
}