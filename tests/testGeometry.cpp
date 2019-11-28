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

#include <geometry.hpp>

#include "CUnit/Basic.h"
#include <glm/glm.hpp>

using namespace MTK;
using namespace MTK::SceneGraph;
using namespace glm;

void testBox2D() {
    Box2D box0 = {{0.0, 0.0}, {1.0, 3.0}};

    CU_ASSERT_TRUE(box0.check());
    CU_ASSERT_DOUBLE_EQUAL(box0.area(), 3.0, 1e-7);

    Box2D box1 = {{2.0, 0.0}, {1.0, 3.0}};

    CU_ASSERT_FALSE(box1.check());
    CU_ASSERT_DOUBLE_EQUAL(box1.p0.x, 1.5, 1e-7);
    CU_ASSERT_DOUBLE_EQUAL(box1.p1.x, 1.5, 1e-7);
    CU_ASSERT_DOUBLE_EQUAL(box1.area(), 0.0, 1e-7);
    CU_ASSERT_TRUE(box1.check());

    Box2D box2 = {{0.0, 5.0}, {1.0, 3.0}};

    CU_ASSERT_FALSE(box2.check());
    CU_ASSERT_DOUBLE_EQUAL(box2.p0.y, 4.0, 1e-7);
    CU_ASSERT_DOUBLE_EQUAL(box2.p1.y, 4.0, 1e-7);
    CU_ASSERT_DOUBLE_EQUAL(box2.area(), 0.0, 1e-7);
    CU_ASSERT_TRUE(box2.check());
}

void testBBox2D() {
    BBox2D bbox0 = { {{0.0, 0.0}, {1.0, 3.0}} };
    BBox2D bbox1 = { {{0.5, 0.5}, {2.0, 2.0}} };
    BBox2D bbox2 = { {{6.0, 6.0}, {8.0, 9.0}} };

    CU_ASSERT_TRUE(bbox0.collide(bbox1));
    CU_ASSERT_TRUE(bbox1.collide(bbox0));

    CU_ASSERT_FALSE(bbox0.collide(bbox2));
    CU_ASSERT_FALSE(bbox1.collide(bbox2));
    CU_ASSERT_FALSE(bbox2.collide(bbox0));

    BBox2D bbox01 = bbox0.join(bbox1);
    BBox2D bbox10 = bbox1.join(bbox0);
    CU_ASSERT(bbox01.box == bbox10.box);

    CU_ASSERT(bbox01.clip(bbox1).box == bbox1.box);

    BBox2D bboxIntersect = { {{0.5, 0.5}, {1.0, 2.0}} };

    CU_ASSERT(bbox0.clip(bbox1).box == bboxIntersect.box);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test Geometry & SceneGraph", nullptr, nullptr);
    if (nullptr == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

   /* add the tests to the suite */
   if (
       (nullptr == CU_add_test(pSuite, "test of Box", testBox2D)) ||
       (nullptr == CU_add_test(pSuite, "test of BBox", testBBox2D))
    ){
      CU_cleanup_registry();
      return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    int failed = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return failed;
}