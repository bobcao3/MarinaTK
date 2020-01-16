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

#include "backend/SDL2.hpp"
#include "components/components.hpp"

using namespace MTK;

using namespace MTK::Components;

#include <iostream>

int main()
{
  Backend::SDL2 b;

  Components::Window w(&b);

  auto big_blue_box = std::make_shared<Container>();
  big_blue_box->layout_node->size = { { 50, Layout::Pixel },
                                     { 50, Layout::Pixel } };
  big_blue_box->backgroundColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
  w.addChildren(big_blue_box);

  w.setPointerCustomCallback([&b](Components::Event *_e) {
    Components::PointerEvent *e = (Components::PointerEvent *)_e;
    float x = e->location.width.getComputedValue(Layout::standardDPI);
    float y = e->location.height.getComputedValue(Layout::standardDPI);

    b.fillColor(0.2, 1.0, 0.6, 0.5);
    b.fillRect(0, y, 800, 1);
    b.fillRect(x, 0, 1, 600);

    return true;
  });

  auto big_red_box = std::make_shared<Container>();
  big_red_box->layout_node->size = { { 250, Layout::Pixel },
                                    { 150, Layout::Pixel } };
  big_red_box->layout_node->padding = { { 25, Layout::Pixel },
                                        { 25, Layout::Pixel },
                                        { 25, Layout::Pixel },
                                        { 25, Layout::Pixel } };
  big_red_box->backgroundColor = glm::vec4(1.0, 0.0, 0.0, 1.0);
  w.addChildren(big_red_box);

  auto small_yellow_box = std::make_shared<Container>();
  small_yellow_box->layout_node->size = { { 100, Layout::Percent },
                                         { 100, Layout::Percent } };
  small_yellow_box->backgroundColor = glm::vec4(1.0, 1.0, 0.0, 1.0);
  big_red_box->addChildren(small_yellow_box);

  auto verticle_grid = std::make_shared<Grid>();
  verticle_grid->layout_node->size = { { 100, Layout::Percent },
                                       { 100, Layout::Percent } };
  verticle_grid->layout_node->major_axis = Layout::Y;
  verticle_grid->layout_node->padding = { { 25, Layout::Pixel },
                                          { 25, Layout::Pixel },
                                          { 25, Layout::Pixel },
                                          { 25, Layout::Pixel } };
  verticle_grid->setGap({ 25, Layout::Pixel });
  verticle_grid->backgroundColor = glm::vec4(0.8, 0.8, 0.8, 1.0);
  w.addChildren(verticle_grid);

  for (int i = 0; i < 5; i++) {
    auto hover = std::make_shared<Container>(Components::Container());
    hover->layout_node->size = { { 100, Layout::Percent },
                                 { 100, Layout::Percent } };
    hover->backgroundColor = glm::vec4(1.0, 0.0, 0.0, 1.0);
    hover->setPointerCustomCallback(
      [hover]([[maybe_unused]] Components::Event *ev) {
        hover->backgroundColor = glm::vec4(0.0, 1.0, 0.0, 1.0);
        return true;
      });
    verticle_grid->addChildren(hover);
  }

  w.run();

  return 0;
}