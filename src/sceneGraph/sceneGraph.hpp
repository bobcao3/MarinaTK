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

#include "geometry.hpp"

namespace MTK {

    class SceneNode
    {
    public:
        virtual const BBox2D& getBBox() = 0;
        virtual void setBBox(BBox2D& bbox) = 0;
        virtual const mat3x3 getTransformation() = 0;

        virtual ~SceneNode() = 0;
    };

    class SceneNodeRect
    {

    };

    class SceneGraph
    {
    private:

    public:
        SceneGraph();
        ~SceneGraph();
    };
    

}