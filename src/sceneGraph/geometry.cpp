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

#include "geometry.hpp"

namespace MTK {

    bool Box2D::check() {
        bool result = true;
        if (p0.x > p1.x) {
            float average = (p0.x + p1.x) * 0.5;
            p0.x = average;
            p1.x = average;
            result &= false;
        }
        if (p0.y > p1.y) {
            float average = (p0.y + p1.y) * 0.5;
            p0.y = average;
            p1.y = average;
            result &= false;
        }
        return result;
    }

    float Box2D::area() {
        vec2 size = p1 - p0;
        return size.x * size.y;
    }

    BBox2D BBox2D::join(BBox2D& other) {
        BBox2D result = {{
            min(box.p0, other.box.p0),
            max(box.p1, other.box.p1)
        }};
        result.box.check();
        return result;
    }

    BBox2D BBox2D::clip(BBox2D& other) {
        BBox2D result = {{
            max(box.p0, other.box.p0),
            min(box.p1, other.box.p1)
        }};
        result.box.check();
        return result;
    }

}