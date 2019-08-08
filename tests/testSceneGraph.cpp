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
#include <sceneGraph.hpp>

#include "CUnit/Basic.h"
#include <glm/glm.hpp>

using namespace MTK;
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

    Box2D box2 = {{0.0, 5.0}, {1.0, 3.0}};

    CU_ASSERT_FALSE(box2.check());
    CU_ASSERT_DOUBLE_EQUAL(box2.p0.y, 4.0, 1e-7);
    CU_ASSERT_DOUBLE_EQUAL(box2.p1.y, 4.0, 1e-7);
    CU_ASSERT_DOUBLE_EQUAL(box2.area(), 0.0, 1e-7);
}

void testBBox2D() {

}

int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Test Geometry & SceneGraph", nullptr, nullptr);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

   /* add the tests to the suite */
   if (
       (NULL == CU_add_test(pSuite, "test of Box", testBox2D)) ||
       (NULL == CU_add_test(pSuite, "test of BBox", testBBox2D))
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