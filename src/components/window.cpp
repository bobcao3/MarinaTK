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

#include "components/window.hpp"

using namespace MTK;
using namespace MTK::Components;

Window::Window(Backend::Backend *b)
  : Container(new Layout::Box({ { 100.0, Layout::Percent },
                                { 100.0, Layout::Percent } },
                              {
                                { 0.0, Layout::Pixel },
                                { 0.0, Layout::Pixel },
                                { 0.0, Layout::Pixel },
                                { 0.0, Layout::Pixel },
                              },
                              Layout::X, {}, NULL))
{
  size = b->getSize();

  backend = b;

  auto cb = std::bind(&Window::onPointer, this, std::placeholders::_1);
  backend->setPointerCallback(cb);

  backgroundColor = glm::vec4(1.0);
}

void Window::onPointer(Backend::Event *_e)
{
  Backend::EventPointer *e = (Backend::EventPointer *)_e;

  Layout::Extent2 hit_pos = {
    Layout::Length::fromNative(Layout::standardDPI, e->x),
    Layout::Length::fromNative(Layout::standardDPI, e->y)
  };
  PointerEvent new_ev = { this, hit_pos, e->action };
  onPointerEvent(&new_ev);
}

void Window::run()
{
  while (!backend->isTerminated()) {
    backend->clear();

    backend->waitEvents();

    layout_node->layout(0, 0, size.x, size.y);

    backend->presentBuffer();
  }
}