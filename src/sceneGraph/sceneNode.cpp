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

#include <sceneGraph.hpp>

using namespace std;

namespace MTK {

    SceneNode::SceneNode() {
        this->transformation = mat3x3(1.0);
    }

    SceneNode::SceneNode(BBox2D& bbox) {
        this->setBBox(bbox);
    }

    void SceneNode::setBBox(BBox2D& bbox) {
        this->bbox = bbox;
    }

    const BBox2D& SceneNode::getBBox() {
        return this->bbox;
    }

    const mat3x3 SceneNode::getTransformation() {
        return this->transformation;
    }

    vector<unique_ptr<SceneNodeAbstract>>& SceneNode::getChildren() {
        return this->children;
    }
}