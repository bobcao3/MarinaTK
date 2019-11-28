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

#include <string>
#include <vector>
#include <memory>

namespace MTK {

    //! An abstract Scene Node.
    class SceneNodeAbstract
    {
    public:
        //! Get the bounding box of this node
        virtual const BBox2D& getBBox() = 0;
        
        //! Set the bounding box of this node
        virtual void setBBox(BBox2D& bbox) = 0;
        
        //! Get the transformation matrix (3x3 as it's 2D) of this node
        virtual const mat3x3 getTransformation() = 0;

        virtual ~SceneNodeAbstract() {};

        //! Get the children of this node
        virtual std::vector<std::unique_ptr<SceneNodeAbstract>>& getChildren() = 0;
    };

    //! An ordinary rectangular scene node with defined bounding box.
    class SceneNode : public SceneNodeAbstract
    {
    private:
        BBox2D bbox;
        mat3x3 transformation;
        std::vector<std::unique_ptr<SceneNodeAbstract>> children;

    public:
        //! Get the bounding box of this node
        const BBox2D& getBBox();
        
        //! Set the bounding box of this node
        void setBBox(BBox2D& bbox);
        
        //! Get the transformation matrix (3x3 as it's 2D) of this node
        const mat3x3 getTransformation();

        //! Get the children of this node
        std::vector<std::unique_ptr<SceneNodeAbstract>>& getChildren();

        SceneNode();
        
        SceneNode(BBox2D& bbox);
    };

    //! The 2D Scene Graph class.
    class SceneGraph
    {
    private:
        SceneNode root;

    public:
        SceneGraph();
        
        ~SceneGraph();
    };
    

}