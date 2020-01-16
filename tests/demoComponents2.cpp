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
using namespace Components;
using namespace MTK::Layout::Units;

#include <iostream>

int main()
{
  Backend::SDL2 b;

  Window w(&b);
  w.setBackgroundColor(0, 0, 1, 1).setPadding(15_px, 15_px, 15_px, 15_px);

  auto black_box = std::make_shared<Container>();
  black_box->setBackgroundColor(0, 0, 0, 1)
    .setSize(480_px, 400_px)
    .setPadding(5_px, 5_px, 5_px, 5_px);
  w.addChildren(black_box);

  auto white_box = std::make_shared<Container>();
  white_box->setBackgroundColor(1, 1, 1, 1)
    .setSize(100_percent, 100_percent)
    .setPadding(5_px, 5_px, 5_px, 5_px)
    .setMajorAxis(Layout::Y);
  black_box->addChildren(white_box);

  auto top_graphs = std::make_shared<Container>();
  top_graphs->setSize(100_percent, 280_px);
  white_box->addChildren(top_graphs);

  auto black_box_L = std::make_shared<Container>();
  black_box_L->setBackgroundColor(0, 0, 0, 1)
    .setSize(70_px, 100_percent)
    .setPadding(5_px, 5_px, 5_px, 5_px);
  top_graphs->addChildren(black_box_L);

  auto red_box_L = std::make_shared<Container>();
  red_box_L->setBackgroundColor(1, 0, 0, 1);
  black_box_L->addChildren(red_box_L);

  auto top_gap = std::make_shared<Container>();
  top_gap->setSize(10_px, 100_percent);
  top_graphs->addChildren(top_gap);

  auto black_box_R = std::make_shared<Container>();
  black_box_R->setBackgroundColor(0, 0, 0, 1)
    .setPadding(10_px, 10_px, 10_px, 10_px);
  top_graphs->addChildren(black_box_R);

  auto white_box_R = std::make_shared<Container>();
  white_box_R->setBackgroundColor(1, 1, 1, 1).setPadding(5_px, 5_px, 5_px, 5_px);
  black_box_R->addChildren(white_box_R);

  auto red_text_R = std::make_shared<Text>();
  red_text_R->setFont("/usr/share/fonts/truetype/NotoSans-Regular.ttf")
    .setFontSize(16_px)
    .setTextColor({ 1.0, 0.0, 0.0, 1.0 })
    .setText("The quick brown fox jumps over the lazy dog.");
  white_box_R->addChildren(red_text_R);

  w.run();

  return 0;
}