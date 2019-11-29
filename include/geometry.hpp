/*
 *  Copyright 2019 Cheng Cao
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#pragma once

#include <algorithm>

#include <glm/glm.hpp>

namespace MTK {

//! Contains scene graph abstractions
namespace SceneGraph {

using namespace glm;

//! Basic 2D Box
struct Box2D {
  vec2 p0, p1;

  /*!
   * Return whether the box is in correct condition, and correct the conditions
   * Conditions:
   *   x0 < x1 && y0 < y1
   */
  bool check();

  //! Return the area of the box
  float area();

  auto operator==(const Box2D &other) {
    return p0 == other.p0 && p1 == other.p1;
  };
  auto operator!=(const Box2D &other) { return !(*this == other); };
};

//! 2D Bounding Box
struct BBox2D {
  Box2D box;

  //! Join the bounding box to another one, return the new one
  BBox2D join(BBox2D &other);

  //! Test if two bounding boxes are colliding
  bool collide(BBox2D &other);

  //! Clip the bounding box with another, return the new one
  BBox2D clip(BBox2D &other);

  bool operator&&(const vec2 other) {
    return other.x > box.p0.x && other.x < box.p1.x && other.y > box.p0.y &&
           other.y < box.p1.y;
  };
};

} // namespace SceneGraph

} // namespace MTK