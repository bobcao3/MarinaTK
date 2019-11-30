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

#include "components/grid.hpp"

using namespace MTK;
using namespace MTK::Components;

Grid::Grid()
  : Container(new Layout::Grid({ { 100.0, Layout::Percent },
                                 { 100.0, Layout::Percent } },
                               {
                                 { 0.0, Layout::Pixel },
                                 { 0.0, Layout::Pixel },
                                 { 0.0, Layout::Pixel },
                                 { 0.0, Layout::Pixel },
                               },
                               Layout::X, { 0, Layout::Pixel }, {}, NULL))
{
}

void Grid::setGap(Layout::Length l)
{
  ((Layout::Grid *)layout_node)->gap = l;
}