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

#pragma once

#include "container.hpp"

namespace MTK
{
namespace Components
{

//! Container component with Grid layout
class Grid : public Container {
  public:
  Grid();

  //! Set the gap of the grid
  /*! This function call and all other setters are chainable for more user
   *  friendly syntax. */
  void setGap(Layout::Length l);
};

} // namespace Components

} // namespace MTK
