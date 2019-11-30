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

//! A window component backed by a user-specified backend
class Window : public Container {
  private:
  glm::vec2 size;

  void onPointer(Backend::Event *_e);

  public:
  //! Construtor. Takes a pointer to a _already created_ instance of backend.
  Window(Backend::Backend *b);

  void run();
};

} // namespace Components

} // namespace MTK
