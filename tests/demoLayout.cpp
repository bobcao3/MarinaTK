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

#include <backend/SDL2.hpp>
#include <layout.hpp>
#include <mtk.hpp>

#include <chrono>
#include <iostream>

using namespace MTK;

Backend::SDL2 *r;

void layout(float x, float y, float w, float h)
{
  r->strokeRect(x, y, w, h);
}

int main()
{
  r = new Backend::SDL2();

  Layout::Box box0({ { 50.0, Layout::Pixel }, { 50.0, Layout::Pixel } },
                   {
                     { 0.0, Layout::Pixel },
                     { 0.0, Layout::Pixel },
                     { 0.0, Layout::Pixel },
                     { 0.0, Layout::Pixel },
                   },
                   Layout::Y, {}, layout);

  Layout::Box box1_0({ { 100.0, Layout::Percent }, { 100.0, Layout::Percent } },
                     {
                       { 0.0, Layout::Pixel },
                       { 0.0, Layout::Pixel },
                       { 0.0, Layout::Pixel },
                       { 0.0, Layout::Pixel },
                     },
                     Layout::Y, {}, layout);

  Layout::Grid box1 = { { { 300.0, Layout::Pixel }, { 100.0, Layout::Pixel } },
                        {
                          { 10.0, Layout::Pixel },
                          { 10.0, Layout::Pixel },
                          { 10.0, Layout::Pixel },
                          { 10.0, Layout::Pixel },
                        },
                        Layout::X,
                        { 5, Layout::Pixel },
                        { &box1_0, &box1_0, &box1_0 },
                        layout };

  Layout::Box box2 = { { { 0.0, Layout::Pixel }, { 100.0, Layout::Pixel } },
                       {
                         { 0.0, Layout::Pixel },
                         { 0.0, Layout::Pixel },
                         { 0.0, Layout::Pixel },
                         { 0.0, Layout::Pixel },
                       },
                       Layout::Y,
                       {},
                       layout };

  Layout::Box root = { { { 800.0, Layout::Pixel }, { 600.0, Layout::Pixel } },
                       {
                         { 10.0, Layout::Pixel },
                         { 10.0, Layout::Pixel },
                         { 50.0, Layout::Pixel },
                         { 50.0, Layout::Pixel },
                       },
                       Layout::Y,
                       { &box0, &box1, &box2 },
                       layout };

  auto start = std::chrono::steady_clock::now();

  while (!r->isTerminated()) {
    r->clear();
    r->waitEvents();

    auto end = std::chrono::steady_clock::now();
    float time =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    box1.size.width.value = sin(time * 0.001) * 200 + 400;

    root.layout(0, 0, 0, 0);

    r->presentBuffer();
  }

  return 0;
}