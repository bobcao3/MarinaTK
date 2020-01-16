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

#include "components/text.hpp"

using namespace MTK;
using namespace MTK::Components;

#include <iostream>

Text::Text()
  : Container()
{
  layout_node->interface = [this](float x, float y, float w, float h) {
    bbox.box = { { x, y }, { x + w, y + h } };

    backend->fillColor(backgroundColor.r, backgroundColor.g, backgroundColor.b,
                       backgroundColor.a);
    backend->fillRect(x, y, w, h);

    backend->fillColor(text_color.r, text_color.g, text_color.b, text_color.a);
    backend->font(fontface.data(), font_size);
    backend->fillText(label.data(), x, y);
  };
}

Text &Text::setFont(std::string f)
{
  fontface = f;
  return *this;
}

Text &Text::setTextColor(glm::vec4 c)
{
  text_color = c;
  return *this;
}

Text &Text::setFontSize(MTK::Layout::Length s)
{
  font_size = s.getComputedValue(Layout::standardDPI, 0.0);
  return *this;
}

Text &Text::setText(std::string t)
{
  label = t;
  return *this;
}